// Untitled1W32.cpp : Implementation of DLL Exports.

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#include "TcPch.h"
#pragma hdrstop

#include "Untitled1Ctrl.h"
#include "TcSysW32_i.c"
#include "Untitled1W32_i.c"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Untitled1Ctrl, CUntitled1Ctrl)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, (HINSTANCE)hInstance);
#ifndef UNDER_CE
		DisableThreadLibraryCalls((HINSTANCE)hInstance);
#endif
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllGetTcCtrl(ITcCtrl** ppCtrl)
{
	HRESULT hr = S_OK;
	if ( ppCtrl == NULL )
	{
		hr = E_POINTER;
	}
	else
	{
		CComObject<CUntitled1Ctrl>* pUntitled1Ctrl;
		pUntitled1Ctrl = new CComObject<CUntitled1Ctrl>();
		hr = pUntitled1Ctrl->QueryInterface(IID_ITcCtrl, reinterpret_cast<void**>(ppCtrl));
	}
	return hr;
}
