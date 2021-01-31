///////////////////////////////////////////////////////////////////////////////
// Untitled1Driver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "Untitled1Driver.h"
#include "Untitled1ClassFactory.h"

DECLARE_GENERIC_DEVICE(UNTITLED1DRV)

IOSTATUS CUntitled1Driver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CUntitled1ClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CUntitled1Driver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CUntitled1Driver::UNTITLED1DRV_GetVersion( )
{
	return( (UNTITLED1DRV_Major << 8) | UNTITLED1DRV_Minor );
}

