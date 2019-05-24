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

// PopulationCounterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PopulationCounter.h"
#include "PopulationCounterDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CPopulationCounterDlg dialog

CPopulationCounterDlg::CPopulationCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPopulationCounterDlg::IDD, pParent)
{
	m_hIcon = theApp.LoadIcon(IDR_MAINFRAME);
	m_nCount = theApp.m_nInitCount;
	m_nPrevCount = 0;
	m_bIsFullScreen = false;
	rPreFullScreen.SetRectEmpty();
	m_nTextBorder = 16;
}

void CPopulationCounterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPopulationCounterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPopulationCounterDlg message handlers

BOOL CPopulationCounterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			CString sFullScreen;
			sFullScreen.LoadString(IDS_FULLSCREEN);
			pSysMenu->AppendMenu(MF_STRING, IDM_FULLSCREEN, sFullScreen);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Add extra initialization here
	UpdateText();
	CRect	rText;
	GetClientRect(rText);
	rText.DeflateRect(m_nTextBorder, m_nTextBorder);
	m_wndText.Create(_T(""), WS_CHILD | WS_VISIBLE, rText, this);
	SetTimer(TIMER_ID, TIMER_PERIOD, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPopulationCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == IDM_FULLSCREEN)
	{
		FullScreen(!m_bIsFullScreen);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPopulationCounterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		CRect	rc;
		GetClientRect(rc);
		dc.FillSolidRect(rc, m_wndText.m_clrBkgnd);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPopulationCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPopulationCounterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_wndText.m_hWnd) {
		CRect	rText(0, 0, cx, cy);
		rText.DeflateRect(m_nTextBorder, m_nTextBorder);
		m_wndText.MoveWindow(rText);
		Invalidate();
	}
}

BOOL CPopulationCounterDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	//CDialogEx::OnEraseBkgnd(pDC);
}

BOOL CPopulationCounterDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_F11:
			FullScreen(!m_bIsFullScreen);
			break;
		case VK_ESCAPE:
			FullScreen(false);
			return true;
		case VK_RETURN:
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPopulationCounterDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID) {
		SYSTEMTIME	stNow;
		GetSystemTime(&stNow);
		CTime	tNow(stNow);
		CTimeSpan	tDelta(tNow - theApp.m_tInitCount);
		double	fDeltaMillis = double(tDelta.GetTotalSeconds()) * 1000 + stNow.wMilliseconds;
		double	fAnnualMillis = 365.2422 * 24 * 3600 * 1000;
		double	fExp = fDeltaMillis / fAnnualMillis;
		m_nCount = round64(theApp.m_nInitCount * pow(1 + theApp.m_fAnnualChange, fExp));
		if (m_nCount != m_nPrevCount) {	// if count changed
			m_nPrevCount = m_nCount;
			UpdateText();
			m_wndText.Invalidate();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CPopulationCounterDlg::UpdateText()
{
	CString	sText;
	sText.Format(_T("%lld"), m_nCount);
	FormatNumberCommas(sText, sText, 0);
	m_wndText.SetText(sText);
}

void CPopulationCounterDlg::FullScreen(bool bEnable)
{
	if (bEnable == m_bIsFullScreen)	// if state unchanged
		return;	// nothing to do
	if (bEnable) {
		GetWindowRect(rPreFullScreen);
		ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);
		CRect rDesktop(CPoint(GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN)),
			CSize(GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN)));
		MoveWindow(rDesktop);
	} else {
		ModifyStyle(0, WS_CAPTION | WS_THICKFRAME);
		MoveWindow(rPreFullScreen);
	}
	m_bIsFullScreen = bEnable;
}
