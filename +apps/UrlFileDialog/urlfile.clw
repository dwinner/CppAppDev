; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUrlFileDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "urlfile.h"

ClassCount=3
Class1=CUrlfileApp
Class2=CUrlFileDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_URLFILE_DIALOG

[CLS:CUrlfileApp]
Type=0
HeaderFile=urlfile.h
ImplementationFile=urlfile.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=urlfileDlg.h
ImplementationFile=urlfileDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_URLFILE_DIALOG]
Type=1
Class=CUrlFileDlg
ControlCount=5
Control1=IDC_URL,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PROGRESS,edit,1353713860

[CLS:CUrlFileDlg]
Type=0
HeaderFile=urlfiledlg.h
ImplementationFile=urlfiledlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROGRESS

