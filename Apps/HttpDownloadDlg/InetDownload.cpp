#include "stdafx.h"
#include "InetDownload.h"
#include "InetDownloadDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma warning(suppress: 26426)
CInetDownloadApp theApp;

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CInetDownloadApp, CWinApp) //NOLINT(clang-diagnostic-unused-local-typedef, modernize-avoid-c-arrays)
END_MESSAGE_MAP()

BOOL CInetDownloadApp::InitInstance()
{
  CInetDownloadDlg dlg;
  m_pMainWnd = &dlg;
  dlg.DoModal();
  return FALSE;
}
