
// ENCARA2_2libDemo.h: archivo de encabezado principal para la aplicaci�n ENCARA2_2libDemo
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // S�mbolos principales


// CENCARA2_2libDemoApp:
// Consulte la secci�n ENCARA2_2libDemo.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CENCARA2_2libDemoApp : public CWinAppEx
{
public:
	CENCARA2_2libDemoApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementaci�n
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CENCARA2_2libDemoApp theApp;
