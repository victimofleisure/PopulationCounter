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

*/

// PopulationCounter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PopulationCounter.h"
#include "PopulationCounterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPopulationCounterApp

BEGIN_MESSAGE_MAP(CPopulationCounterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPopulationCounterApp construction

CPopulationCounterApp::CPopulationCounterApp()
{
	// add construction code here,
	// Place all significant initialization in InitInstance

	// Population data from http://worldometers.info
	// This data can be overriden via the command line; see below.
	m_nInitCount = 7714576923ll;
	m_tInitCount = CTime(2019, 7, 1, 0, 0, 0);
	m_fAnnualChange = 0.0107;
}

CPopulationCounterApp::CMyCommandLineInfo::CMyCommandLineInfo()
{
	m_iParam = -1;
}

void CPopulationCounterApp::CMyCommandLineInfo::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
/*
	The following command line parameters are supported:
	/n N	N is the initial population count (no commas!)
	/d D	D is the census date in MM/DD/YYYY format only
	/g G	G is the annual growth rate (not a percentage!)
	
	Sample command line:
	PopulationCounter /n 7714576923 /d 7/1/2019 /g 0.0107

	The date format is fixed and doesn't vary by region.
	The above growth rate is equivalent to 1.07 percent.
	The parameter names aren't case sensitive, and they
	can be prefixed with a hyphen instead of a slash.

*/
	enum {	// define parameters
		P_INIT_COUNT,
		P_CENSUS_DATE,
		P_GROWTH_RATE,
		PARAMS
	};
	static const LPCTSTR arrParamName[PARAMS] = {
		_T("n"),
		_T("d"),
		_T("g")
	};
	if (bFlag) {	// if flag name
		m_iParam = -1;	// init to unknown parameter
		for (int iParam = 0; iParam < PARAMS; iParam++) {	// for each parameter
			if (!_tcsicmp(pszParam, arrParamName[iParam])) {	// if name matches
				m_iParam = iParam;	// store parameter index
				break;
			}
		}
	} else {	// flag value
		int	mm, dd, yyyy;
		switch (m_iParam) {
		case P_INIT_COUNT:
			if (_stscanf_s(pszParam, _T("%lld"), &theApp.m_nInitCount) != 1)
				AfxMessageBox(_T("Invalid initial population."));
			break;
		case P_CENSUS_DATE:
			if (_stscanf_s(pszParam, _T("%d/%d/%d"), &mm, &dd, &yyyy) != 3)
				AfxMessageBox(_T("Invalid census date."));
			else
				theApp.m_tInitCount = CTime(yyyy, mm, dd, 0, 0, 0);
			break;
		case P_GROWTH_RATE:
			if (_stscanf_s(pszParam, _T("%lf"), &theApp.m_fAnnualChange) != 1)
				AfxMessageBox(_T("Invalid growth rate."));
			break;
		}
	}
	if (m_iParam < 0)	// if unknown parameter
		CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

// The one and only CPopulationCounterApp object

CPopulationCounterApp theApp;


// CPopulationCounterApp initialization

BOOL CPopulationCounterApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Anal Software"));

	CMyCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CPopulationCounterDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

