# Microsoft Developer Studio Project File - Name="ProgrammeTechnicFund" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ProgrammeTechnicFund - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProgrammeTechnicFund.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProgrammeTechnicFund.mak" CFG="ProgrammeTechnicFund - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProgrammeTechnicFund - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProgrammeTechnicFund - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProgrammeTechnicFund - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ProgrammeTechnicFund - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProgrammeTechnicFund - Win32 Release"
# Name "ProgrammeTechnicFund - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ACE_Frame.cpp
# End Source File
# Begin Source File

SOURCE=.\BackgroundUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlRegedit.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOperateClass.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOperateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFund.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFund.rc
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFundDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFundView.cpp
# End Source File
# Begin Source File

SOURCE=.\ShareResource.cpp
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UsingMethodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UsingSocketCommunication.cpp
# End Source File
# Begin Source File

SOURCE=.\VisitDatabaseInterface.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ACE_Frame.h
# End Source File
# Begin Source File

SOURCE=.\BackgroundUtil.h
# End Source File
# Begin Source File

SOURCE=.\ControlRegedit.h
# End Source File
# Begin Source File

SOURCE=.\ControlSystem.h
# End Source File
# Begin Source File

SOURCE=.\FileOperateClass.h
# End Source File
# Begin Source File

SOURCE=.\FileOperateDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.h
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFund.h
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFundDoc.h
# End Source File
# Begin Source File

SOURCE=.\ProgrammeTechnicFundView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShareResource.h
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UsingMethodDlg.h
# End Source File
# Begin Source File

SOURCE=.\UsingSocketCommunication.h
# End Source File
# Begin Source File

SOURCE=.\VisitDatabaseInterface.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ProgrammeTechnicFund.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProgrammeTechnicFund.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ProgrammeTechnicFundDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
