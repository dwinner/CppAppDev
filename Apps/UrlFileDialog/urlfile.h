// urlfile.h : main header file for the URLFILE application
//

#if !defined(AFX_URLFILE_H__BB9CC6D1_27C9_11D3_ACCC_00104B247756__INCLUDED_)
#define AFX_URLFILE_H__BB9CC6D1_27C9_11D3_ACCC_00104B247756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUrlFileApp:
// See urlfile.cpp for the implementation of this class
//

class CUrlFileApp : public CWinApp
{
public:
	CUrlFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUrlFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUrlFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLFILE_H__BB9CC6D1_27C9_11D3_ACCC_00104B247756__INCLUDED_)
