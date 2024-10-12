// Copyleft 2019 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00		19apr19	initial version
		01		22may19	add command line parameters
		02		10mar24	add launch full screen flag

*/

// PopulationCounter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPopulationCounterApp:
// See PopulationCounter.cpp for the implementation of this class
//

class CPopulationCounterApp : public CWinApp
{
public:
	CPopulationCounterApp();

	LONGLONG	m_nInitCount;		// initial population count
	CTime	m_tInitCount;			// time of initial population count
	double	m_fAnnualChange;		// annual population change as a fraction
	bool	m_bLaunchFullScreen;	// if true, go full screen on launch

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	class CMyCommandLineInfo : public CCommandLineInfo {
	public:
		CMyCommandLineInfo();
		virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
		int		m_iParam;	// parameter index, or -1 if invalid
	};

	DECLARE_MESSAGE_MAP()
};

extern CPopulationCounterApp theApp;