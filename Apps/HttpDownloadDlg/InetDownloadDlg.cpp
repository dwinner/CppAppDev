#include "stdafx.h"
#include "InetDownload.h"
#include "InetDownloadDlg.h"
#include "HTTPDownloadDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CInetDownloadDlg, CDialog) //NOLINT(modernize-avoid-c-arrays)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_DOWNLOAD, &CInetDownloadDlg::OnDownload)
END_MESSAGE_MAP()

#pragma warning(suppress: 26455)
CInetDownloadDlg::CInetDownloadDlg(_In_opt_ CWnd* pParent) : CDialog(CInetDownloadDlg::IDD, pParent),
                                                             m_dwOffset(0),
                                                             m_nConnection(static_cast<int>(CHTTPDownloader::ConnectionType::UsePreConfig)),
                                                             m_bPromptForFileOverwrite(FALSE),
                                                             m_bPromptForHTTPDetails(FALSE),
                                                             m_bPromptForProxyDetails(FALSE),
                                                             m_dbLimit(0.0),
                                                             m_bNoURLRedirect(FALSE),
                                                             m_sAcceptTypes(_T("*/*")),
                                                             m_bHTTPPreauthentication(TRUE),
                                                             m_bProxyPreauthentication(TRUE),
                                                             m_bPromptForCertificate(FALSE),
                                                             m_bIgnoreCertificateRevocationProblems(FALSE),
                                                             m_bIgnoreUnknownCertificateAuthorityProblems(FALSE),
                                                             m_bIgnoreIncorrectUsageProblems(FALSE),
                                                             m_bIgnoreCertificateCommonNameProblems(FALSE),
                                                             m_bIgnoreCertificateDateProblems(FALSE),
                                                             m_bIgnoreHTTPSToHTTPRedirectErrors(FALSE),
                                                             m_bIgnoreHTTPToHTTPSRedirectErrors(FALSE),
                                                             m_hIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME))
{
}

#pragma warning(suppress: 26429)
void CInetDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
  __super::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_FILE, m_sFile);
  DDX_Text(pDX, IDC_HTTP_PASSWORD, m_sHTTPPassword);
  DDX_Text(pDX, IDC_PROXY_PASSWORD, m_sProxyPassword);
  DDX_Text(pDX, IDC_URL, m_sURL);
  DDX_Text(pDX, IDC_HTTP_USER, m_sHTTPUserName);
  DDX_Text(pDX, IDC_PROXY_USER, m_sProxyUserName);
  DDX_Text(pDX, IDC_OFFSET, m_dwOffset);
  DDX_CBIndex(pDX, IDC_CONNECTION, m_nConnection);
  DDX_Check(pDX, IDC_PROMPT_FILE_OVERWRITE, m_bPromptForFileOverwrite);
  DDX_Check(pDX, IDC_PROMPT_FOR_HTTP_DETAILS, m_bPromptForHTTPDetails);
  DDX_Check(pDX, IDC_PROMPT_FOR_PROXY_DETAILS, m_bPromptForProxyDetails);
  DDX_Text(pDX, IDC_PROXYSERVER, m_sProxyServer);
  DDX_Text(pDX, IDC_LIMIT, m_dbLimit);
  DDV_MinMaxDouble(pDX, m_dbLimit, 0.0, 200000000.0);
  DDX_Check(pDX, IDC_NO_URL_REDIRECT, m_bNoURLRedirect);
  DDX_Text(pDX, IDC_ACCEPT_TYPES, m_sAcceptTypes);
  DDX_Check(pDX, IDC_HTTP_PREAUTHENTICATION, m_bHTTPPreauthentication);
  DDX_Check(pDX, IDC_PROXY_PREAUTHENTICATION, m_bProxyPreauthentication);
  DDX_Text(pDX, IDC_REFERRER, m_sReferrer);
  DDX_Check(pDX, IDC_PROMPT_CERTIFICATE, m_bPromptForCertificate);
  DDX_Check(pDX, IDC_IGNORE_REVOCATION_PROBLEMS, m_bIgnoreCertificateRevocationProblems);
  DDX_Check(pDX, IDC_IGNORE_UNKNOWN_CA, m_bIgnoreUnknownCertificateAuthorityProblems);
  DDX_Check(pDX, IDC_IGNORE_WRONG_USAGE, m_bIgnoreIncorrectUsageProblems);
  DDX_Check(pDX, IDC_IGNORE_CERT_CN_INVALID, m_bIgnoreCertificateCommonNameProblems);
  DDX_Check(pDX, IDC_IGNORE_CERT_DATE_INVALID, m_bIgnoreCertificateDateProblems);
  DDX_Check(pDX, IDC_IGNORE_REDIRECT_TO_HTTP_ERRORS, m_bIgnoreHTTPSToHTTPRedirectErrors);
  DDX_Check(pDX, IDC_IGNORE_REDIRECT_TO_HTTPS_ERRORS, m_bIgnoreHTTPToHTTPSRedirectErrors);
  if (pDX->m_bSaveAndValidate)
  {
    if (m_sURL.IsEmpty())
    {
      AfxMessageBox(_T("Please enter a non-empty URL to download"));
      pDX->PrepareEditCtrl(IDC_URL);
      pDX->Fail();
    }
    if (m_sFile.IsEmpty())
    {
      AfxMessageBox(_T("Please specify a file to download into"));
      pDX->PrepareEditCtrl(IDC_FILE);
      pDX->Fail();
    }
    if ((m_nConnection == static_cast<int>(CHTTPDownloader::ConnectionType::UseProxy)) && (m_sProxyServer.GetLength() == 0))
    {
      AfxMessageBox(_T("Please enter a non-empty Proxy Server"));
      pDX->PrepareEditCtrl(IDC_PROXYSERVER);
      pDX->Fail();
    }
  }
}

