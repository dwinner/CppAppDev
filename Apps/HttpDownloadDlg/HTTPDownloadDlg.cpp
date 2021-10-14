/*
Module : HTTPDownloadDlg.cpp
Purpose: Defines the implementation for an MFC dialog which performs HTTP downloads
         similiar to the Internet Explorer download dialog using Wininet
Created: PJN / 14-11-1999
History: PJN / 25-01-2000 1. Fixed a problem where server authentication was not being detected correctly,
                          while proxy authentication was being handled.
                          2. Updated the way and periodicity certain UI controls are updated during the 
                          HTTP download
         PJN / 12-06-2000 1. Now fully supports HTTPS downloads.
         PJN / 02-07-2000 1. Now supports resuming downloads
         PJN / 28-04-2001 1. Updated Copyright Information
                          2. You need to have the Latest Wininet header files installed to compile the code. This 
                          will not be the case with VC 5, which you will also have to install the plaform SDK also.
                          2. Now includes support for the following fields:
                             m_sProxyUserName: You can now specify the Proxy user details
                             m_sProxyPassword: THe Proxy password to use
                             m_ConnectionType: You can now specify the HTTP connection type
                             m_bPromptFileOverwrite: Should you be prompted for file overwrites
                             m_bPromptForProxyDetails: Should you be prompted for Proxy authentication
                             m_bPromptForHTTPDetails: Should you be prompted for HTTP authentication
                             m_sUserAgent: The User Agent value to use in HTTP requests
                          3. Fixed a problem in downloading files using HTTPS
                          4. Provided a OnSetOptions method to allow customisation through deriving your own
                          class from CHttpDownloadDlg
         PJN / 17-06-2001 1. Now provides Bandwidth throtling support. Thanks to Karim Mribti for
                          this good addition.
                          2. Code now uses InternetReadFile instead of InternetReadFileEx as InternetReadFileEx
                          is not implemented under Unicode.
         PJN / 10-10-2001 1. Fixed a problem where old style MFC exception handling was being used
                          instead of C++ standard.
                          2. Code is now independent of Platform SDK meaning that it can compile on VC 5 without
                          need for having the Platform SDK installed.
         PJN / 03-12-2001 1. Tidied up support for resumed downloads
         PJN / 02-02-2002 1. Fixed a bug where the local downloaded file would get appended to even when you are
                             not resuming the download. Thanks to Davide Zaccanti for spotting this problem.
                          2. Updated documentation to include explicit requirements for the class.
         PJN / 20-04-2002 1. Fixed bug in call to AfxBeginThread. Thanks to mark anderson for spotting this 
                          problem.
                          2. Fixed a redraw glitch where the progress control was being updated twice instead of
                          once each time for each percentage. Again thanks to Mark Anderson for spotting this
                          problem.
         PJN / 30-10-2002 1. Fixed a problem with seeking to the correct position when resuming a download. Thanks
                          to Liping Dai for this bug report.
         PJN / 06-01-2003 1. Fixed a bug where using HTTPS on a non standard port would cause the download to fail.
                          Thanks to "Sundar" for spotting this problem
                          2. Fixed a bug in the displaying of errors which use the strings 
                          "IDS_HTTPDOWNLOAD_INVALID_SERVER_RESPONSE" and "IDS_HTTPDOWNLOAD_INVALID_SERVER_RESPONSE"
         PJN / 19-01-2003 1. Fixed a bug in calling InternetReadFile when doing proxy authentication which could 
                          have resulted in an infinite loop occurring. Thanks to Nathan Lewis for reporting this.
                          2. Reworked the code which queries for the HTTP status code to use the HTTP_QUERY_FLAG_NUMBER
                          flag in the call to HttpQueryInfo. Again thanks to Nathan Lewis for suggesting this.
                          3. Reworked the code which queries for the HTTP content length code to use the 
                          HTTP_QUERY_FLAG_NUMBER flag in the call to HttpQueryInfo. Again thanks to Nathan Lewis 
                          for suggesting this.
         PJN / 29-06-2003 1. The progress control now uses a range of 0 - 100 percent rather than the actual file size. 
                          This prevents overflow with the SetRange method. I could use SetRange32, but then the class
                          would depend on having an updated version of the common control dll installed.
                          2. Fixed a problem in OnStatusCallBack when compiled for Unicode
         PJN / 05-02-2004 1. Updated the way the progress control is displayed when a resumed download is performed.
                          Thanks to David C. Hochrein for reporting this addition.
         PJN / 12-02-2004 1. Class now automatically pulls in wininet.lib support via a #pragma. This means that client
                          apps no longer need to update the linker settings.
         PJN / 11-11-2004 1. Fixed an issue in the code where the request is only reissued when authentication errors 
                          occur and the code needs to prompt the user. Thanks to Thomas Kiesswetter for reporting
                          this problem and provided the fix.
                          2. Addition of a CHTTPDOWNLOADDLG_EXT_CLASS preprocessor macro which allows the class
                          to be easily added to an extension dll
                          3. Fixed a bug when errors are displayed when QueryStatusCode fails.
         PJN / 05-03-2005 1. Tidied up the way the file to be downloaded is closed and deleted if the download 
                          fails. Thanks to Guillermo for reporting this bug.
                          2. Fixed a bug in the main logic of the class which caused the http or proxy credentials
                          dialog to be continually displayed even when you hit cancel. Thanks to Guillermo for 
                          reporting this bug and providing the fix.
                          3. Optimized the code which calls GetLastError.
                          4. Display of error messages now uses FormatMessage to display a more friendlier
                          value.
         PJN / 04-04-2005 1. Fix for bug when providing all information in the dialog for both proxy and user
                          validation and one uses the option to connect directly via the proxy and no prompting is checked 
                          then when the code 407 is received the code resends with proxy info and gets a 401 code. This time 
                          it reports the error as the bool flag for bRetrying is true. Thanks to Stephen Miller 
                          for providing the fix for this problem.
         PJN / 08-05-2006 1. Updated copyright details.
                          2. Fixed an ASSERT in CHttpDownloadDlg::OnThreadFinished when you cancel a download prematurely.
                          3. Updated the documentation to use the same style as the web site.
                          4. Did a spell check of the documentation.
                          5. Addition of a m_bNoURLRedirect variable so that the class can optionally ignore 302 redirects.
                          6. The flags passed to HttpOpenRequest can now be customized via a new method GetOpenRequestFlags
                          7. Optimized creation of member variables in CHttpDownloadDlg constructor.
                          8. Updated various captions and version infos in the sample app
                          9. Fixed a number of compiler warnings when the code is compiled using /Wp64. Please note that 
                          to implement these fixes, the code will now require the Platform SDK to be installed if you 
                          compile the code on VC 6.
         PJN / 02-07-2006 1. Updated the code to clean compile on VC 2005     
                          2. Code now uses new C++ style casts rather than old style C casts where necessary.     
                          3. The class now requires the Platform SDK if compiled using VC 6.
         PJN / 14-07-2006 1. Fixed some issues in OnStatusCallback when the code is compiled for Unicode. Thanks to 
                          Itamar Syn-Hershko for reporting this issue.
                          2. WM_HTTPDOWNLOAD_THREAD_FINISHED now uses WM_USER instead of WM_APP to define its value
                          3. Major refactoring of the code into 3 classes namely CHttpDownloadSettings, CHttpDownloader
                          and the existing CHttpDownloadDlg class which has been significantly reworked to fit in with
                          this new layout. The new layout means that you can use the new "CHttpDownloader" class in a 
                          synchronous manner without any UI at all. For example to download a file without any UI you 
                          would just use something like:
                          
                          CHttpDownloader downloader;
                          downloader.m_Settings.m_sURLToDownload = _T("http://www.some-site.com/somefile.ext");
                          downloader.m_Settings.m_sFileToDownloadInto = _T("c:\\somefile.ext");
                          downloader.Download();

                          When the Download() function returns the file will have been downloaded successfully or
                          will have failed to download. Various synchronous virtual functions can be overridden
                          to handle the various events as they occur during the download. The CHttpDownloadDlg class
                          now derives from both CDialog and CHttpDownloader, and handles these virtual events to provide 
                          the existing functionality which it had. You should review how CHttpDownloadDlg handles these 
                          virtual functions if you want to create your own customized implementation which derives from 
                          CHttpDownloader.

                          4. Fixed a spelling mistake in the IDS_HTTPDOWNLOAD_RETREIVEING_FILE string
                          5. The buffer size used in calls to InternetReadFile can now be changed via 
                          CHttpDownloadSettings::m_dwReadBufferSize
                          6. Thread protected changes to the Abort flag
         PJN / 17-09-2006 1. Fixed an issue where the OnStatusCallback method was not being called. This has been addressed
                          by renaming the function to OnWininetStatusCallBack. This is necessary due to the refactoring
                          of the base CHttpDownloader class. Thanks to Johan Sörensen for reporting this bug
         PJN / 09-06-2007 1. Updated copyright messages.
                          2. Updated CHttpDownloadDlg::OnWininetStatusCallBack in line with CFTPTransferer class.
         PJN / 11-05-2008 1. Updated copyright messages.
                          2. Updated the logic in CHttpDownloadDlg::OnWininetStatusCallBack to correctly handle ASCII or 
                          Unicode strings. Thanks to Hans Dietrich for prompting this update.
                          3. OnProgress virtual methods now correctly handles reporting results for resumed downloads
         PJN / 22-02-2015 1. Renamed CHttpDownloadDlg class to CHTTPDownloadDlg
                          2. Updated the code to clean compile using /analyze
         PJN / 16-01-2016 1. Updated copyright details.
                          2. Verified the code compiles cleanly in VC 2015
                          3. Added SAL annotations to all the code
         PJN / 24-12-2016 1. Updated code to use nullptr instead of NULL
         PJN / 19-09-2017 1. Updated copyright details.
                          2. Replaced CString::operator LPC*STR() calls throughout the codebase with CString::GetString 
                          calls
         PJN / 27-10-2018 1. Updated copyright details.
                          2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that
                          the code will now only compile on VC 2017 or later.
         PJN / 12-10-2019 1. Fixed a number of compiler warnings when the code is compiled with VS 2019 Preview
                          2. Reworked timing code to use GetTickCount64
         PJN / 16-01-2021 1. Updated copyright details.
                          2. Updated the code to use std::atomic for thread synchronisation.
                          3. General cleanup / review of the code

Copyright (c) 1999 - 2021 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

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
#include "HTTPDownloadDlg.h"

#ifndef _CLIMITS_
#pragma message("To avoid this message, please put climits in your pre compiled header (normally stdafx.h)")
#include <climits>
#endif //#ifndef _CLIMITS_


//////////////////////////// Macros / Defines /////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

constexpr const UINT WM_HTTPDOWNLOAD_THREAD_FINISHED = WM_USER + 1;


//////////////////////////// Implementation ///////////////////////////////////

#pragma warning(suppress: 26433 26440 26477)
IMPLEMENT_DYNAMIC(CHTTPDownloadDlg, CDialog);

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CHTTPDownloadDlg, CDialog) //NOLINT(modernize-avoid-c-arrays)
  ON_WM_DESTROY()
  ON_WM_CLOSE()
  ON_MESSAGE(WM_HTTPDOWNLOAD_THREAD_FINISHED, &CHTTPDownloadDlg::OnThreadFinished)
END_MESSAGE_MAP()

#pragma warning(suppress: 26455)
CHTTPDownloadDlg::CHTTPDownloadDlg(_In_opt_ CWnd* pParent) : CDialog(CHTTPDownloadDlg::IDD, pParent),
                                                             m_bSafeToClose(false),
                                                             m_pThread(nullptr),
                                                             m_nLastTotalBytes(0),
                                                             m_dwLastPercentage(UINT_MAX),
                                                             m_nLastProgressTicks(0),
                                                             m_nStartProgressTicks(0)
{
}

void CHTTPDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATUS, m_ctrlStatus);
  DDX_Control(pDX, IDC_TRANSFER_RATE, m_ctrlTransferRate);
  DDX_Control(pDX, IDC_TIMELEFT, m_ctrlTimeLeft);
  DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
  DDX_Control(pDX, IDC_FILESTATUS, m_ctrlFileStatus);
  DDX_Control(pDX, IDC_ANIMATE1, m_ctrlAnimate);
}

LRESULT CHTTPDownloadDlg::OnThreadFinished(_In_ WPARAM /*wParam*/, _In_ LPARAM /*lParam*/)
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

