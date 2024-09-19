// urlfileDlg.h : header file
// Written by chensu
//

#if !defined(AFX_URLFILEDLG_H__BB9CC6D3_27C9_11D3_ACCC_00104B247756__INCLUDED_)
#define AFX_URLFILEDLG_H__BB9CC6D3_27C9_11D3_ACCC_00104B247756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	UF_BINDSTATUS_FIRST = BINDSTATUS_FINDINGRESOURCE,
	UF_BINDSTATUS_LAST = BINDSTATUS_ACCEPTRANGES
};

/////////////////////////////////////////////////////////////////////////////
// CUrlFileDlg dialog

class CUrlFileDlg : public CDialog
{
// Construction
public:
	CUrlFileDlg(CWnd* pParent = NULL);	// standard constructor

	struct DOWNLOADSTATUS
	{
		ULONG ulProgress;
		ULONG ulProgressMax;
		ULONG ulStatusCode;
		LPCWSTR szStatusText;
	};

// Dialog Data
	//{{AFX_DATA(CUrlFileDlg)
	enum { IDD = IDD_URLFILE_DIALOG };
	CButton	m_btnDownloadStop;
	CButton	m_btnExit;
	CEdit	m_editURL;
	CString	m_strURL;
	CEdit	m_editProgress;
	CString	m_strProgress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUrlFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUrlFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnEndDownload(WPARAM, LPARAM);
	afx_msg LRESULT OnDisplayStatus(WPARAM, LPARAM lParam);
	afx_msg void OnMaxtextProgress();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	struct DOWNLOADPARAM
	{
		HWND hWnd;
		HANDLE hEventStop;
		CString strURL;
		CString strFileName;
	};

	CWinThread *m_pDownloadThread;
	DOWNLOADPARAM m_downloadParam;
	CEvent m_eventStop;
	
	void ChangeUIDownloading(bool bDownloading = true);
	static UINT Download(LPVOID pParam);
};

/////////////////////////////////////////////////////////////////////////////
// CBSCallbackImpl

class CBSCallbackImpl : public IBindStatusCallback
{
public:
	CBSCallbackImpl(HWND hWnd, HANDLE hEventStop);

	// IUnknown methods
	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();

	// IBindStatusCallback methods
	STDMETHOD(OnStartBinding)(DWORD, IBinding *);
	STDMETHOD(GetPriority)(LONG *);
	STDMETHOD(OnLowResource)(DWORD);
	STDMETHOD(OnProgress)(ULONG ulProgress,
						  ULONG ulProgressMax,
						  ULONG ulStatusCode,
						  LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT, LPCWSTR);
	STDMETHOD(GetBindInfo)(DWORD *, BINDINFO *);
	STDMETHOD(OnDataAvailable)(DWORD, DWORD, FORMATETC *, STGMEDIUM *);
	STDMETHOD(OnObjectAvailable)(REFIID, IUnknown *);

protected:
	ULONG m_ulObjRefCount;

private:
	HWND m_hWnd;
	HANDLE m_hEventStop;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLFILEDLG_H__BB9CC6D3_27C9_11D3_ACCC_00104B247756__INCLUDED_)