BOOL CInetDownloadDlg::OnInitDialog()
{
  __super::OnInitDialog();
  SetIcon(m_hIcon, TRUE);
  SetIcon(m_hIcon, FALSE);
  return TRUE;
}

#pragma warning(suppress: 26434)
void CInetDownloadDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this);

#pragma warning(suppress: 26490)
    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    //Center icon in client rectangle
    const int cxIcon = GetSystemMetrics(SM_CXICON);
    const int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    const int x = (rect.Width() - cxIcon + 1) / 2;
    const int y = (rect.Height() - cyIcon + 1) / 2;

    //Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
    __super::OnPaint();
}

#pragma warning(suppress: 26434)
HCURSOR CInetDownloadDlg::OnQueryDragIcon() noexcept
{
#pragma warning(suppress: 26473)
  return static_cast<HCURSOR>(m_hIcon);
}

void CInetDownloadDlg::OnDownload()
{
  if (UpdateData())
  {
    CHTTPDownloadDlg dlg;
    dlg.m_sURLToDownload = m_sURL;
    dlg.m_sFileToDownloadInto = m_sFile;
    dlg.m_nStartPos = m_dwOffset;
    dlg.m_sHTTPUserName = m_sHTTPUserName;
    dlg.m_sHTTPPassword = m_sHTTPPassword;
    dlg.m_sProxyUserName = m_sProxyUserName;
    dlg.m_sProxyPassword = m_sProxyPassword;
    dlg.m_ConnectionType = static_cast<CHTTPDownloader::ConnectionType>(m_nConnection);
    dlg.m_bPromptFileOverwrite = m_bPromptForFileOverwrite ? true : false;
    dlg.m_bPromptForProxyDetails = m_bPromptForProxyDetails ? true : false;
    dlg.m_bPromptForHTTPDetails = m_bPromptForHTTPDetails ? true : false;
    dlg.m_sProxyServer = m_sProxyServer;
    dlg.m_dbLimit = m_dbLimit;
    dlg.m_bNoURLRedirect = m_bNoURLRedirect ? true : false;
    dlg.m_sReferrer = m_sReferrer;
    dlg.m_bHTTPPreauthentication = m_bHTTPPreauthentication ? true : false;
    dlg.m_bProxyPreauthentication = m_bProxyPreauthentication ? true : false;
    dlg.m_sAcceptTypes = m_sAcceptTypes;
    dlg.m_bPromptForCertificateDetails = m_bPromptForCertificate ? true : false;
    dlg.m_bIgnoreCertificateRevocationProblems = m_bIgnoreCertificateRevocationProblems ? true : false;
    dlg.m_bIgnoreUnknownCertificateAuthorityProblems = m_bIgnoreUnknownCertificateAuthorityProblems ? true : false;
    dlg.m_bIgnoreIncorrectUsageProblems = m_bIgnoreIncorrectUsageProblems ? true : false;
    dlg.m_bIgnoreCertificateCommonNameProblems = m_bIgnoreCertificateCommonNameProblems ? true : false;
    dlg.m_bIgnoreCertificateDateProblems = m_bIgnoreCertificateDateProblems ? true : false;
    dlg.m_bIgnoreHTTPSToHTTPRedirectErrors = m_bIgnoreHTTPSToHTTPRedirectErrors ? true : false;
    dlg.m_bIgnoreHTTPToHTTPSRedirectErrors = m_bIgnoreHTTPToHTTPSRedirectErrors ? true : false;

#ifndef HTTPDOWNLOADER_NO_CERTIFICATE_SUPPORT    
    //uncomment this section of code if you would like to try out CHttpDownloader's support for programmatic selection of client certificates
    //Note that you should uncheck "Prompt for Certificate" in the UI to force programmatic selection as well as change the last parameter to
    //CertOpenStore to specify a certificate that you have installed.
    /*
    HCERTSTORE hStoreHandle = CertOpenStore(CERT_STORE_PROV_SYSTEM_A, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_SYSTEM_STORE_LOCAL_MACHINE, "Some_Certificate_Name");
    VERIFY(hStoreHandle);
    PCCERT_CONTEXT pCertContext = CertFindCertificateInStore(hStoreHandle, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR, L"JUPITER", nullptr);
    VERIFY(pCertContext);
    CertCloseStore(hStoreHandle, 0);
    dlg.SetClientCertificate(pCertContext);
    CertFreeCertificateContext(pCertContext);
    */
#endif

    if (dlg.DoModal() == IDOK)
      AfxMessageBox(_T("File has been downloaded"));
  }
}
