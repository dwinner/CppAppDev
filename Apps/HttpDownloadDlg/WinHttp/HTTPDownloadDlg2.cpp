/*
Module : HTTPDownloadDlg2.cpp
Purpose: Defines the implementation for an MFC dialog which performs HTTP downloads
         similiar to the Internet Explorer download dialog using WinHTTP
Created: PJN / 16-07-2006
History: PJN / 17-09-2006 1. Fixed an issue where the OnStatusCallback method was not being called. This has been addressed
                          by renaming the function to OnWinHttpStatusCallBack. This is necessary due to the refactoring
                          of the base CHttpDownloader2 class. Thanks to Johan Sörensen for reporting this bug
         PJN / 11-05-2008 1. Updated copyright messages.
                          2. OnProgress virtual method now correctly handles reporting results for resumed downloads
         PJN / 08-06-2008 1. Updated code to compile correctly using _ATL_CSTRING_EXPLICIT_CONSTRUCTORS define
                          2. Code now compiles cleanly using Code Analysis (/analyze)
                          3. The code has now been updated to support VC 2005 or later only.
         PJN / 22-02-2015 1. Renamed CHttpDownloadDlg2 class to CHTTPDownloadDlg2
                          2. Updated the code to clean compile using /analyze 
         PJN / 16-01-2016 1. Updated copyright details.
                          2. Verified the code compiles cleanly in VC 2015
                          3. Added SAL annotations to all the code
         PJN / 24-12-2016 1. Updated code to use nullptr instead of NULL
         PJN / 19-09-2017 1. Updated copyright details.
                          2. Replaced CString::operator LPC*STR() calls throughout the codebase with CString::GetString
                          calls
         PJN / 28-12-2017 1. Updated the code to compile cleanly when _ATL_NO_AUTOMATIC_NAMESPACE is defined.
         PJN / 27-10-2018 1. Updated copyright details.
                          2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that
                          the code will now only compile on VC 2017 or later.
         PJN / 12-10-2019 1. Fixed a number of compiler warnings when the code is compiled with VS 2019 Preview
                          2. Reworked timing code to use GetTickCount64
         PJN / 16-01-2021 1. Updated copyright details.
                          2. Updated the code to use std::atomic for thread synchronisation.
                          3. General cleanup / review of the code

Copyright (c) 2006 - 2021 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////////////////// Includes /////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "HTTPDownloadDlg2.h"

#ifndef _CLIMITS_
#pragma message("To avoid this message, please put climits in your pre compiled header (normally stdafx.h)")
#include <climits>
#endif //#ifndef _CLIMITS_


//////////////////////////// Macros / Defines /////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

constexpr const UINT WM_HTTPDOWNLOAD_THREAD_FINISHED = WM_USER + 1;

//We need to extern define AfxParseURL here because including AFXINET.H causes clashes with WinHttp.h
extern BOOL AFXAPI AfxParseURL(LPCTSTR pstrURL, DWORD& dwServiceType,	CString& strServer, CString& strObject, INTERNET_PORT& nPort);


//////////////////////////// Implementation ///////////////////////////////////

#pragma warning(suppress: 26433 26440 26477)
IMPLEMENT_DYNAMIC(CHTTPDownloadDlg2, CDialog);

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CHTTPDownloadDlg2, CDialog) //NOLINT(modernize-avoid-c-arrays)
  ON_WM_DESTROY()
  ON_WM_CLOSE()
  ON_MESSAGE(WM_HTTPDOWNLOAD_THREAD_FINISHED, &CHTTPDownloadDlg2::OnThreadFinished)
END_MESSAGE_MAP()

#pragma warning(suppress: 26455)
CHTTPDownloadDlg2::CHTTPDownloadDlg2(_In_opt_ CWnd* pParent) : CDialog(CHTTPDownloadDlg2::IDD, pParent),
                                                               m_bSafeToClose(false),
                                                               m_pThread(nullptr),
                                                               m_nLastTotalBytes(0),
                                                               m_dwLastPercentage(UINT_MAX),
                                                               m_nLastProgressTicks(0),
                                                               m_nStartProgressTicks(0)
{
}

void CHTTPDownloadDlg2::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATUS, m_ctrlStatus);
  DDX_Control(pDX, IDC_TRANSFER_RATE, m_ctrlTransferRate);
  DDX_Control(pDX, IDC_TIMELEFT, m_ctrlTimeLeft);
  DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
  DDX_Control(pDX, IDC_FILESTATUS, m_ctrlFileStatus);
  DDX_Control(pDX, IDC_ANIMATE1, m_ctrlAnimate);
}

LRESULT CHTTPDownloadDlg2::OnThreadFinished(_In_ WPARAM /*wParam*/, _In_ LPARAM /*lParam*/)
{
  //It's now safe to close since the thread has signaled us
  m_bSafeToClose = true;

  //Stop the animation
  m_ctrlAnimate.Stop();

  //If an error occured display the message box
  if (Abort()) //No need to thread protect this because by design we can be sure that the worker thread will not be modifying this variable at this time
    EndDialog(IDCANCEL);
  else if (m_sError.GetLength())
  {
    AfxMessageBox(m_sError);
    EndDialog(IDCANCEL);
  }
  else
    EndDialog(IDOK);

  return 0L;
}