BOOL CHTTPDownloadDlg::OnInitDialog()
{
  //Let the parent class do its thing
  __super::OnInitDialog();

  //Empty out the error string
  m_sError.Empty();

  //Reset the values we use for updating the progress
#pragma warning(suppress: 26472)
  m_dwLastPercentage = static_cast<DWORD>(-1);
  m_nLastTotalBytes = 0;

  //Setup the animation control
  m_ctrlAnimate.Open(IDR_HTTPDOWNLOAD_ANIMATION);

  //Check to see if the file we are downloading to exists and if
  //it does, then ask the user if they want it overwritten
  CFileStatus fs;
  ASSERT(m_sFileToDownloadInto.GetLength());
  const bool bDownloadFileExists = CFile::GetStatus(m_sFileToDownloadInto, fs) ? true : false;
  if (bDownloadFileExists && m_nStartPos == 0 && m_bPromptFileOverwrite)
  {
    CString sMsg;
    AfxFormatString1(sMsg, IDS_HTTPDOWNLOAD_OK_TO_OVERWRITE, m_sFileToDownloadInto);
    if (AfxMessageBox(sMsg, MB_YESNO) != IDYES)
    {
      TRACE(_T("CHTTPDownloadDlg::OnInitDialog, Failed to confirm file overwrite, download aborted\n"));
      EndDialog(IDCANCEL);
      return TRUE;
    }
  }
  
  //Pull out just the filename part of the URL so that we can update the file status text
  INTERNET_PORT nPort = 0;
  CString sObject;
  CString sServer;
  if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, sServer, sObject, nPort))
  {
    //Try sticking "http://" before it
    m_sURLToDownload = _T("http://") + m_sURLToDownload;
    if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, sServer, sObject, nPort))
    {
      TRACE(_T("CHTTPDownloadDlg::OnInitDialog, Failed to parse the URL: %s\n"), m_sURLToDownload.GetString());
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
    TRACE(_T("CHTTPDownloadDlg::OnInitDialog, Failed to create download thread, dialog is aborting\n"));
    EndDialog(IDCANCEL);
    return TRUE;
  }
  m_pThread->m_bAutoDelete = FALSE;
  m_pThread->ResumeThread();

  return TRUE;
}

