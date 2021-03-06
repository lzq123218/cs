// ==================================================================
// 
//  handleref.h
//  
//  Created:       03.10.2004
//
//  Copyright (C) Peter Hauptmann 2004
//              
// ------------------------------------------------------------------
/// 
/// @file
/// Copyright (C) 2004 Peter Hauptmann. All rights reserved.
/// For updates, see http://www.codeproject.com/vcpp/stl/boostsmartptr.asps
/// 
/// This code may be used and distributed freely in source and 
/// compiled form, provided:
///     - copyright notice,  licence note and disclaimer remian unmodified
///     - all modifications to the original source, (including bug fixes)
///       are marked clearly as not being part of the original code 
/// 
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, 
/// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
/// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/// IN NO EVENT SHALL THE AUTHOR OR HIS CONTRIBUTORS BE LIABLE FOR ANY DAMAGES 
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
/// POSSIBILITY OF SUCH DAMAGE.
/// 
/// 
/// Wrapping windows Resource Handles into smart references.
/// 
/// boost::shared_ptr is required. see boost.org for details.
/// 
/// The following HandleRefs are defined:
/// 
/// - HIMAGELIST  ==> CImageListRef
/// - HMENU       ==> CMenuRef
/// - HANDLE      ==> CHandleRef
/// - HBITMAP     ==> CBitmapRef
/// - HBRUSH      ==> CBrushRef
/// - HPEN        ==> CPenRef
/// - HKEY        ==> CHKeyRef
/// 
/// \todo Write a custom CDCRef, that can be (a) Do Nothing, (b) DeleteDC, or (c) ReleaseDC
///     

#ifndef FILE_PH_HANDLEREF_H_200427719_INCLUDED_
#define FILE_PH_HANDLEREF_H_200427719_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// boost::shared_ptr is required for this file, see boost.org for details
#include <boost/shared_ptr.hpp> 

// ==================================================================
//  namespace nsHandleRefDetail
// ------------------------------------------------------------------
///
/// 
/// the nsHandleRefDetail namespace contains helper classes 
/// definitions for CHandleRef template, especially the custom deleters.
/// 
/// Deleters for new types should be placed in this namespace as well.
/// 
/// 
namespace nsHandleRefDetail
{

/// a "do nothing" deleter
struct CDeleterVoid
{
    void operator()(void * p) { }
};

/// Deleter calling DeleteObject
struct CDeleterGDI
{
    void operator()(void * p) { DeleteObject( (HGDIOBJ) p); }
};

/// Deleter calling ImageList_Destroy
struct CDeleterImageList
{
    void operator()(void * p) { ImageList_Destroy( (HIMAGELIST) p); }
};

/// Deleter calling CloseHandle
struct CDeleterHMENU
{
    void operator()(void * p) { DestroyMenu((HMENU) p); }
};


/// Deleter calling CloseHandle
struct CDeleterHANDLE
{
    void operator()(void * p) { CloseHandle( (HANDLE) p); }
};

/// Deleter for Registry keys
struct CDeleterHKEY
{
    void operator()(void * p) { RegCloseKey( (HKEY) p); }
};

struct CDeleterReleaseDC
{
    HWND wnd;
    CDeleterReleaseDC(HWND _wnd) : wnd(_wnd) {}

    void operator()(void * p) { ReleaseDC(wnd, (HDC) p); }
};

struct CDeleterDeleteDC
{
    void operator()(void * p) { DeleteDC( (HDC) p); }
};



} // namespace nsHandleRef_Detail



