#pragma once


class CInetDownloadDlg2 : public CDialog
{
public:
//Constructors / Destructors
  CInetDownloadDlg2(_In_opt_ CWnd* pParent = nullptr);

protected:
//Member variables
  enum { IDD = IDD_INETDOWNLOAD_DIALOG };
  CString m_sFile;
  CString m_sHTTPPassword;
  CString m_sProxyPassword;
  CString m_sURL;
  CString m_sHTTPUserName;
  CString m_sProxyUserName;
  DWORD m_dwOffset;
  int m_nConnection;
  BOOL m_bPromptForFileOverwrite;
  BOOL m_bPromptForHTTPDetails;
  BOOL m_bPromptForProxyDetails;
  CString m_sProxyServer;
  double m_dbLimit;
  BOOL m_bNoURLRedirect;
  CString m_sAcceptTypes;
  BOOL m_bHTTPPreauthentication;
  BOOL m_bProxyPreauthentication;
  CString m_sReferrer;
  int m_nHTTPPreauth;
  int m_nProxyPreauth;
  BOOL m_bIgnoreUnknownCertificateAuthorityProblems;
  BOOL m_bIgnoreIncorrectUsageProblems;
  BOOL m_bIgnoreCertificateCommonNameProblems;
  BOOL m_bIgnoreCertificateDateProblems;
  HICON m_hIcon;

//Methods
  void DoDataExchange(CDataExchange* pDX) override;
  BOOL OnInitDialog() override;

//Message handlers
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon() noexcept;
  afx_msg void OnDownload();

  DECLARE_MESSAGE_MAP()
};