UINT CHTTPDownloadDlg::_DownloadThread(_In_opt_ LPVOID pParam)
{
  //Convert from the SDK world to the C++ world
  auto pDlg = static_cast<CHTTPDownloadDlg*>(pParam);
#pragma warning(suppress: 26496)
  AFXASSUME(pDlg != nullptr);
  ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CHTTPDownloadDlg)));
  pDlg->DownloadThread();
  return 0;
}

void CHTTPDownloadDlg::SetPercentage(_In_ int nPercentage)
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

void CHTTPDownloadDlg::SetTimeLeft(_In_ DWORD dwSecondsLeft, _In_ ULONGLONG dwBytesRead, _In_ ULONGLONG dwFileSize)
{
  CString sCopied;
  if (dwBytesRead < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%I64u"), dwBytesRead);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (dwBytesRead < 1048576)
  {
    CString sKiloBytes;
#pragma warning(suppress: 26472)
    sKiloBytes.Format(_T("%0.1f"), static_cast<LONGLONG>(dwBytesRead)/1024.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
#pragma warning(suppress: 26472)
    sMegaBytes.Format(_T("%0.2f"), static_cast<LONGLONG>(dwBytesRead)/1048576.0);
    AfxFormatString1(sCopied, IDS_HTTPDOWNLOAD_MEGABYTES, sMegaBytes);
  }

  CString sTotal;
  if (dwFileSize < 1024)
  {
    CString sBytes;
    sBytes.Format(_T("%I64u"), dwFileSize);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_BYTES, sBytes);
  }
  else if (dwFileSize < 1048576)
  {
    CString sKiloBytes;
#pragma warning(suppress: 26472)
    sKiloBytes.Format(_T("%0.1f"), static_cast<LONGLONG>(dwFileSize)/1024.0);
    AfxFormatString1(sTotal, IDS_HTTPDOWNLOAD_KILOBYTES, sKiloBytes);
  }
  else
  {
    CString sMegaBytes;
#pragma warning(suppress: 26472)
    sMegaBytes.Format(_T("%0.2f"), static_cast<LONGLONG>(dwFileSize)/1048576.0);
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

void CHTTPDownloadDlg::SetTransferRate(_In_ double KbPerSecond)
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

void CHTTPDownloadDlg::DownloadThread()
{
  //Call the function which does the heavy lifting
  Download();

  //We're finished
  PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
}

#pragma warning(suppress: 26434)
void CHTTPDownloadDlg::OnDestroy()
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

void CHTTPDownloadDlg::OnCancel()
{
  //Just set the abort flag and disable the cancel button
  SetAbort();
  GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
  __super::SetStatus(IDS_HTTPDOWNLOAD_ABORTING_TRANSFER);
}

#pragma warning(suppress: 26434)
void CHTTPDownloadDlg::OnClose()
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

void CHTTPDownloadDlg::SetStatus(_In_z_ LPCTSTR pszStatus)
{
  //For debugging purposes also run CHttpDownloader::SetStatus
  __super::SetStatus(pszStatus);

  //Simply update the static controls text
  m_ctrlStatus.SetWindowText(pszStatus);
}

void CHTTPDownloadDlg::HandleError(_In_ UINT nID, _In_ DWORD dwError)
{
  //For debugging purposes also run CHttpDownloader::HandleError
  __super::HandleError(nID, dwError);

  //Form the error string to report
  CString sError;
  if (dwError)
    sError = GetErrorMessage(dwError);
  else
    sError = GetErrorMessage(GetLastError());
  AfxFormatString1(m_sError, nID, sError);
}

void CHTTPDownloadDlg::HandleStatusCode(_In_ UINT nID, _In_ DWORD dwStatusCode)
{
  //For debugging purposes also run CHttpDownloader::HandleError
  __super::HandleStatusCode(nID, dwStatusCode);

  //Form the error string to report
  CString sError;
  sError.Format(_T("%u"), dwStatusCode);
  AfxFormatString1(m_sError, nID, sError);
}

void CHTTPDownloadDlg::OnProgress(_In_ ULONGLONG nTotalBytesRead, _In_ bool bGotFileSize, _In_ ULONGLONG nFileSize)
{
  //For debugging purposes also run CHttpDownloader::OnProgress
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

void CHTTPDownloadDlg::OnWininetStatusCallBack(_In_ HINTERNET /*hInternet*/, _In_ DWORD dwInternetStatus, _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD dwStatusInformationLength)
{
  //Note the MSDN documentation has very poor information on what the lpStatusInformation parameter actually contains for various callbacks. Some users of 
  //the class has reported that it reports a LPTSTR for string type information, but the author has seen it return a LPSTR even for Unicode builds. As a 
  //defense in depth approach against this uncertainty, lets determine at runtime what type of string we have. Perhaps I will check with MS support to get
  //a definitive answer on this. For more info on this, check out http://groups.google.com/group/microsoft.public.inetsdk.programming.wininet/browse_thread/thread/e75e20aa425cfb16/a569b0026815bc98
  switch (dwInternetStatus)
  {
    case INTERNET_STATUS_RESOLVING_NAME:
    {
      //Determine if it is ASCII or Unicode text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      const BOOL bUnicodeText = IsTextUnicode(lpvStatusInformation, dwStatusInformationLength, nullptr);

      //Just delegate back up to the base class to update the status text
      __super::SetStatus(IDS_HTTPDOWNLOAD_RESOLVING_NAME, bUnicodeText ? CString(static_cast<LPWSTR>(lpvStatusInformation)) : CString(static_cast<LPSTR>(lpvStatusInformation)));
      break;
    }
    case INTERNET_STATUS_NAME_RESOLVED:
    {
      //Determine if it is ASCII or Unicode text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      const BOOL bUnicodeText = IsTextUnicode(lpvStatusInformation, dwStatusInformationLength, nullptr);

      //Just delegate back up to the base class to update the status text
      __super::SetStatus(IDS_HTTPDOWNLOAD_RESOLVED_NAME, bUnicodeText ? CString(static_cast<LPWSTR>(lpvStatusInformation)) : CString(static_cast<LPSTR>(lpvStatusInformation)));
      break;
    }
    case INTERNET_STATUS_CONNECTING_TO_SERVER:
    {
      //Determine if it is ASCII or Unicode text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      const BOOL bUnicodeText = IsTextUnicode(lpvStatusInformation, dwStatusInformationLength, nullptr);

      //Just delegate back up to the base class to update the status text
      __super::SetStatus(IDS_HTTPDOWNLOAD_CONNECTING, bUnicodeText ? CString(static_cast<LPWSTR>(lpvStatusInformation)) : CString(static_cast<LPSTR>(lpvStatusInformation)));
      break;
    }
    case INTERNET_STATUS_CONNECTED_TO_SERVER:
    {
      //Determine if it is ASCII or Unicode text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      const BOOL bUnicodeText = IsTextUnicode(lpvStatusInformation, dwStatusInformationLength, nullptr);

      //Just delegate back up to the base class to update the status text
      __super::SetStatus(IDS_HTTPDOWNLOAD_CONNECTED, bUnicodeText ? CString(static_cast<LPWSTR>(lpvStatusInformation)) : CString(static_cast<LPSTR>(lpvStatusInformation)));
      break;
    }
    case INTERNET_STATUS_REDIRECT:
    {
      //Determine if it is ASCII or Unicode text
#pragma warning(suppress: 26496)
      AFXASSUME(lpvStatusInformation != nullptr);
      const BOOL bUnicodeText = IsTextUnicode(lpvStatusInformation, dwStatusInformationLength, nullptr);

      //Just delegate back up to the base class to update the status text
      __super::SetStatus(IDS_HTTPDOWNLOAD_REDIRECTING, bUnicodeText ? CString(static_cast<LPWSTR>(lpvStatusInformation)) : CString(static_cast<LPSTR>(lpvStatusInformation)));
      break;
    }
    default:
    {
      break;
    }
  }
}

bool CHTTPDownloadDlg::DoCertificateSelection()
{
  const DWORD dwResult = InternetErrorDlg(GetSafeHwnd(), m_hHttpFile, ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED, 
                                          FLAGS_ERROR_UI_FILTER_FOR_ERRORS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
                                          FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, nullptr);
  return (dwResult == ERROR_INTERNET_FORCE_RETRY) || (dwResult == ERROR_SUCCESS);
}

bool CHTTPDownloadDlg::HandlePrompt(_Inout_ DWORD& dwError)
{
  //Bring up the standard authentication dialog if required
  dwError = InternetErrorDlg(GetSafeHwnd(), m_hHttpFile, ERROR_INTERNET_INCORRECT_PASSWORD, 
                             FLAGS_ERROR_UI_FILTER_FOR_ERRORS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, nullptr);

  //Did the user wish to cancel?
  if (dwError == ERROR_SUCCESS)
    SetAbort();

  //Indicate to the caller what action to take
  return (dwError == ERROR_INTERNET_FORCE_RETRY);
}

void CHTTPDownloadDlg::OnGotContentLength(_In_ ULONGLONG dwContentLength)
{
  //For debugging purposes also run CHttpDownloader::OnGotContentLength
  __super::OnGotContentLength(dwContentLength);

  //Set up the progress control now that we have Content-Length value
  m_ctrlProgress.SetRange(0, 100);
}
