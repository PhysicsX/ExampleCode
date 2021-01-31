///////////////////////////////////////////////////////////////////////////////
// Untitled1Ctrl.h

#ifndef __UNTITLED1CTRL_H__
#define __UNTITLED1CTRL_H__

#include <atlbase.h>
#include <atlcom.h>


#include "resource.h"       // main symbols
#include "Untitled1W32.h"
#include "TcBase.h"
#include "Untitled1ClassFactory.h"
#include "TcOCFCtrlImpl.h"

class CUntitled1Ctrl 
	: public CComObjectRootEx<CComMultiThreadModel>
	, public CComCoClass<CUntitled1Ctrl, &CLSID_Untitled1Ctrl>
	, public IUntitled1Ctrl
	, public ITcOCFCtrlImpl<CUntitled1Ctrl, CUntitled1ClassFactory>
{
public:
	CUntitled1Ctrl();
	virtual ~CUntitled1Ctrl();

DECLARE_REGISTRY_RESOURCEID(IDR_UNTITLED1CTRL)
DECLARE_NOT_AGGREGATABLE(CUntitled1Ctrl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUntitled1Ctrl)
	COM_INTERFACE_ENTRY(IUntitled1Ctrl)
	COM_INTERFACE_ENTRY(ITcCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl2)
END_COM_MAP()

};

#endif // #ifndef __UNTITLED1CTRL_H__
