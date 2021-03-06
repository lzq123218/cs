; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXRichEditCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SCC.h"
LastPage=0

ClassCount=13
Class1=CSCCApp
Class2=CXRichEditDoc
Class3=CXRichEditView
Class4=CMainFrame

ResourceCount=11
Resource1=IDR_MENU_SHELL
Resource2=IDR_SCC_TOOL
Class5=CAboutDlg
Resource4=IDD_DIALOG_FILTER
Resource3=IDR_TOOLBAR_SHELL
Class6=CXRichEditCtrl
Class7=CSendFrameWnd
Class8=CSCCView
Class9=CSCCSendEdit
Resource5=IDR_TOOLBAR_CS
Resource6=IDD_DIALOG_CYC
Resource7=IDR_MAINFRAME
Class10=CDlgSend
Resource8=IDD_ABOUTBOX
Class11=CTransmit
Resource9=IDD_DIALOG_TRANSMIT
Class12=CDlgFilter
Resource10=IDD_DIALOG_SEND
Class13=CDlgAutoSave
Resource11=IDD_DIALOG_SAVE

[CLS:CSCCApp]
Type=0
HeaderFile=SCC.h
ImplementationFile=SCC.cpp
Filter=N
LastObject=CSCCApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
LastObject=CMainFrame
BaseClass=CGuiFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=SCC.cpp
ImplementationFile=SCC.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_EMAIL,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_GUILIB,static,1342308352
Control9=IDC_STATIC_GUILIB2,static,1342308352
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_XSAVE
Command3=ID_FILE_AUTOSAVE
Command4=ID_FILE_OPENS
Command5=ID_FILE_SAVESEND
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_PASTE_SPECIAL
Command16=ID_EDIT_SELECT_ALL
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_OLE_INSERT_NEW
Command21=ID_OLE_EDIT_LINKS
Command22=ID_OLE_EDIT_PROPERTIES
Command23=ID_OLE_VERB_FIRST
Command24=ID_SCC_PAUSE
Command25=ID_SHOW_FILTER
Command26=ID_VIEW_SCC_PORT
Command27=ID_VIEW_SCC_SEND
Command28=ID_VIEW_SCC_TIME
Command29=ID_SCC_CLEARDATA
Command30=ID_SCC_READONLY
Command31=ID_VIEW_WRAP
Command32=ID_SCC_OPEN
Command33=ID_SCC_SET_OPTION
Command34=ID_SCC_SENDLINE
Command35=ID_SCC_GONEXT
Command36=ID_SCC_ASCRECV
Command37=ID_SCC_ASCSEND
Command38=ID_SCC_ADDSTX
Command39=ID_SCC_ADDETX
Command40=ID_SCC_ADDENTER
Command41=ID_SCC_ADDECHO
Command42=ID_SCC_CYCSEND
Command43=ID_SCC_TRIGGER
Command44=ID_ADVANCE_SEND
Command45=ID_SCC_TRANSMIT
Command46=ID_CS_ADDSUM
Command47=ID_CS_ADDSUMWORD
Command48=ID_CS_MODBUS
Command49=ID_CS_CRC_CCITT16
Command50=ID_CS_CRC_CCITT8
Command51=ID_CS_CRC_ANSI16
Command52=ID_CS_CRC_CDT
Command53=ID_VIEW_TOOLBAR
Command54=ID_VIEW_STATUS_BAR
Command55=ID_VIEW_SFWND
Command56=IDR_SCC_TOOL
Command57=ID_ALWAYSONTOP
Command58=ID_VIEW_CENTER
Command59=ID_VIEW_TOPHARF
Command60=ID_VIEW_BOTTOMHARF
Command61=ID_VIEW_LEFTHARF
Command62=ID_VIEW_RIGHTHARF
Command63=ID_APP_ABOUT
CommandCount=63

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_SELECT_ALL
Command2=IDR_SCC_TOOL
Command3=ID_EDIT_COPY
Command4=ID_SCC_CLEARDATA
Command5=ID_EDIT_FIND
Command6=ID_EDIT_REPLACE
Command7=ID_CS_MODBUS
Command8=ID_FILE_OPEN
Command9=ID_FILE_PRINT
Command10=ID_SCC_READONLY
Command11=ID_FILE_XSAVE
Command12=ID_ALWAYSONTOP
Command13=ID_EDIT_PASTE
Command14=ID_CANCEL_EDIT_CNTR
Command15=ID_CS_ADDSUM
Command16=ID_SCC_SENDLINE
Command17=ID_EDIT_REPEAT
Command18=ID_VIEW_SFWND
Command19=ID_SCC_OPEN
Command20=ID_ADVANCE_SEND
Command21=ID_SCC_PAUSE
Command22=ID_OLE_EDIT_PROPERTIES
Command23=ID_EDIT_CUT
Command24=ID_EDIT_UNDO
CommandCount=24

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_XSAVE
Command2=ID_VIEW_SFWND
Command3=ID_SCC_OPEN
Command4=ID_SCC_PAUSE
Command5=ID_SCC_CLEARDATA
Command6=ID_SHOW_FILTER
Command7=ID_SCC_SENDLINE
Command8=ID_SCC_CYCSEND
Command9=ID_SCC_TRIGGER
Command10=ID_SCC_ASCRECV
Command11=ID_SCC_ASCSEND
CommandCount=11

