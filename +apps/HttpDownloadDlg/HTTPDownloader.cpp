/*
Module : HTTPDownloader.cpp
Purpose: Defines the implementation for an MFC class which provides a wrapping for downloading HTTP requests in a 
         synchronous manner via Wininet
Created: PJN / 15-07-2006
History: PJN / 16-07-2006 1. Split off CHttpDownloader class into its own module
                          2. Now includes support for customizing the HTTP_REFERRER header
                          3. Now includes support for customizing the HTTP verb used e.g. "GET" etc
                          4. Now includes support for specifying the HTTP version to use e.g. "HTTP/1.0". "HTTP/1.1" etc
                          5. Now includes support for customizing the HTTP_ACCEPT header
                          6. Added support for client customization of any other HTTP headers which are now transmitted
                          7. Brought the CHttpDownloadSettings member variables back into the CHttpDownloader class.
                          This means that the HttpDownloadSettings module is now defunct.
                          8. In line with the new CHttpDownloader2 class, the creation of the various handles is now 
                          broken down into 3 virtual functions of CreateSession, CreateConnection and CreateRequest.
                          9. Now supports both HTTP and Proxy preauthentication.
                          10. Reviewed all TRACE statements for correctness
                          11. Internet handles are now freed up before CHttpDownloader::Download returns
                          12. Moved the m_lAbort flag from the CHttpDownloadDlg up into CHttpDownloader. This allows client
                          code extra flexibility in how users can cancel a download. Thanks to Itamar Syn-Hershko for
                          reporting this issue.
                          13. Inclusion of a function called "DeleteDownloadedFile" which is a simple wrapper for deleting 
                          the downloaded file. Thanks to Itamar Syn-Hershko for suggesting this addition.
         PJN / 25-08-2006 1. Downloading to file is now optional, a new virtual function OnDownloadData is now called each 
                          time a chunk of data has been retrieved. The default implementation writes the data into the file 
                          "m_sFileToDownloadInto". A derived class is free to override this function and implement their own 
                          specific functionality. Thanks to Itamar Syn-Hershko for suggesting this update.
                          2. Optimized the way aborting a download occurs by freeing up the handles in the SetAbort call.
                          This should hopefully fix times where aborting a download appears to respond slowly.
                          3. Class now supports sending client certificates both via user selection and programmatically. 
                          Thanks to Johan Sörensen for this very nice addition.
         PJN / 10-06-2007 1. Updated copyright details.
                          2. CHttpDownloader now supports resumed downloads for files > 4GB in size.
                          3. Updated sample app to compile cleanly on VC 2005
         PJN / 30-12-2007 1. Updated sample apps to clean compile on VC 2008
                          2. Remove VC 6 style appwizard comments from the code.
                          3. CHttpDownloader::GetErrorMessage now uses the FORMAT_MESSAGE_IGNORE_INSERTS flag. For more 
                          information please see Raymond Chen's blog at 
                          http://blogs.msdn.com/oldnewthing/archive/2007/11/28/6564257.aspx. Thanks to Alexey Kuznetsov 
                          for reporting this issue.
                          4. CHttpDownloader::GetErrorMessage now uses Checked::tcsncpy_s if compiled using VC 2005 or 
                          later.
         PJN / 11-05-2008 1. Updated copyright details
                          2. Addition of AttachSession and DetachSession methods which allow the lifetime of the session
                          to be controlled independently of the lifetime of the CHttpDownloader instance. Thanks to 
                          Hans Dietrich for prompting this update
                          3. Fixed a spelling mistake in the IDS_HTTPDOWNLOAD_RETRIEVING_FILE string resource
         PJN / 08-06-2008 1. Updated code to compile correctly using _ATL_CSTRING_EXPLICIT_CONSTRUCTORS define
                          2. Code now compiles cleanly using Code Analysis (/analyze)
                          3. The code has now been updated to support VC 2005 or later only.  
         PJN / 22-02-2015 1. Renamed CHttpDownloader class to CHTTPDownloader.
                          2. Updated the code to clean compile using /analyze
                          3. Added support for a CHTTPDownloader::m_bIgnoreInvalidCertificate value. Setting this value to 
                          TRUE, the code will ignore the ERROR_INTERNET_INVALID_CA error code when downloading 
                          (i.e. an invalid HTTPS certificate)
                          4. Added support for a CHTTPDownloader::m_bIgnoreCRLFailures. Setting this value to TRUE, the code 
                          will ignore the ERROR_INTERNET_SEC_CERT_REV_FAILED error code when downloading 
                          (i.e. revocation checks failed)
         PJN / 16-01-2016 1. Updated copyright details.
                          2. Verified the code compiles cleanly in VC 2015
                          3. Added SAL annotations to all the code
         PJN / 25-12-2016 1. Updated code to use nullptr instead of NULL
                          2. Updated usage of BOOL with bool in codebase
                          3. Reworked CHTTPDownloader::Abort to use proper thread protection.
                          4. Removed support for the m_bIgnoreInvalidCertificate & m_bIgnoreCRLFailures configuration values
                          and introduced support for SECURITY_FLAG_IGNORE_REVOCATION, SECURITY_FLAG_IGNORE_UNKNOWN_CA, 
                          SECURITY_FLAG_IGNORE_WRONG_USAGE, SECURITY_FLAG_IGNORE_CERT_CN_INVALID, 
                          SECURITY_FLAG_IGNORE_CERT_DATE_INVALID, SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS & 
                          SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP option flags in the CHTTPDownloader class
         PJN / 19-09-2017 1. Updated copyright details.
                          2. Fixed compiler errors in CHTTPDownloader::CreateSession
         PJN / 28-12-2017 1. Updated the code to compile cleanly when _ATL_NO_AUTOMATIC_NAMESPACE is defined.
         PJN / 27-10-2018 1. Updated copyright details.
                          2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that
                          the code will now only compile on VC 2017 or later.
         PJN / 30-04-2019 1. Updated copyright details.
                          2. Updated the code to clean compile on VC 2019
         PJN / 08-12-2019 1. Fixed a bug in CHTTPDownloader::Download where an unsuccessfully downloaded file would not be
                          deleted. Thanks to "michar" for reporting this bug.
         PJN / 12-01-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 16-01-2021 1. Updated copyright details.
                          2. Updated the code to use std::atomic for thread synchronisation.
                          3. Replaced ATL::CHeapPtr with std::vector.
                          4. General cleanup / review of the code

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
#include "HTTPDownloader.h"

#ifndef _VECTOR_
#pragma message("To avoid this message, please put vector in your pre compiled header (normally stdafx.h)")
#include <vector>
#endif //#ifndef _VECTOR_


//////////////////////////// Macros / Defines /////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

//Link to the wininet lib file automatically
#pragma comment(lib, "Wininet.lib")

//Link to the Windows Cryptography file automatically if required
#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
#pragma comment(lib, "Crypt32.lib")
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT


//////////////////////////// Implementation ///////////////////////////////////

#pragma warning(suppress: 26455)
CHTTPDownloader::CHTTPDownloader() : m_ConnectionType(ConnectionType::UsePreConfig),
                                     m_bPromptFileOverwrite(true),
                                     m_bPromptForProxyDetails(true),
                                     m_bPromptForHTTPDetails(true),
                                     m_bPromptForCertificateDetails(true),
                                     m_dbLimit(0),
                                     m_nStartPos(0),
                                     m_bNoURLRedirect(false),
                                     m_dwReadBufferSize(1024),
                                     m_bProxyPreauthentication(true),
                                     m_bHTTPPreauthentication(true),
                                     m_sAcceptTypes(_T("*/*")),
                                     m_bIgnoreCertificateRevocationProblems(false),
                                     m_bIgnoreUnknownCertificateAuthorityProblems(false),
                                     m_bIgnoreIncorrectUsageProblems(false),
                                     m_bIgnoreCertificateCommonNameProblems(false),
                                     m_bIgnoreCertificateDateProblems(false),
                                     m_bIgnoreHTTPSToHTTPRedirectErrors(false),
                                     m_bIgnoreHTTPToHTTPSRedirectErrors(false),
                                     m_dwServiceType(0),
                                     m_hInternetSession(nullptr),
                                     m_hHttpConnection(nullptr),
                                     m_hHttpFile(nullptr),
                                     m_nPort(0),
                                     m_bAbort(false)