BOOL CHTTPDownloadDlg2::OnInitDialog()
{
  //Let the parent class do its thing
  __super::OnInitDialog();

  //Empty out the error string
  m_sError.Empty();

  //Reset the values we use for updating the progress
  m_dwLastPercentage = UINT_MAX;
  m_nLastTotalBytes = 0;

  //Setup the animation control
  m_ctrlAnimate.Open(IDR_HTTPDOWNLOAD_ANIMATION);

  //Check to see if the file we are downloading to exists and if
  //it does, then ask the user if they want it overwritten
  CFileStatus fs;
  ASSERT(m_sFileToDownloadInto.GetLength()); //NOLINT(clang-analyzer-core.CallAndMessage)
  const BOOL bDownloadFileExists = CFile::GetStatus(m_sFileToDownloadInto, fs);
  if (bDownloadFileExists && (m_nStartPos == 0) && m_bPromptFileOverwrite) //NOLINT(clang-analyzer-core.CallAndMessage)
  {
    CString sMsg;
    AfxFormatString1(sMsg, IDS_HTTPDOWNLOAD_OK_TO_OVERWRITE, m_sFileToDownloadInto);
    if (AfxMessageBox(sMsg, MB_YESNO) != IDYES)
    {
      TRACE(_T("CHTTPDownloadDlg2::OnInitDialog, Failed to confirm file overwrite, download aborted\n"));
      EndDialog(IDCANCEL);
      return TRUE;
    }
  }

  //Pull out just the filename part of the URL so that we can update the file status text
  INTERNET_PORT nPort = 0;
  CString sObject;
  CString sServer;
  if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, sServer, sObject, nPort)) //NOLINT(clang-analyzer-core.CallAndMessage)
  {
    //Try sticking "http://" before it
    m_sURLToDownload = _T("http://") + m_sURLToDownload;
    if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, sServer, sObject, nPort))
    {
      TRACE(_T("CHTTPDownloadDlg2::OnInitDialog, Failed to parse the URL: %s\n"), m_sURLToDownload.GetString());
      EndDialog(IDCANCEL);
      return TRUE;
    }
  }

  //Pull out just the filename component
  int nSlash = sObject.ReverseFind(_T('/'));
  if (nSlash == -1)
    nSlash = sObject.ReverseFind(_T('\\'));
  if (nSlash != -1 && sObject.GetLength() > 1)
    m_sFilename = sObject.Right(sObject.GetLength() - nSlash - 1);
  else
    m_sFilename = sObject;

  //Set the file status text
  CString sFileStatus;
  AfxFormatString2(sFileStatus, IDS_HTTPDOWNLOAD_FILESTATUS, m_sFilename, sServer);
  m_ctrlFileStatus.SetWindowText(sFileStatus);

  //Start the animation to signify that the download is taking place
