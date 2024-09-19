/*
Module : HTTPDownloadDlg.h
Purpose: Defines the interface for an MFC dialog which performs HTTP downloads
         similiar to the Internet Explorer download dialog using Wininet

Copyright (c) 1999 - 2021 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////// Macros ////////////////////////////////////////////

#pragma once

#ifndef __HTTPDOWNLOADDLG_H__
#define __HTTPDOWNLOADDLG_H__

#ifndef CHTTPDOWNLOADDLG_EXT_CLASS
#define CHTTPDOWNLOADDLG_EXT_CLASS
#endif //#ifndef CHTTPDOWNLOADDLG_EXT_CLASS


/////////////////////////// Includes //////////////////////////////////////////

#ifndef __HTTPDOWNLOADDER_H__
#include "HTTPDownloader.h"
#endif //#ifndef __HTTPDOWNLOADDER_H__


/////////////////////////// Classes ///////////////////////////////////////////

//The dialog class which does the HTTP downloading

class CHTTPDOWNLOADDLG_EXT_CLASS CHTTPDownloadDlg : public CDialog,
                                                    public CHTTPDownloader
{
public:
//Constructors / Destructors
  CHTTPDownloadDlg(_In_opt_ CWnd* pParent = nullptr);

protected:
//Member variables
  enum { IDD = IDD_HTTPDOWNLOAD };
  CStatic m_ctrlStatus;
  CStatic m_ctrlTransferRate;
  CStatic m_ctrlTimeLeft;
  CProgressCtrl m_ctrlProgress;
  CStatic m_ctrlFileStatus;
  CAnimateCtrl m_ctrlAnimate;
  CString m_sFilename;
  CString m_sError;
  bool m_bSafeToClose;
  CWinThread* m_pThread;
  ULONGLONG m_nLastTotalBytes;
  DWORD m_dwLastPercentage;
  ULONGLONG m_nLastProgressTicks;
  ULONGLONG m_nStartProgressTicks;

//Methods
  void DoDataExchange(CDataExchange* pDX) override;
  BOOL OnInitDialog() override;
  void OnCancel() override;
  void OnWininetStatusCallBack(_In_ HINTERNET hInternet, _In_ DWORD dwInternetStatus, _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD dwStatusInformationLength) override;
  virtual void DownloadThread();
  void HandleError(_In_ UINT nID, _In_ DWORD dwError) override;
  void HandleStatusCode(_In_ UINT nID, _In_ DWORD dwStatusCode) override;
  void OnProgress(_In_ ULONGLONG nBytesRead, _In_ bool bGotFileSize, _In_ ULONGLONG nFileSize) override;
  virtual void SetPercentage(_In_ int nPercentage);
  virtual void SetTimeLeft(_In_ DWORD dwSecondsLeft, _In_ ULONGLONG nBytesRead, _In_ ULONGLONG nFileSize);
  void SetStatus(_In_z_ LPCTSTR pszStatus) override;
  virtual void SetTransferRate(_In_ double KbPerSecond);
  bool DoCertificateSelection() override;
  bool HandlePrompt(_Inout_ DWORD& dwError) override;
  void OnGotContentLength(_In_ ULONGLONG nContentLength) override;
  static UINT _DownloadThread(_In_opt_ LPVOID pParam);

//Mesage handlers
  afx_msg void OnDestroy();
  afx_msg void OnClose();
  afx_msg LRESULT OnThreadFinished(_In_ WPARAM wParam, _In_ LPARAM lParam);

  DECLARE_MESSAGE_MAP()

  DECLARE_DYNAMIC(CHTTPDownloadDlg);
};

#endif //#ifndef __HTTPDOWNLOADDER_H__