#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
                                     ,m_pCertContext(nullptr)
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
{
}

CHTTPDownloader::~CHTTPDownloader()
{
#pragma warning(suppress: 26447)
  ReleaseHandles();
#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
  ReleaseCertContext();
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
}

void CHTTPDownloader::AttachSession(_In_ HINTERNET hInternetSession) noexcept
{
  if (m_hInternetSession != nullptr)
    InternetCloseHandle(m_hInternetSession);
  m_hInternetSession = hInternetSession;
}

HINTERNET CHTTPDownloader::DetachSession() noexcept
{
  HINTERNET hTempSession = m_hInternetSession;
  m_hInternetSession = nullptr;
  return hTempSession;
}

void CHTTPDownloader::ReleaseHandles()
{
  //Serialize access to the handles
  CSingleLock sl(&m_csHandles, TRUE);

  //Free up the internet handles we may be using
  if (m_hHttpFile != nullptr)
  {
    InternetCloseHandle(m_hHttpFile);
    m_hHttpFile = nullptr;
  }
  if (m_hHttpConnection != nullptr)
  {
    InternetCloseHandle(m_hHttpConnection);
    m_hHttpConnection = nullptr;
  }
  if (m_hInternetSession != nullptr)
  {
    InternetCloseHandle(m_hInternetSession);
    m_hInternetSession = nullptr;
  }
}

#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
void CHTTPDownloader::ReleaseCertContext() noexcept
{
  if (m_pCertContext != nullptr)
  {
    CertFreeCertificateContext(m_pCertContext);
    m_pCertContext = nullptr;
  }
}
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT

