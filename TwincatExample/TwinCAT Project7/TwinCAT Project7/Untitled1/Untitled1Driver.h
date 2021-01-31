///////////////////////////////////////////////////////////////////////////////
// Untitled1Driver.h

#ifndef __UNTITLED1DRIVER_H__
#define __UNTITLED1DRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define UNTITLED1DRV_NAME        "UNTITLED1"
#define UNTITLED1DRV_Major       1
#define UNTITLED1DRV_Minor       0

#define DEVICE_CLASS CUntitled1Driver

#include "ObjDriver.h"

class CUntitled1Driver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl UNTITLED1DRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(UNTITLED1DRV)
	VxD_Service( UNTITLED1DRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __UNTITLED1DRIVER_H__