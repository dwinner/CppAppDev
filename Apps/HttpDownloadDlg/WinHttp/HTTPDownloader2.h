/*
Module : HTTPDownloader2.h
Purpose: Defines the interface for an MFC class which provides a wrapping for downloading HTTP requests in a 
         synchronous manner via WinHTTP

Copyright (c) 2006 - 2021 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////////////////// Macros / Defines /////////////////////////////////

#pragma once

#ifndef __HTTPDOWNLOADDER2_H__
#define __HTTPDOWNLOADDER2_H__

#ifndef CHTTPDOWNLOADDER2_EXT_CLASS
#define CHTTPDOWNLOADDER2_EXT_CLASS
#endif //#ifndef CHTTPDOWNLOADDER2_EXT_CLASS


//////////////////////////// Includes /////////////////////////////////////////

#ifndef _WINHTTPX_
#pragma message("To avoid this message, please put winhttp.h in your pre compiled header (normally stdafx.h)")
#include <winhttp.h>
#endif //#ifndef _WINHTTPX_

#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
#ifndef __WINCRYPT_H__
#pragma message("To avoid this message, please put WinCrypt.h in your pre compiled header (normally stdafx.h)")
#include <WinCrypt.h>
#endif //#ifndef __WINCRYPT_H__
#endif //#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT

#ifndef _ATOMIC_
#pragma message("To avoid this message, please put atomic in your pre compiled header (normally stdafx.h)")
#include <atomic>
#endif //#ifndef _ATOMIC_


//////////////////////////// Classes //////////////////////////////////////////

//The synchronous downloading API which CHTTPDownloadDlg incorporates. If you do not want
//any UI then you can use this class directly
class CHTTPDOWNLOADDER2_EXT_CLASS CHTTPDownloader2
{
public:
//Constructors / Destructors
  CHTTPDownloader2();
  CHTTPDownloader2(const CHTTPDownloader2&) = delete;
  CHTTPDownloader2(CHTTPDownloader2&&) = delete;
  virtual ~CHTTPDownloader2();

//Methods
  CHTTPDownloader2& operator=(const CHTTPDownloader2&) = delete;
  CHTTPDownloader2& operator=(CHTTPDownloader2&&) = delete;
  bool Download();
  bool DeleteDownloadedFile();
  void AttachSession(_In_ HINTERNET hInternetSession) noexcept;
  HINTERNET DetachSession() noexcept;

//Enums
  enum class ConnectionType
  {
    UsePreConfig,
    DirectToInternet,
    UseProxy,
  };

//Member variables
  CString m_sURLToDownload; //The URL to download
  CString m_sFileToDownloadInto; //Where to download it to
  CString m_sProxyServer; //The proxy server to use
  CString m_sProxyUserName; //The proxy server username to use
  CString m_sProxyPassword; //The proxy server password to use
  CString m_sHTTPUserName; //The HTTP server username to use
  CString m_sHTTPPassword; //The HTTP server password to use
  CString m_sUserAgent; //The HTTP_USER_AGENT header to use
  CString m_sReferrer; //Allows you to customize the HTTP_REFERRER header
  CString m_sHTTPVerb; //The HTTP verb to use (normally would be "GET")
  CString m_sHTTPVersion; //The HTTP version to use (e.g. "HTTP/1.0", "HTTP/1.1" etc)
  ConnectionType m_ConnectionType; //The connection type to use  
  bool m_bPromptFileOverwrite; //Should overwrites result in a prompt, the base CHttpDownloader2 does not support this
  bool m_bPromptForProxyDetails; //Should we prompt for proxy credentials if required
  bool m_bPromptForHTTPDetails; //Should we prompt for HTTP server credentials if required
  double m_dbLimit; //For BANDWIDTH Throptling, The value in Bytes / Second to limit the connection to
  ULONGLONG m_nStartPos; //Offset to resume the download at   
  bool m_bNoURLRedirect; //Set to true, if you do not want 302 redirects to be followed
  DWORD m_dwReadBufferSize; //The size of the receive buffer when we read the HTTP response
  DWORD m_dwProxyPreauthenticationScheme; //The authentication scheme to use for proxy preauthentication, Can be WINHTTP_AUTH_SCHEME_BASIC, WINHTTP_AUTH_SCHEME_NTLM, WINHTTP_AUTH_SCHEME_PASSPORT
                                          //WINHTTP_AUTH_SCHEME_DIGEST or WINHTTP_AUTH_SCHEME_NEGOTIATE
  DWORD m_dwHTTPPreauthenticationScheme; //The authentication scheme to use for HTTP server preauthentication, Can be WINHTTP_AUTH_SCHEME_BASIC, WINHTTP_AUTH_SCHEME_NTLM, WINHTTP_AUTH_SCHEME_PASSPORT
                                         //WINHTTP_AUTH_SCHEME_DIGEST or WINHTTP_AUTH_SCHEME_NEGOTIATE
  bool m_bProxyPreauthentication; //Should we supply credentials on the first request for the Proxy rather than starting out with anonymous credentials
                                  //and only authenticating when challenged
  bool m_bHTTPPreauthentication; //Should we supply credentials on the first request for the HTTP Server rather than starting out with anonymous credentials
                                 //and only authenticating when challenged
  CString m_sAcceptTypes; //The AcceptTypes header to send
  bool m_bIgnoreUnknownCertificateAuthorityProblems; //Set to true to set the SECURITY_FLAG_IGNORE_UNKNOWN_CA flag
  bool m_bIgnoreIncorrectUsageProblems; //Set to true to set the SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE flag
  bool m_bIgnoreCertificateCommonNameProblems; //Set to true to set the SECURITY_FLAG_IGNORE_CERT_CN_INVALID flag
  bool m_bIgnoreCertificateDateProblems; //Set to true to set the SECURITY_FLAG_IGNORE_CERT_DATE_INVALID flag

//Methods
#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
  bool SetClientCertificate(_In_opt_ PCCERT_CONTEXT pClientCertContext) noexcept; //The client certificate we will use. Note the code makes a copy of the cert context through 
                                                                                  //CertDuplicateCertificateContext, so client code still needs to destroy the passed in cert context parameter
                                                                                  //using CertFreeCertificateContext
#endif //#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT

protected:
//Member variables
  DWORD m_dwServiceType;
  HINTERNET m_hInternetSession;
  HINTERNET m_hHttpConnection;
  HINTERNET m_hHttpFile;
  CString m_sServer;
  CString m_sObject;
  INTERNET_PORT m_nPort;
  std::atomic<bool> m_bAbort;
  CFile m_FileToDownloadInto;
  CCriticalSection m_csHandles; //Critical section we use to serialize access to the Wininet handles
#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
  PCCERT_CONTEXT m_pCertContext;
#endif //#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
 
//Static methods
  static void CALLBACK _OnWinHttpStatusCallBack(_In_ HINTERNET hInternet, _In_ DWORD_PTR dwContext, _In_ DWORD dwInternetStatus, _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD dwStatusInformationLength);
  static _Return_type_success_(return != false) bool QueryStatusNumber(_In_ HINTERNET hInternet, _In_ DWORD dwFlag, _Out_ DWORD& dwCode) noexcept;
  static _Return_type_success_(return != false) bool QueryStatusCode(_In_ HINTERNET hInternet, _Out_ DWORD& dwCode) noexcept;
  static _Return_type_success_(return != false) bool QueryContentLength(_In_ HINTERNET hInternet, _Out_ ULONGLONG& nCode);
  static CString GetErrorMessage(_In_ DWORD dwError);
  
//Standard methods
  void ReleaseHandles();
#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
  void ReleaseCertContext() noexcept;
#endif //#ifndef HTTPDOWNLOADER2_NO_CERTIFICATE_SUPPORT
  void SetAbort();
  bool _Download();

//Virtual methods
  virtual bool CreateSession();
  virtual bool CreateConnection();
  virtual bool CreateRequest();
  virtual bool DoHTTPAuthentication(_In_ DWORD dwAuthenticationScheme);
  virtual bool DoProxyAuthentication(_In_ DWORD dwAuthenticationScheme);
  virtual bool DoCertificateSelection() noexcept;
  virtual DWORD ChooseHTTPAuthScheme(_In_ DWORD dwSupportedSchemes) noexcept;
  virtual DWORD ChooseProxyAuthScheme(_In_ DWORD dwSupportedSchemes) noexcept;
  virtual void OnWinHttpStatusCallBack(_In_ HINTERNET hInternet, _In_ DWORD dwInternetStatus, _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD dwStatusInformationLength);
  virtual void HandleError(_In_ UINT nID, _In_ DWORD dwError);
  virtual void HandleStatusCode(_In_ UINT nID, _In_ DWORD dwStatusCode);
  virtual DWORD GetOpenRequestFlags() noexcept;
  virtual CString GetOptionalHeaders();
  virtual bool HandlePrompt(_Inout_ DWORD& dwError);
  virtual void SetStatus(_In_ UINT nID);
  virtual void SetStatus(_In_ UINT nID, _In_z_ LPCTSTR lpsz1);
  virtual void SetStatus(_In_z_ LPCTSTR pszStatus);
  virtual bool Abort() noexcept;
  virtual void OnGotContentLength(_In_ ULONGLONG nContentLength);
  virtual void OnProgress(_In_ ULONGLONG nBytesRead, _In_ bool bGotFileSize, _In_ ULONGLONG nFileSize);
  virtual bool OnDownloadData(_In_reads_bytes_opt_(dwSize) const BYTE* pbyData, _In_ DWORD dwSize);
};

#endif //#ifndef __HTTPDOWNLOADDER2_H__