#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
bool CHTTPDownloader::SetClientCertificate(_In_opt_ PCCERT_CONTEXT pCertContext) noexcept
{
  //What will be the return value from this function (assume the best)
  bool bSuccess = true;

  //Free up the current copy if any
  ReleaseCertContext();

  //Now make our only copy of the certificate passed
  if (pCertContext != nullptr)
  {
    m_pCertContext = CertDuplicateCertificateContext(pCertContext);
    bSuccess = (m_pCertContext != nullptr);
  }

  return bSuccess;
}
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT

#pragma warning(suppress: 26440)
bool CHTTPDownloader::DeleteDownloadedFile()
{
  const bool bSuccess = (DeleteFile(m_sFileToDownloadInto) != FALSE);
  if (!bSuccess)
    TRACE(_T("CHTTPDownloader::DeleteDownloadedFile, Failed to delete failed downloaded file, Error:%u\n"), GetLastError());
  return bSuccess;
}

bool CHTTPDownloader::Download()
{
  //Remember if we have the file to download into before we do the download
  bool bDownloadFileAlreadyExists = false;
  const bool bSpecifiedDownloadFile = (m_sFileToDownloadInto.GetLength() != 0); //NOLINT(clang-analyzer-core.CallAndMessage)
  if (bSpecifiedDownloadFile)
    bDownloadFileAlreadyExists = (GetFileAttributes(m_sFileToDownloadInto) != INVALID_FILE_ATTRIBUTES);

  //Call the internal version which does the heavy lifting
  const bool bSuccess = _Download();

  //Free up the internet handles now that we are finished with them
  ReleaseHandles();

  //Close the download file if it was used
  if (bSpecifiedDownloadFile)
  {
    try
    {
      if (m_FileToDownloadInto.operator HANDLE() != INVALID_HANDLE_VALUE)
        m_FileToDownloadInto.Close();
    }
#pragma warning(suppress: 26429 26462)
    catch(CFileException* pEx)
    {
      pEx->Delete();
    }

    //Remove any downloaded file which did not come down successfully (when it did not exist before we did the download)
    if (!bSuccess && !bDownloadFileAlreadyExists && (GetFileAttributes(m_sFileToDownloadInto) != INVALID_FILE_ATTRIBUTES))
      DeleteDownloadedFile();
  }

  return bSuccess;
}

bool CHTTPDownloader::CreateSession()
{
  //Serialize access to the handles
  CSingleLock sl(&m_csHandles, TRUE);

  //Create the Internet session handle if required
  if (m_hInternetSession == nullptr)
  {
    switch (m_ConnectionType)
    {
      case ConnectionType::UsePreConfig:
      {
        m_hInternetSession = InternetOpen(m_sUserAgent.GetLength() ? m_sUserAgent.GetString() : AfxGetAppName(), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
        break;
      }
      case ConnectionType::DirectToInternet:
      {
        m_hInternetSession = InternetOpen(m_sUserAgent.GetLength() ? m_sUserAgent.GetString() : AfxGetAppName(), INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
        break;
      }
      case ConnectionType::UseProxy:
      {
        ASSERT(m_sProxyServer.GetLength()); //You need to give me a proxy Server
        m_hInternetSession = InternetOpen(m_sUserAgent.GetLength() ? m_sUserAgent.GetString() : AfxGetAppName(), INTERNET_OPEN_TYPE_PROXY, m_sProxyServer, nullptr, 0);
        break;
      }
      default:
      {
        ASSERT(false);
        break;
      }
    }
  }

  if (m_hInternetSession == nullptr)
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::CreateSession, Failed in call to InternetOpen, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
    return false;
  }

  //Setup the status callback function
  if (InternetSetStatusCallback(m_hInternetSession, _OnWininetStatusCallBack) == INTERNET_INVALID_STATUS_CALLBACK)
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::Download, Failed in call to InternetSetStatusCallback, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
    return false;
  }

  return true;
}

bool CHTTPDownloader::CreateConnection()
{
  //Serialize access to the handles
  CSingleLock sl(&m_csHandles, TRUE);

  //Make the connection to the HTTP server
  ASSERT(m_hHttpConnection == nullptr);
  if (m_sHTTPUserName.GetLength())
#pragma warning(suppress: 26490)
    m_hHttpConnection = InternetConnect(m_hInternetSession, m_sServer, m_nPort, m_sHTTPUserName, 
                                        m_sHTTPPassword, INTERNET_SERVICE_HTTP, 0, reinterpret_cast<DWORD_PTR>(this));
  else
#pragma warning(suppress: 26490)
    m_hHttpConnection = InternetConnect(m_hInternetSession, m_sServer, m_nPort, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, reinterpret_cast<DWORD_PTR>(this));
  if (m_hHttpConnection == nullptr)
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::CreateConnection, Failed in call to InternetConnect, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER, dwError);
    return false;
  }

  return true;
}

