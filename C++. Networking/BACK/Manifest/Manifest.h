// Manifest.h : main header file for the Manifest DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CManifestApp
// See Manifest.cpp for the implementation of this class
//

class CManifestApp : public CWinApp
{
public:
	CManifestApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
