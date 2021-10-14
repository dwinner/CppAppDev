#include "stdafx.h"
#include "InetDownload2.h"
#include "InetDownloadDlg2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma warning(suppress: 26426)
CInetDownload2App theApp;

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CInetDownload2App, CWinApp) //NOLINT(clang-diagnostic-unused-local-typedef, modernize-avoid-c-arrays)
END_MESSAGE_MAP()

BOOL CInetDownload2App::InitInstance()
{
  CInetDownloadDlg2 dlg;
  m_pMainWnd = &dlg;
  dlg.DoModal();
  return FALSE;
}