bool CHTTPDownloader::CreateRequest()
{
  //First need to loop thro the string to create a CStringArray version of AcceptTypes
  std::vector<CString> AcceptTypes;
  int nCurPos = 0;
  CString sToken(m_sAcceptTypes.Tokenize(_T(",;"), nCurPos));
  while (sToken != _T(""))
  {
      sToken.Trim();
      AcceptTypes.emplace_back(sToken);
      sToken = m_sAcceptTypes.Tokenize(_T(",;"), nCurPos);
  }

  //Ok, now that we have the string data in an array, convert to the double null terminated array format for HttpOpenRequest
  const auto nAcceptTypes = AcceptTypes.size();
  std::vector<LPCTSTR> ppszAcceptTypes;
  ppszAcceptTypes.resize(nAcceptTypes + 1);
  for (size_t i=0; i<nAcceptTypes; i++)
#pragma warning(suppress: 26446 26481 26489)
    ppszAcceptTypes[i] = AcceptTypes[i].GetString();
#pragma warning(suppress: 26446 26481 26489)
  ppszAcceptTypes[nAcceptTypes] = nullptr;

  //Serialize access to the handles
  CSingleLock sl(&m_csHandles, TRUE);

  //Issue the request to read the file
  ASSERT(m_hHttpFile == nullptr);
#pragma warning(suppress: 26490)
  m_hHttpFile = HttpOpenRequest(m_hHttpConnection, m_sHTTPVerb.GetLength() ? m_sHTTPVerb.GetString() : nullptr, m_sObject, 
                                m_sHTTPVersion.GetLength() ? m_sHTTPVersion.GetString() : nullptr, 
                                m_sReferrer.GetLength() ? m_sReferrer.GetString() : nullptr, ppszAcceptTypes.data(), 
                                GetOpenRequestFlags(), reinterpret_cast<DWORD_PTR>(this));
  if (m_hHttpFile == nullptr)
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::CreateRequest, Failed in call to HttpOpenRequest, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER, dwError);
    return false;
  }

  //Set the optional request flags if necessary
  DWORD dwNewFlags = 0;
  if (m_bIgnoreCertificateRevocationProblems)
    dwNewFlags |= SECURITY_FLAG_IGNORE_REVOCATION;
  if (m_bIgnoreUnknownCertificateAuthorityProblems)
    dwNewFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
  if (m_bIgnoreIncorrectUsageProblems)
    dwNewFlags |= SECURITY_FLAG_IGNORE_WRONG_USAGE;
  if (m_bIgnoreCertificateCommonNameProblems)
    dwNewFlags |= SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
  if (m_bIgnoreCertificateDateProblems)
    dwNewFlags |= SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
  if (m_bIgnoreHTTPSToHTTPRedirectErrors)
    dwNewFlags |= SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP;
  if (m_bIgnoreHTTPToHTTPSRedirectErrors)
    dwNewFlags |= SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS;
  if (dwNewFlags)
  {
    DWORD dwFlags = 0;
    DWORD dwBuffLen = sizeof(dwFlags);
    if (!InternetQueryOption(m_hHttpFile, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, &dwBuffLen))
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::CreateRequest, Failed in call to InternetSetOption, Error:%u\n"), dwError);
      HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }

    dwFlags |= dwNewFlags;
    if (!InternetSetOption(m_hHttpFile, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, sizeof (dwFlags)))
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::CreateRequest, Failed in call to InternetSetOption, Error:%u\n"), dwError);
      HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
  }

  return true;
}

