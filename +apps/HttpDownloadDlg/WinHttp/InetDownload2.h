#pragma once

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif


#include "resource.h"


class CInetDownload2App : public CWinApp
{
public:
  BOOL InitInstance() override;

  DECLARE_MESSAGE_MAP()
};