// ==================================================================
//  CHandleRefT::
// ------------------------------------------------------------------
///
/// Template class implementing a counted reference to a windows resource handle.
/// Usage rules are similar to a reference counted smart pointer.
/// 
/// \par template parameters:
///     - \c HDL : type of the resource handle (e.g. HFONT)
///     - \c DELETER : a functor releasing the resources of Handle of type HDL (e.g. 
///         a functor calling DeleteObject). The handle is passed as void *.
/// 
/// \par Automatic vs. manual handles
///     When constructing a HandleRef from a raw handle, you pass a \c bDeleteOnRelease flag
///     indicating if the handle should be released automatically when the last reference to it
///     goes out of scope. 
///     \n\n
///     For an automatic handle, assign the raw handle to a HandleRef immediately after construction, 
///     specifying bDeleteOnRelease=true. Then then pass it around only as HandleRef. 
///     This guarantees the handle is deleted when it is no longer used.
///     \n\n
///     For a manual handle, that you will delete yourself manually, or that must not be deleted,
///     specify \c bDeleteOnRelease=false.
///     \n\n
///     The idea here is that you can pass around, copy, store, or return a HandleRef, it remembers
///     it's deletion policy. 
/// 
/// \par Guidelines
///     Utility functions that merely receive and use a resource handle (without storing it) may 
///     use the raw handle as argument. However, when the Handle is stored (e.g. as a class member)
///     or used as a return value from a function, a HandleRef is recommended.
/// 
/// 
template <class HDL, class DELETER>
class CHandleRefT
{
protected:
    typedef boost::shared_ptr<void> tBoostSP;
    tBoostSP m_ptr;

public:

    /// creates a null handle
    CHandleRefT() {}

    /// Initialize the Handle Reference with a handle
    /// \param h : Handle to the resource to (of type \c HDL)
    /// \param deleteOnRelease [bool]: if true, the handle is deleted automatically (using the
    ///     specified \c DELETER) when the last HandleRef goes put of scope.
    explicit CHandleRefT(HDL h, bool deleteOnRelease)
    {
        if (deleteOnRelease)
            m_ptr = tBoostSP(h, DELETER());
        else
            m_ptr = tBoostSP(h, nsHandleRefDetail::CDeleterVoid());
    }

    /// automatic cast to the handle type
    operator HDL() const { return (HDL) m_ptr.get(); }

    void reset() { m_ptr.reset(); }
};


// ==================================================================
//  CDCRef::CDCRef
// ------------------------------------------------------------------
///
/// HDC needs special handling, since there are two valid cleanups
///  - DeleteDC
///  - ReleaseDC
/// 
class CDCRef 
{
protected:
    typedef boost::shared_ptr<void> tBoostSP;
    tBoostSP m_ptr;

    typedef nsHandleRefDetail::CDeleterVoid         Null;
    typedef nsHandleRefDetail::CDeleterDeleteDC     Delete;
    typedef nsHandleRefDetail::CDeleterReleaseDC    Release;

public:

    /// creates a null handle
    CDCRef() {}

    /// retrieve a device context handle
    operator HDC() const { return (HDC) m_ptr.get(); }


    /// initializes the handler
    /// For the second parameter, you can specify:
    ///  - CDCRef::Null for a null deleter (handle is not destroyed)
    ///  - CDCRef::Delete to call DeleteDC (when the handle was acquired by CreateDC)
    ///  - CDCRef::Release to call ReleaseDC (when the handle was acquired by GetDC)

    CDCRef(HDC dc, bool deleteOnRelease) 
    { 
        m_ptr = deleteOnRelease ? tBoostSP(dc, Delete()) :
                                  tBoostSP(dc, Null());
    }

    CDCRef(HWND wnd, HDC dc, bool releaseOnRelease)
    {
        m_ptr = releaseOnRelease ? tBoostSP(dc, Release(wnd)) :
                                   tBoostSP(dc, Null());
    }

    /// implements GetDC, returning a valid CDCRef
    /// for more information, see MSDN: GetDC
    static CDCRef GetDC(HWND wnd) 
    { 
        return CDCRef(wnd, ::GetDC(wnd), true); 
    }