bool CHTTPDownloader::DoHTTPAuthentication()
{
  const int nHTTPUserLength = m_sHTTPUserName.GetLength();
  if (nHTTPUserLength)
  {
    CString sLocalHTTPUserName(m_sHTTPUserName);
    BOOL bSetOption = InternetSetOption(m_hHttpFile, INTERNET_OPTION_USERNAME, sLocalHTTPUserName.GetBuffer(), sLocalHTTPUserName.GetLength());
    sLocalHTTPUserName.ReleaseBuffer();
    if (!bSetOption)
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::DoHTTPAuthentication, Failed to set HTTP server username details, Error:%u\n"), dwError);
      HandleStatusCode(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
    CString sLocalHTTPPassword(m_sHTTPPassword);
    bSetOption = InternetSetOption(m_hHttpFile, INTERNET_OPTION_PASSWORD, sLocalHTTPPassword.GetBuffer(), sLocalHTTPPassword.GetLength());
    sLocalHTTPPassword.ReleaseBuffer();
    if (!bSetOption)
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::DoHTTPAuthentication, Failed to set HTTP server password details, Error:%u\n"), dwError);
      HandleStatusCode(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
  }

  return true;
}

bool CHTTPDownloader::DoProxyAuthentication()
{
  const int nProxyUserLength = m_sProxyUserName.GetLength();
  if (nProxyUserLength)
  {
    CString sLocalProxyUserName(m_sProxyUserName);
    BOOL bSetOption = InternetSetOption(m_hHttpFile, INTERNET_OPTION_PROXY_USERNAME, sLocalProxyUserName.GetBuffer(), sLocalProxyUserName.GetLength());
    sLocalProxyUserName.ReleaseBuffer();
    if (!bSetOption)
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::DoProxyAuthentication, Failed to set Proxy username details, Error:%u\n"), dwError);
      HandleStatusCode(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
    CString sLocalProxyPassword(m_sProxyPassword);
    bSetOption = InternetSetOption(m_hHttpFile, INTERNET_OPTION_PROXY_PASSWORD, sLocalProxyPassword.GetBuffer(), sLocalProxyPassword.GetLength());
    sLocalProxyPassword.ReleaseBuffer();
    if (!bSetOption)
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::DoProxyAuthentication, Failed to set Proxy password details, Error:%u\n"), dwError);
      HandleStatusCode(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
  }

  return true;
}

bool CHTTPDownloader::OnDownloadData(_In_reads_bytes_opt_(dwSize) const BYTE* pbyData, _In_ DWORD dwSize)
{
  if (m_sFileToDownloadInto.GetLength())
  {
    //Write the data to file
    try
    {
      m_FileToDownloadInto.Write(pbyData, dwSize);
    }
#pragma warning(suppress: 26429 26462)
    catch(CFileException* pEx)
    {
      TRACE(_T("CHTTPDownloader::OnDownloadData, An exception occured while writing to the download file\n"));
      HandleError(IDS_HTTPDOWNLOAD_ERROR_READFILE, pEx->m_lOsError);
      pEx->Delete();
      return false;
    }
  }

  //Continue the download if we are not aborting
  return !Abort();
}

#pragma warning(suppress: 26440)
bool CHTTPDownloader::DoCertificateSelection()
{
  //What will be the return value from this function (assume the worst)
  bool bSuccess = false;

#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT
  //Do we have a client cert, if so try use it
  if (m_pCertContext)
#pragma warning(suppress: 26474 26465 26492)
    bSuccess = (InternetSetOption(m_hHttpFile, INTERNET_OPTION_CLIENT_CERT_CONTEXT, reinterpret_cast<LPVOID>(const_cast<PCERT_CONTEXT>(m_pCertContext)), sizeof(CERT_CONTEXT)) != FALSE);
#endif //#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT

  return bSuccess;
}

bool CHTTPDownloader::_Download()
{
  //Make sure our wininet handles are empty
  ReleaseHandles();

  //Validate the URL
  ASSERT(m_sURLToDownload.GetLength()); //Did you forget to specify the file to download
  if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort)) //NOLINT(clang-analyzer-core.CallAndMessage)
  {
    //Try sticking "http://" before it
    m_sURLToDownload = _T("http://") + m_sURLToDownload;
    if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::_Download, Failed to parse the URL: %s\n"), m_sURLToDownload.GetString());
      HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
      return false;
    }
  }

  //open up the download file if required to
  if (m_sFileToDownloadInto.GetLength())
  {
    const bool bDownloadFileExists = (GetFileAttributes(m_sFileToDownloadInto) != INVALID_FILE_ATTRIBUTES);

    //Try and open the file we will download into
    DWORD dwFileFlags = 0;
    if (bDownloadFileExists && (m_nStartPos > 0))
      dwFileFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite;
    else
      dwFileFlags = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite;
    if (!m_FileToDownloadInto.Open(m_sFileToDownloadInto, dwFileFlags))
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::_Download, Failed to open the file to download into, Error:%u\n"), dwError);
      HandleError(IDS_HTTPDOWNLOAD_FAIL_FILE_OPEN, dwError);
      return false;
    }
    else
    {
      //Seek to the end of the file
      try
      {
        m_FileToDownloadInto.Seek(m_nStartPos, CFile::begin);
        m_FileToDownloadInto.SetLength(m_nStartPos);
      }
#pragma warning(suppress: 26462)
      catch(CFileException* pEx)
      {
        TRACE(_T("CHTTPDownloader::_Download, An exception occured while set file pointer position, Error:%d\n"), pEx->m_lOsError);
        HandleError(IDS_HTTPDOWNLOAD_FAIL_FILE_SEEK, pEx->m_lOsError);
        pEx->Delete();
        return false;
      }	
    }
  }

  //Call the virtual functions which create the session, connection and request
  if (!CreateSession())
    return false;
  if (!CreateConnection())
    return false;
  if (!CreateRequest())
    return false;

  bool bRetryingProxy = false;
  bool bRetryingHTTP = false;
  bool bRetryingCertificate = false;

  //Do preauthentication if required
  if (m_bProxyPreauthentication)
  {
    if (!DoProxyAuthentication())
      return false;
    bRetryingProxy = true;
  }
  if (m_bHTTPPreauthentication)
  {
    if (!DoHTTPAuthentication())
      return false;
    bRetryingHTTP = true;
  }

//label used to jump to if we need to resend the request
resend:

  //Issue the request
  CString sHeaders(GetOptionalHeaders());
  const bool bSend = (HttpSendRequest(m_hHttpFile, sHeaders.GetLength() ? sHeaders.GetString() : nullptr, sHeaders.GetLength(), nullptr, 0) != FALSE);
  if (!bSend)
  {
    const DWORD dwError = GetLastError();
    if (dwError == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED && !bRetryingCertificate)
    {
      if (m_bPromptForCertificateDetails)
      {
        if (DoCertificateSelection()) //CHTTPDownloader::DoCertificateSelection() might display a dialog
        {
          bRetryingCertificate = true;
#pragma warning(suppress: 26438 26448)
          goto resend;
        }
      }
      else if (CHTTPDownloader::DoCertificateSelection()) //try programmatic certificate selection
      {
        bRetryingCertificate = true;
#pragma warning(suppress: 26438 26448)
        goto resend;
      }
    }
  
    TRACE(_T("CHTTPDownloader::_Download, Failed in call to HttpSendRequest, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER, dwError);
    return false;
  }

  //Handle the status code in the response
  bool bPrompt = false;
  DWORD dwStatusCode = 0;
  if (!QueryStatusCode(m_hHttpFile, dwStatusCode))
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::_Download, Failed in call to HttpQueryInfo for HTTP query status code, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_INVALID_SERVER_RESPONSE, dwError);
    return false;
  }

  //discard any outstanding data if required
  if (dwStatusCode == HTTP_STATUS_PROXY_AUTH_REQ || dwStatusCode == HTTP_STATUS_DENIED)
  {
    std::vector<BYTE> readBuffer;
    readBuffer.resize(m_dwReadBufferSize);
    bool bContinueRead = true;
    while (bContinueRead)
    {
      DWORD dwSize = 0;
#pragma warning(suppress: 26486)
      bContinueRead = (InternetReadFile(m_hHttpFile, readBuffer.data(), m_dwReadBufferSize, &dwSize) != FALSE);
    }
  }

  if (dwStatusCode == HTTP_STATUS_PROXY_AUTH_REQ) //Proxy authentication required
  {
    const int nProxyUserLength = m_sProxyUserName.GetLength();
    if (nProxyUserLength && !bRetryingProxy)
    {
      if (!DoProxyAuthentication())
        return false;
      bRetryingProxy = true;
#pragma warning(suppress: 26438 26448)
      goto resend;
    }
    else if (m_bPromptForProxyDetails)
      bPrompt = true;
    else
    {
      TRACE(_T("CHTTPDownloader::_Download, Failed to retrieve a HTTP OK or partial content status, Status Code:%u\n"), dwStatusCode);
      HandleStatusCode(IDS_HTTPDOWNLOAD_INVALID_HTTP_RESPONSE, dwStatusCode);
      return false;
    }
  }
  else if (dwStatusCode == HTTP_STATUS_DENIED) //HTTP authentication required
  {
    const int nHTTPUserLength = m_sHTTPUserName.GetLength();
    if (nHTTPUserLength && !bRetryingHTTP)
    {
      if (!DoHTTPAuthentication())
        return false;
      bRetryingHTTP = true;
#pragma warning(suppress: 26438 26448)
      goto resend;
    }
    else if (m_bPromptForHTTPDetails)
      bPrompt = true;
    else
    {
      TRACE(_T("CHTTPDownloader::_Download, Failed to retrieve a HTTP OK or partial content status, Status Code:%u\n"), dwStatusCode);
      HandleStatusCode(IDS_HTTPDOWNLOAD_INVALID_HTTP_RESPONSE, dwStatusCode);
      return false;
    }
  }
  else if (dwStatusCode != HTTP_STATUS_OK && dwStatusCode != HTTP_STATUS_PARTIAL_CONTENT)
  {
    TRACE(_T("CHTTPDownloader::_Download, Failed to retrieve a HTTP OK or partial content status, Status Code:%u\n"), dwStatusCode);
    HandleStatusCode(IDS_HTTPDOWNLOAD_INVALID_HTTP_RESPONSE, dwStatusCode);
    return false;
  }

  if (bPrompt)
  {
    DWORD dwError = 0;
    if (HandlePrompt(dwError))
#pragma warning(suppress: 26438 26448)
      goto resend;
    else
    {
      if (dwError != 0)
        HandleError(IDS_HTTPDOWNLOAD_ABORTING_TRANSFER, dwError);
      return false;
    }
  }

  //Update the status control to reflect that we are getting the file information
  SetStatus(IDS_HTTPDOWNLOAD_GETTING_FILE_INFORMATION);

  //Get the length of the file
  ULONGLONG nContentLength = 0;
  bool bGotFileSize = false;
  if (QueryContentLength(m_hHttpFile, nContentLength))
  {
    //Call the virtual function to indicate that we have got the Content-length header
    bGotFileSize = true;
    OnGotContentLength(nContentLength);
  }
  else
    TRACE(_T("CHTTPDownloader::_Download, failed to get content length for request, continuing\n"));

  //Update the status to say that we are now downloading the file
  SetStatus(IDS_HTTPDOWNLOAD_RETRIEVING_FILE);

  //Remember the time we started the download at
  SYSTEMTIME st{};
  GetSystemTime(&st);
  FILETIME dwStartTicks{};
  if (!SystemTimeToFileTime(&st, &dwStartTicks))
  {
    const DWORD dwError = GetLastError();
    TRACE(_T("CHTTPDownloader::_Download, Failed in call to SystemTimeToFileTime, Error:%u\n"), dwError);
    HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
    return false;
  }

  //Now do the actual read of the file
  DWORD dwBytesRead = 0;
  std::vector<BYTE> readBuffer;
  readBuffer.resize(m_dwReadBufferSize);
  ULONGLONG nTotalBytesRead = 0;
  do
  {
    if (!InternetReadFile(m_hHttpFile, readBuffer.data(), m_dwReadBufferSize, &dwBytesRead))
    {
      const DWORD dwError = GetLastError();
      TRACE(_T("CHTTPDownloader::_Download, Failed in call to InternetReadFile, Error:%u\n"), dwError);
      HandleError(IDS_HTTPDOWNLOAD_ERROR_READFILE, dwError);
      return false;
    }
    else
    {
      //Do something with any data read
      if (dwBytesRead)
      {
        //Call the virtual function which handles the downloading
        if (!OnDownloadData(readBuffer.data(), dwBytesRead))
          return false;

        //Increment the total number of bytes read
        nTotalBytesRead += dwBytesRead;

        //Do the bandwidth throttling
        if (m_dbLimit > 0)
        {
          GetSystemTime(&st);
          FILETIME ft{};
          if (!SystemTimeToFileTime(&st, &ft))
          {
            const DWORD dwError = GetLastError();
            TRACE(_T("CHTTPDownloader::_Download, Failed in call to SystemTimeToFileTime, Error:%u\n"), dwError);
            HandleError(IDS_HTTPDOWNLOAD_GENERIC_ERROR, dwError);
            return false;
          }
#pragma warning(suppress: 26472)
          const auto t = static_cast<double>(((static_cast<__int64>(ft.dwHighDateTime) << 32) + ft.dwLowDateTime - (static_cast<__int64>(dwStartTicks.dwHighDateTime) << 32) - dwStartTicks.dwLowDateTime) / 10000);
#pragma warning(suppress: 26472)
          const auto q = static_cast<double>(static_cast<LONGLONG>(nTotalBytesRead)) / t;

          if (q > m_dbLimit)
              Sleep(static_cast<DWORD>(((q*t)/m_dbLimit) - t));
        }
      }

      //Call the virtual function which reports progress as the download is occuring
      #pragma warning(suppress: 6102)
      OnProgress(nTotalBytesRead, bGotFileSize, nContentLength + m_nStartPos);
    }
  }
  while (dwBytesRead && !Abort());

  //We're finished
  return true;
}