[TB:IDR_SCC_TOOL]
Type=1
Class=CMainFrame
Command1=ID_SCC_SET_COM
Command2=ID_SCC_SET_BAUD
Command3=ID_SCC_SET_PARITY
Command4=ID_SCC_SET_DATA
Command5=ID_SCC_SET_STOP
Command6=ID_SCC_SET_RTO
Command7=ID_SCC_SET_FLOW
Command8=ID_SCC_SET_ADVANCE
CommandCount=8

[TB:IDR_TOOLBAR_SHELL]
Type=1
Class=?
Command1=ID_SCC_OPEN
Command2=ID_SCC_OPEN
Command3=ID_VIEW_WRAP
Command4=ID_SCC_READONLY
Command5=ID_FILE_PRINT
Command6=ID_APP_EXIT
Command7=ID_VIEW_CENTER
Command8=ID_VIEW_TOPHARF
Command9=ID_VIEW_BOTTOMHARF
Command10=ID_VIEW_LEFTHARF
Command11=ID_VIEW_RIGHTHARF
Command12=ID_FILE_OPEN
CommandCount=12

[CLS:CXRichEditCtrl]
Type=0
HeaderFile=XRichEditCtrl.h
ImplementationFile=XRichEditCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CXRichEditCtrl

[CLS:CSendFrameWnd]
Type=0
HeaderFile=SendFrameWnd.h
ImplementationFile=SendFrameWnd.cpp
BaseClass=CGuiControlBar
Filter=W
VirtualFilter=WC
LastObject=CSendFrameWnd

[CLS:CXRichEditView]
Type=0
HeaderFile=xricheditview.h
ImplementationFile=xricheditview.cpp
BaseClass=CRichEditView
LastObject=CXRichEditView

[CLS:CXRichEditDoc]
Type=0
HeaderFile=xricheditview.h
ImplementationFile=xricheditview.cpp
BaseClass=CRichEditDoc
LastObject=CXRichEditDoc
Filter=N
VirtualFilter=DC

[CLS:CSCCView]
Type=0
HeaderFile=SCCView.h
ImplementationFile=SCCView.cpp
BaseClass=CEditView
Filter=C

[CLS:CSCCSendEdit]
Type=0
HeaderFile=SCCSendEdit.h
ImplementationFile=SCCSendEdit.cpp
BaseClass=CXRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CSCCSendEdit

[TB:IDR_TOOLBAR_CS]
Type=1
Class=?
Command1=ID_CS_ADDSUM
Command2=ID_CS_ADDSUMWORD
Command3=ID_CS_MODBUS
Command4=ID_CS_CRC_CCITT16
Command5=ID_CS_CRC_CCITT8
Command6=ID_CS_CRC_ANSI16
Command7=ID_CS_CRC_CDT
Command8=ID_CS_1
Command9=ID_CS_2
Command10=ID_CS_3
Command11=ID_CS_4
Command12=ID_CS_5
Command13=ID_CS_6
Command14=ID_CS_7
CommandCount=14

[MNU:IDR_MENU_SHELL]
Type=1
Class=?
Command1=ID_SCC_DEFAULT
CommandCount=1

[DLG:IDD_DIALOG_CYC]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_SEND]
Type=1
Class=CDlgSend
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_LINE,button,1342308361
Control3=IDC_RADIO_LINES,button,1342177289
Control4=IDC_RADIO_CURLINE,button,1342308361
Control5=IDC_RADIO_ONELINE,button,1342177289
Control6=IDC_EDIT_ONELINE,edit,1342242944
Control7=IDC_EDIT_MULTILINES,edit,1342242944
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_TIME,edit,1342242944
Control10=IDC_BUTTON_USE,button,1342242816
Control11=IDC_BUTTON_HIDE,button,1342242816
Control12=IDC_EDIT_MULTILINES2,edit,1342242944
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_LIST_TRIGGER,SysListView32,1350631433
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_TRIGGER,edit,1342242944
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352

[CLS:CDlgSend]
Type=0
HeaderFile=DlgSend.h
ImplementationFile=DlgSend.cpp
BaseClass=CDialog
Filter=W
LastObject=CDlgSend
VirtualFilter=dWC

[DLG:IDD_DIALOG_TRANSMIT]
Type=1
Class=CTransmit
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_COMSRC,edit,1342242816
Control6=IDC_EDIT_COMDEST,edit,1342242944
Control7=IDC_CHECK_COM,button,1342275587

[CLS:CTransmit]
Type=0
HeaderFile=Transmit.h
ImplementationFile=Transmit.cpp
BaseClass=CDialog
Filter=D
LastObject=CTransmit
VirtualFilter=dWC

[DLG:IDD_DIALOG_FILTER]
Type=1
Class=CDlgFilter
ControlCount=9
Control1=IDC_RADIO_ALL,button,1342308361
Control2=IDC_RADIO_CUR,button,1342177289
Control3=IDC_LIST_FILTER,SysListView32,1350631433
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BUTTON_FILTER,button,1342242816
Control8=IDC_BUTTON_EXIT,button,1342242816
Control9=IDC_CHECK_FILTER,button,1342242819

[CLS:CDlgFilter]
Type=0
HeaderFile=DlgFilter.h
ImplementationFile=DlgFilter.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgFilter
VirtualFilter=dWC

[DLG:IDD_DIALOG_SAVE]
Type=1
Class=CDlgAutoSave
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_BROWSE_EDIT,edit,1342242944
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECK_AS,button,1342242819
Control6=IDC_EDIT_ASTIME,edit,1342242944
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK_CLEAR,button,1342242819

[CLS:CDlgAutoSave]
Type=0
HeaderFile=DlgAutoSave.h
ImplementationFile=DlgAutoSave.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BROWSE_EDIT
VirtualFilter=dWC

