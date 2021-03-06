# Microsoft Developer Studio Generated NMAKE File, Based on DrawServ.dsp
!IF "$(CFG)" == ""
CFG=DrawServ - Win32 Release
!MESSAGE No configuration specified. Defaulting to DrawServ - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DrawServ - Win32 Release" && "$(CFG)" != "DrawServ - Win32 Debug" && "$(CFG)" != "DrawServ - Win32 Unicode Release" && "$(CFG)" != "DrawServ - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DrawServ.mak" CFG="DrawServ - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DrawServ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "DrawServ - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DrawServ - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DrawServ.exe" ".\.\Release\reg_exe.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DrawServ.obj"
	-@erase "$(INTDIR)\DrawServ.res"
	-@erase "$(INTDIR)\predraw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DrawServ.exe"
	-@erase ".\DrawServ.h"
	-@erase ".\DrawServ.tlb"
	-@erase ".\DrawServ_i.c"
	-@erase ".\.\Release\reg_exe.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawServ.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DrawServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\DrawServ.pdb" /machine:I386 /out:"$(OUTDIR)\DrawServ.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DrawServ.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\predraw.obj" \
	"$(INTDIR)\DrawServ.res"

"$(OUTDIR)\DrawServ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\DrawServ.exe
InputPath=.\Release\DrawServ.exe
SOURCE=$(InputPath)

"$(OutDir)\reg_exe.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done!
<< 
	

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DrawServ.exe" "$(OUTDIR)\predraw.pch" "$(OUTDIR)\DrawServ.bsc" ".\.\Debug\reg_exe.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DrawObj.sbr"
	-@erase "$(INTDIR)\DrawServ.obj"
	-@erase "$(INTDIR)\DrawServ.res"
	-@erase "$(INTDIR)\DrawServ.sbr"
	-@erase "$(INTDIR)\predraw.obj"
	-@erase "$(INTDIR)\predraw.pch"
	-@erase "$(INTDIR)\predraw.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DrawServ.bsc"
	-@erase "$(OUTDIR)\DrawServ.exe"
	-@erase "$(OUTDIR)\DrawServ.ilk"
	-@erase "$(OUTDIR)\DrawServ.pdb"
	-@erase ".\DrawServ.h"
	-@erase ".\DrawServ.tlb"
	-@erase ".\DrawServ_i.c"
	-@erase ".\.\Debug\reg_exe.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawServ.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DrawServ.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DrawServ.sbr" \
	"$(INTDIR)\DrawObj.sbr" \
	"$(INTDIR)\predraw.sbr"

"$(OUTDIR)\DrawServ.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\DrawServ.pdb" /debug /machine:I386 /out:"$(OUTDIR)\DrawServ.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DrawServ.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\predraw.obj" \
	"$(INTDIR)\DrawServ.res"

"$(OUTDIR)\DrawServ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\DrawServ.exe
InputPath=.\Debug\DrawServ.exe
SOURCE=$(InputPath)

"$(OutDir)\reg_exe.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done!
<< 
	

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\DrawServ.exe" ".\.\ReleaseU\reg_exe.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DrawServ.obj"
	-@erase "$(INTDIR)\DrawServ.res"
	-@erase "$(INTDIR)\predraw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DrawServ.exe"
	-@erase ".\DrawServ.h"
	-@erase ".\DrawServ.tlb"
	-@erase ".\DrawServ_i.c"
	-@erase ".\.\ReleaseU\reg_exe.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawServ.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DrawServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\DrawServ.pdb" /machine:I386 /out:"$(OUTDIR)\DrawServ.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DrawServ.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\predraw.obj" \
	"$(INTDIR)\DrawServ.res"

"$(OUTDIR)\DrawServ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\ReleaseU
TargetPath=.\ReleaseU\DrawServ.exe
InputPath=.\ReleaseU\DrawServ.exe
SOURCE=$(InputPath)

"$(OutDir)\reg_exe.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done!
<< 
	

!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\DrawServ.exe" ".\.\DebugU\reg_exe.trg"


CLEAN :
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DrawServ.obj"
	-@erase "$(INTDIR)\DrawServ.res"
	-@erase "$(INTDIR)\predraw.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DrawServ.exe"
	-@erase "$(OUTDIR)\DrawServ.ilk"
	-@erase "$(OUTDIR)\DrawServ.pdb"
	-@erase ".\DrawServ.h"
	-@erase ".\DrawServ.tlb"
	-@erase ".\DrawServ_i.c"
	-@erase ".\.\DebugU\reg_exe.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\DrawServ.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DrawServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\DrawServ.pdb" /debug /machine:I386 /out:"$(OUTDIR)\DrawServ.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DrawServ.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\predraw.obj" \
	"$(INTDIR)\DrawServ.res"

"$(OUTDIR)\DrawServ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\DrawServ.exe
InputPath=.\DebugU\DrawServ.exe
SOURCE=$(InputPath)

"$(OutDir)\reg_exe.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	$(TargetPath) /RegServer 
	echo reg_exe exec. time > "$(OutDir)\reg_exe.trg" 
	echo Server registration done!
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DrawServ.dep")
!INCLUDE "DrawServ.dep"
!ELSE 
!MESSAGE Warning: cannot find "DrawServ.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DrawServ - Win32 Release" || "$(CFG)" == "DrawServ - Win32 Debug" || "$(CFG)" == "DrawServ - Win32 Unicode Release" || "$(CFG)" == "DrawServ - Win32 Unicode Debug"
SOURCE=.\DrawObj.cpp

!IF  "$(CFG)" == "DrawServ - Win32 Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"


"$(INTDIR)\DrawObj.obj"	"$(INTDIR)\DrawObj.sbr" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h"


!ENDIF 

SOURCE=.\DrawServ.cpp

!IF  "$(CFG)" == "DrawServ - Win32 Release"


"$(INTDIR)\DrawServ.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h" ".\DrawServ_i.c"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"


"$(INTDIR)\DrawServ.obj"	"$(INTDIR)\DrawServ.sbr" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h" ".\DrawServ_i.c"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"


"$(INTDIR)\DrawServ.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h" ".\DrawServ_i.c"


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"


"$(INTDIR)\DrawServ.obj" : $(SOURCE) "$(INTDIR)" ".\DrawServ.h" ".\DrawServ_i.c"


!ENDIF 

SOURCE=.\DrawServ.idl

!IF  "$(CFG)" == "DrawServ - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\DrawServ.tlb" /h "DrawServ.h" /iid "DrawServ_i.c" /win32 

".\DrawServ.tlb"	".\DrawServ.h"	".\DrawServ_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\DrawServ.tlb" /h "DrawServ.h" /iid "DrawServ_i.c" /win32 

".\DrawServ.tlb"	".\DrawServ.h"	".\DrawServ_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb ".\DrawServ.tlb" /h "DrawServ.h" /iid "DrawServ_i.c" /win32 

".\DrawServ.tlb"	".\DrawServ.h"	".\DrawServ_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb ".\DrawServ.tlb" /h "DrawServ.h" /iid "DrawServ_i.c" /win32 

".\DrawServ.tlb"	".\DrawServ.h"	".\DrawServ_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DrawServ.rc

"$(INTDIR)\DrawServ.res" : $(SOURCE) "$(INTDIR)" ".\DrawServ.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\predraw.cpp

!IF  "$(CFG)" == "DrawServ - Win32 Release"

CPP_SWITCHES=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\predraw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\predraw.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\predraw.obj"	"$(INTDIR)\predraw.sbr"	"$(INTDIR)\predraw.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\predraw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DrawServ - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\predraw.pch" /YX"predraw.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\predraw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