CString CHTTPDownloader::GetOptionalHeaders()
{
  //Allows you to further customize the HTTP headers which CHTTPDownloader sends

  //By default, we create the Range header here if required
  CString sHeaders;
  if (m_nStartPos != 0)  //we will build the range request.
      sHeaders.Format(_T("Range: bytes=%I64u-\r\n"), m_nStartPos);

  return sHeaders;
}

#pragma warning(suppress: 26440)
void CHTTPDownloader::OnGotContentLength(_In_ ULONGLONG nContentLength)
{
#ifndef _DEBUG
  UNREFERENCED_PARAMETER(nContentLength);
#endif //#ifndef _DEBUG

  //Just trace out the value, derived classes are free to implement something more useful
  TRACE(_T("Got a Content-Length header value of %I64u\n"), nContentLength);
}

#pragma warning(suppress: 26440)
void CHTTPDownloader::OnProgress(_In_ ULONGLONG nTotalBytesRead, _In_ bool bGotFileSize, _In_ ULONGLONG nFileSize)
{
#ifndef _DEBUG
  UNREFERENCED_PARAMETER(nTotalBytesRead);
  UNREFERENCED_PARAMETER(bGotFileSize);
  UNREFERENCED_PARAMETER(nFileSize);
#endif //#ifndef _DEBUG

  //Just trace out the progress, derived classes are free to implement something more useful
  if (bGotFileSize)
    TRACE(_T("Received %I64u of %I64u bytes\n"), nTotalBytesRead, nFileSize - m_nStartPos);
  else
    TRACE(_T("Received %I64u bytes\n"), nTotalBytesRead);
}

