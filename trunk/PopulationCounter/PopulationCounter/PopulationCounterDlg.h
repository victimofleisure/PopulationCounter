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

// PopulationCounterDlg.h : header file
//

#pragma once

#include "MaxFontStatic.h"

// CPopulationCounterDlg dialog
class CPopulationCounterDlg : public CDialogEx
{
// Construction
public:
	CPopulationCounterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POPULATIONCOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	enum {
		TIMER_ID = 1850,			// refresh timer identifier
		TIMER_PERIOD = 50,			// refresh timer period in milliseconds
	};
	enum {
		IDM_ABOUTBOX = 0x0010,
		IDM_FULLSCREEN = 0x0020,
	};
	HICON m_hIcon;
	CMaxFontStatic	m_wndText;		// font-maximizing text control
	LONGLONG	m_nCount;			// currently displayed count
	LONGLONG	m_nPrevCount;		// previously displayed count
	bool	m_bIsFullScreen;		// true if full screen
	CRect	rPreFullScreen;			// window rectangle prior to going full screen
	UINT	m_nTextBorder;			// size of border around text control, in pixels

	void	UpdateText();
	void	FullScreen(bool bEnable);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