#pragma warning(suppress: 26472)
  m_ctrlAnimate.Play(0, static_cast<UINT>(-1), static_cast<UINT>(-1));

  //Spin off the background thread which will do the actual downloading
  m_pThread = AfxBeginThread(_DownloadThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
  if (m_pThread == nullptr)
  {
    TRACE(_T("CHTTPDownloadDlg2::OnInitDialog, Failed to create download thread, dialog is aborting\n"));
    EndDialog(IDCANCEL);
    return TRUE;
  }
  m_pThread->m_bAutoDelete = FALSE;
  m_pThread->ResumeThread();

  return TRUE;
}

UINT CHTTPDownloadDlg2::_DownloadThread(_In_opt_ LPVOID pParam)
{
  //Convert from the SDK world to the C++ world
  auto pDlg = static_cast<CHTTPDownloadDlg2*>(pParam);
#pragma warning(suppress: 26496)
  AFXASSUME(pDlg != nullptr);
  ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CHTTPDownloadDlg2)));
  pDlg->DownloadThread();
  return 0;
}

void CHTTPDownloadDlg2::SetPercentage(_In_ int nPercentage)
{
  //Change the progress control
  m_ctrlProgress.SetPos(nPercentage);

  //Change the caption text
  CString sPercentage;
  sPercentage.Format(_T("%d"), nPercentage);
  CString sCaption;
  AfxFormatString2(sCaption, IDS_HTTPDOWNLOAD_PERCENTAGE, sPercentage, m_sFilename);
  SetWindowText(sCaption);
}