bool CHTTPDownloader::Abort() noexcept
{
  return m_bAbort;
}

void CHTTPDownloader::SetAbort()
{
  m_bAbort = true;

  //Also release the Wininet handles, this should cause any blocking calls to Wininet to fail with errors
  ReleaseHandles();
}

void CHTTPDownloader::HandleError(_In_ UINT nID, _In_ DWORD dwError)
{
  //Just trace out the error, derived classes are free to implement something more useful
  CString sError;
  if (dwError)
    sError = GetErrorMessage(dwError);
  else
    sError = GetErrorMessage(GetLastError());
  CString sErrorMsg;
  AfxFormatString1(sErrorMsg, nID, sError);
  TRACE(_T("%s\n"), sErrorMsg.GetString());
}

void CHTTPDownloader::SetStatus(_In_ UINT nID)
{
  //Just load up the string and pass to the other version of the function
  CString sStatus;
  if (sStatus.LoadString(nID))
    SetStatus(sStatus);
}

void CHTTPDownloader::SetStatus(_In_ UINT nID, _In_z_ LPCTSTR lpsz1)
{
  //Just form out the string and pass to the other version of the function
  CString sStatus;
  AfxFormatString1(sStatus, nID, lpsz1);
  SetStatus(sStatus);
}

#pragma warning(suppress: 26440)
void CHTTPDownloader::SetStatus(_In_z_ LPCTSTR pszStatus)
{
#ifndef _DEBUG
  UNREFERENCED_PARAMETER(pszStatus);
#endif //#ifndef _DEBUG

  //Just trace out the string, derived classes are free to implement something more useful
  TRACE(_T("CHTTPDownloader::SetStatus, %s\n"), pszStatus);
}