    /// implements GetDC, returning a valid CDCRef
    /// for more information, see MSDN: GetDCEx
    static CDCRef GetDCEx(HWND wnd, HRGN rgnClip, DWORD flags) 
    { 
        return CDCRef(wnd, ::GetDCEx(wnd, rgnClip, flags), true); 
    }

    static CDCRef GetWindowDC(HWND wnd)
    {
        return CDCRef(wnd, ::GetWindowDC(wnd), true );
    }


    /// implements CreateDC / CreateIC, returning a valid CDCRef
    /// for more information, see MSDN: CreateDC
    /// specify idonDCOnly=true to call CreateIC instead of CreateDC.
    /// 
    static CDCRef CreateDC(LPCTSTR lpszDriver, 
                           LPCTSTR lpszDevice, 
                           LPCTSTR  lpszOutput, 
                           CONST DEVMODE * lpInitData, bool infoDCOnly = false)
    {
        HDC dc = infoDCOnly ? ::CreateIC(lpszDriver, lpszDevice, lpszOutput, lpInitData) :
                              ::CreateDC(lpszDriver, lpszDevice, lpszOutput, lpInitData);
        return CDCRef(dc, true);
    }

    /// implements CreateCompatibleDC, returning a valid CDCRef
    /// for more information, see MSDN: CreateCompatibleDC
    /// 
    static CDCRef CreateCompatibleDC(HDC dc)
    {
        return CDCRef( ::CreateCompatibleDC(dc), true);
    }
};




typedef CHandleRefT<HIMAGELIST, nsHandleRefDetail::CDeleterImageList> CImageListRef;
typedef CHandleRefT<HBITMAP, nsHandleRefDetail::CDeleterGDI> CBitmapRef;
typedef CHandleRefT<HBITMAP, nsHandleRefDetail::CDeleterGDI> CBitmapRef;
typedef CHandleRefT<HBRUSH, nsHandleRefDetail::CDeleterGDI> CBrushRef;
typedef CHandleRefT<HPEN, nsHandleRefDetail::CDeleterGDI> CPenRef;
typedef CHandleRefT<HANDLE, nsHandleRefDetail::CDeleterHANDLE> CHandleRef;
typedef CHandleRefT<HMENU, nsHandleRefDetail::CDeleterHMENU> CMenuRef;
typedef CHandleRefT<HKEY, nsHandleRefDetail::CDeleterHKEY> CHKeyRef;
// CDCRef - special class


/**
 \page pgUse Usage Recommendations
 the following block shows god/bad usage samples:
 \code

// OK: assign new resource immediately to a HandleRef
CMenuRef menu(LoadMenu(myInstance, ID_MENU), true);

// OK: returning a HandleRef from a function
// the function itself determines if the handle must be deleted
CMenuRef GetCustomizedMenu()
{
    return CMenuRef(LoadMenu(myInstance), ID_CUSTOM_MENU, true);
}

// OK: store HandleRefs instead of raw resources
class CMyUIStuff
{
    CMenuRef        m_menu;
    CImageListRef   m_imgList;

  public:
    // important: use a CMenuRef here, to preserve the deletion policy
    void SetMenu(CMenuRef menu); 
    void SetImageList(CImageListRef il);
};

// OK: passing raw handle to a function that does not store the handle
//     (you can also use a HandleRef, of course)
void CountEnabledCommands(HMENU menu); 

// \b WRONG: delete a Handle behind HandleRef's back
HMENU hmenu = LoadMenu(myInstance, myID);
CHandleRef menu(hmenu, true);
DeleteMenu(hmenu);  // ERROR: will be deleted again by CHandleRef

// \b WRONG: assign a raw handle to two automatic refs:
HMENU hmenu = LoadMenu(myInstance, myID);
CHandleRef menuA(hmenu, true);

CHandleRef menuB(hmenu, true); // ERROR: will be deleted twice
CHandleRef menuB = menuA;      // correct: share the handle

\endcode
*/



#endif // FILE_PH_HANDLEREF_H_200427719_INCLUDED_