void CHTTPDownloadDlg2::SetTimeLeft(_In_ DWORD dwSecondsLeft, _In_ ULONGLONG nBytesRead, _In_ ULONGLONG nFileSize)
{
  CString sCopied;
  if (nBytesRead < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%I64u"), nBytesRead);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (nBytesRead < 1048576)
  {
    CString sKiloBytes;
#pragma warning(suppress: 26472)
    sKiloBytes.Format(_T("%0.1f"), static_cast<LONGLONG>(nBytesRead)/1024.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
#pragma warning(suppress: 26472)
    sMegaBytes.Format(_T("%0.2f"), static_cast<LONGLONG>(nBytesRead)/1048576.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_MEGABYTES, sMegaBytes);
  }

  CString sTotal;
  if (nFileSize < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%I64u"), nFileSize);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (nFileSize < 1048576)
  {
    CString sKiloBytes;
#pragma warning(suppress: 26472)
    sKiloBytes.Format(_T("%0.1f"), static_cast<LONGLONG>(nFileSize)/1024.0);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
#pragma warning(suppress: 26472)
    sMegaBytes.Format(_T("%0.2f"), static_cast<LONGLONG>(nFileSize)/1048576.0);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_MEGABYTES, sMegaBytes);
  }

  CString sOf;
  AfxFormatString2(sOf, IDS_HTTPDOWNLOAD_OF, sCopied, sTotal);

  CString sTime;
  if (dwSecondsLeft < 60)
  {
    CString sSeconds;
    sSeconds.Format(_T("%u"), dwSecondsLeft);
    AfxFormatString1(sTime, IDS_HTTPDOWNLOAD_SECONDS, sSeconds);
  }
  else
  {
    const DWORD dwMinutes = dwSecondsLeft / 60;
    const DWORD dwSeconds = dwSecondsLeft % 60;
    CString sSeconds;
    sSeconds.Format(_T("%u"), dwSeconds);
    CString sMinutes;
    sMinutes.Format(_T("%u"), dwMinutes);
    if (dwSeconds == 0)
      AfxFormatString1(sTime, IDS_HTTPDOWNLOAD_MINUTES, sMinutes);
    else
      AfxFormatString2(sTime, IDS_HTTPDOWNLOAD_MINUTES_AND_SECONDS, sMinutes, sSeconds);
  }

  CString sTimeLeft;
  AfxFormatString2(sTimeLeft, IDS_HTTPDOWNLOAD_TIMELEFT, sTime, sOf);
  m_ctrlTimeLeft.SetWindowText(sTimeLeft);
}

void CHTTPDownloadDlg2::SetTransferRate(_In_ double KbPerSecond)
{
  CString sRate;
  if (KbPerSecond < 1)
  {
    CString sBytesPerSecond;
    sBytesPerSecond.Format(_T("%0.0f"), KbPerSecond*1024);
    AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_BYTESPERSECOND, sBytesPerSecond);
  }
  else if (KbPerSecond < 10)
  {
    CString sKiloBytesPerSecond;
    sKiloBytesPerSecond.Format(_T("%0.2f"), KbPerSecond);
    AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
  }
  else
  {
    CString sKiloBytesPerSecond;
    sKiloBytesPerSecond.Format(_T("%0.0f"), KbPerSecond);
    AfxFormatString1(sRate, IDS_HTTPDOWNLOAD_KILOBYTESPERSECOND, sKiloBytesPerSecond);
  }
  m_ctrlTransferRate.SetWindowText(sRate);
}

void CHTTPDownloadDlg2::DownloadThread()
{
  //Call the function which does the heavy lifting
  Download();

  //We're finished
  PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
}

#pragma warning(suppress: 26434)
void CHTTPDownloadDlg2::OnDestroy()
{
  //Wait for the worker thread to exit
  if (m_pThread != nullptr)
  {
    WaitForSingleObject(m_pThread->m_hThread, INFINITE);
    delete m_pThread;
    m_pThread = nullptr;
  }

  //Let the parent class do its thing
  __super::OnDestroy();
}

void CHTTPDownloadDlg2::OnCancel()
{
  //Just set the abort flag and disable the cancel button
  SetAbort();
  GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
  __super::SetStatus(IDS_HTTPDOWNLOAD_ABORTING_TRANSFER);
}

#pragma warning(suppress: 26434)
void CHTTPDownloadDlg2::OnClose()
{
  if (m_bSafeToClose)
    __super::OnClose();
  else
  {
    //Just set the abort flag and disable the cancel button
    SetAbort();
    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    __super::SetStatus(IDS_HTTPDOWNLOAD_ABORTING_TRANSFER);
  }
}

void CHTTPDownloadDlg2::SetStatus(_In_z_ LPCTSTR pszStatus)
{
  //For debugging purposes also run CHttpDownloader2::SetStatus
  __super::SetStatus(pszStatus);

  //Simply update the static controls text
  m_ctrlStatus.SetWindowText(pszStatus);
}

void CHTTPDownloadDlg2::HandleError(_In_ UINT nID, _In_ DWORD dwError)
{
  //For debugging purposes also run CHttpDownloader2::HandleError
  __super::HandleError(nID, dwError);

  //Form the error string to report
  CString sError;
  if (dwError)
    sError = GetErrorMessage(dwError);
  else
    sError = GetErrorMessage(GetLastError());
  AfxFormatString1(m_sError, nID, sError);
}

void CHTTPDownloadDlg2::HandleStatusCode(_In_ UINT nID, _In_ DWORD dwStatusCode)
{
  //For debugging purposes also run CHttpDownloader2::HandleError
  __super::HandleStatusCode(nID, dwStatusCode);

  //Form the error string to report
  CString sError;
  sError.Format(_T("%u"), dwStatusCode);
  AfxFormatString1(m_sError, nID, sError);
}

void CHTTPDownloadDlg2::OnProgress(_In_ ULONGLONG nTotalBytesRead, _In_ bool bGotFileSize, _In_ ULONGLONG nFileSize)
{
  //For debugging purposes also run CHttpDownloader2::OnProgress
  __super::OnProgress(nTotalBytesRead, bGotFileSize, nFileSize);

  if (m_dwLastPercentage == UINT_MAX) //Is this the first time we have been called for this download
  {
    m_nStartProgressTicks = GetTickCount64();
    m_nLastProgressTicks = m_nStartProgressTicks;
  }

  if (bGotFileSize)
  {
    //Update the percentage downloaded in the caption
#pragma warning(suppress: 26472)
    const auto dwPercentage = static_cast<DWORD>((nTotalBytesRead + m_nStartPos) * 100 / nFileSize);
    if (dwPercentage != m_dwLastPercentage)
    {
      //Update the progress control bar
      SetPercentage(dwPercentage);
      m_dwLastPercentage = dwPercentage;
    }
  }

  //Update the transfer rate amd estimated time left every second
  const ULONGLONG nCurrentTickCount = GetTickCount64();
  const __int64 nTimeTaken = nCurrentTickCount - m_nLastProgressTicks;
  if (nTimeTaken > 1000) //By default, only update the transfer rate and time left every second
  {
    //Update the transfer rate
#pragma warning(suppress: 26472)
    const double KbPerSecond = (static_cast<double>(static_cast<LONGLONG>(nTotalBytesRead)) - static_cast<double>(static_cast<LONGLONG>(m_nLastTotalBytes))) / (static_cast<double>(nTimeTaken));
    SetTransferRate(KbPerSecond);

    //Setup for the next time around the loop
    m_nLastProgressTicks = nCurrentTickCount;
    m_nLastTotalBytes = nTotalBytesRead;

    //Update the time remaining if we have got a file size
    if (bGotFileSize)
    {
      //Update the estimated time left if we have downloaded something so far and we have not downloaded everything
      if (nTotalBytesRead)
      {
#pragma warning(suppress: 26472)
        const auto dwSecondsLeft = static_cast<DWORD>(static_cast<double>(nCurrentTickCount - m_nStartProgressTicks) 
                                     / static_cast<double>(static_cast<LONGLONG>(nTotalBytesRead)) * (static_cast<LONGLONG>(nFileSize - m_nStartPos) - static_cast<double>(static_cast<LONGLONG>(nTotalBytesRead))) / 1000);
        SetTimeLeft(dwSecondsLeft, nTotalBytesRead + m_nStartPos, nFileSize);
      }
    }
  }
}

void CHTTPDownloadDlg2::OnWinHttpStatusCallBack(_In_ HINTERNET /*hInternet*/, _In_ DWORD dwInternetStatus, _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD /*dwStatusInformationLength*/)
{
  switch (dwInternetStatus)
  {
    case WINHTTP_CALLBACK_STATUS_RESOLVING_NAME:
    {
      //Just delegate back up to the base class to update the status text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      __super::SetStatus(IDS_HTTPDOWNLOAD_RESOLVING_NAME, CString(static_cast<LPWSTR>(lpvStatusInformation)));
      break;
    }
    case WINHTTP_CALLBACK_STATUS_NAME_RESOLVED:
    {
      //Just delegate back up to the base class to update the status text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      __super::SetStatus(IDS_HTTPDOWNLOAD_RESOLVED_NAME, CString(static_cast<LPWSTR>(lpvStatusInformation)));
      break;
    }
    case WINHTTP_CALLBACK_STATUS_CONNECTING_TO_SERVER:
    {
      //Just delegate back up to the base class to update the status text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      __super::SetStatus(IDS_HTTPDOWNLOAD_CONNECTING, CString(static_cast<LPWSTR>(lpvStatusInformation)));
      break;
    }
    case WINHTTP_CALLBACK_STATUS_CONNECTED_TO_SERVER:
    {
      //Just delegate back up to the base class to update the status text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      __super::SetStatus(IDS_HTTPDOWNLOAD_CONNECTED, CString(static_cast<LPWSTR>(lpvStatusInformation)));
      break;
    }
    case WINHTTP_CALLBACK_STATUS_REDIRECT:
    {
      //Just delegate back up to the base class to update the status text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      __super::SetStatus(IDS_HTTPDOWNLOAD_REDIRECTING, CString(static_cast<LPWSTR>(lpvStatusInformation)));
      break;
    }
    default:
    {
      break;
    }
  }
}

void CHTTPDownloadDlg2::OnGotContentLength(_In_ ULONGLONG nContentLength)
{
  //For debugging purposes also run CHttpDownloader2::OnGotContentLength
  __super::OnGotContentLength(nContentLength);

  //Set up the progress control now that we have Content-Length value
  m_ctrlProgress.SetRange(0, 100);
}