void CHTTPDownloader::HandleStatusCode(_In_ UINT nID, _In_ DWORD dwStatusCode)
{
  //Just trace out the string, derived classes are free to implement something more useful
  CString sStatusCode;
  sStatusCode.Format(_T("%u"), dwStatusCode);
  CString sMsg;
  AfxFormatString1(sMsg, nID, sStatusCode);
  TRACE(sMsg);
}

#pragma warning(suppress: 26440)
bool CHTTPDownloader::HandlePrompt(_Inout_ DWORD& /*dwError*/)
{
  //By default in the base class we do not support prompting
  return false;
}

CString CHTTPDownloader::GetErrorMessage(_In_ DWORD dwError)
{
  //use the Wininet dll also to find error strings
#pragma warning(suppress: 26462)
  HMODULE hWininet = GetModuleHandle(_T("WININET.DLL"));

  CString rVal;
#pragma warning(suppress: 26429)
  LPTSTR pstrError = rVal.GetBuffer(4096);
  LPTSTR lpBuffer = nullptr;
#pragma warning(suppress: 26490)
  const DWORD dwReturn = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
                                       FORMAT_MESSAGE_FROM_HMODULE, hWininet, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT), 
                                       reinterpret_cast<LPTSTR>(&lpBuffer), 0, nullptr);
  if (dwReturn == 0)
    *pstrError = _T('\0');
  else
  {
    ATL::Checked::tcsncpy_s(pstrError, 4096, lpBuffer, _TRUNCATE);
    LocalFree(lpBuffer);
  }
  rVal.ReleaseBuffer();

  return rVal;
}

_Return_type_success_(return != false) bool CHTTPDownloader::QueryStatusNumber(_In_ HINTERNET hInternet, _In_ DWORD dwFlag, _Out_ DWORD& dwCode) noexcept
{
  dwCode = 0;
  DWORD dwSize = sizeof(DWORD);
  return (HttpQueryInfo(hInternet, dwFlag | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, nullptr) != FALSE);
}

_Return_type_success_(return != false) bool CHTTPDownloader::QueryStatusCode(_In_ HINTERNET hInternet, _Out_ DWORD& dwCode) noexcept
{
  return QueryStatusNumber(hInternet, HTTP_QUERY_STATUS_CODE, dwCode);
}

_Return_type_success_(return != false) bool CHTTPDownloader::QueryContentLength(_In_ HINTERNET hInternet, _Out_ ULONGLONG& dwCode)
{
  CString sContentLength;
  DWORD dwSize = 32;
  const bool bSuccess = (HttpQueryInfo(hInternet, HTTP_QUERY_CONTENT_LENGTH, sContentLength.GetBuffer(32), &dwSize, nullptr) != FALSE);
  sContentLength.ReleaseBuffer();
  if (bSuccess)
    dwCode = _ttoi64(sContentLength);

  return bSuccess;
}

DWORD CHTTPDownloader::GetOpenRequestFlags() noexcept
{
  DWORD dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION;
  if (m_dwServiceType == AFX_INET_SERVICE_HTTPS) 
    dwFlags |= INTERNET_FLAG_SECURE;
  if (m_bNoURLRedirect)
    dwFlags |= INTERNET_FLAG_NO_AUTO_REDIRECT;

  return dwFlags;
}

void CHTTPDownloader::_OnWininetStatusCallBack(_In_ HINTERNET hInternet, _In_ DWORD_PTR dwContext, _In_ DWORD dwInternetStatus,
                                               _In_opt_ LPVOID lpvStatusInformation, _In_ DWORD dwStatusInformationLength)
{
  //Convert from the SDK C world to the C++ world
#pragma warning(suppress: 26490)
  auto pThis = reinterpret_cast<CHTTPDownloader*>(dwContext);
#pragma warning(suppress: 26496)
  AFXASSUME(pThis != nullptr);
#pragma warning(suppress: 26486)
  pThis->OnWininetStatusCallBack(hInternet, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
}

#pragma warning(suppress: 26440)
void CHTTPDownloader::OnWininetStatusCallBack(_In_ HINTERNET /*hInternet*/, _In_ DWORD /*dwInternetStatus*/, _In_opt_ LPVOID /*lpvStatusInformation*/, _In_ DWORD /*dwStatusInformationLength*/)
{
  //The base class does nothing with this information, derived classes are free to implement something more useful
}
