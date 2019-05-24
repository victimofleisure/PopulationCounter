// Copyleft 2019 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00		19apr19	initial version

*/

#include "stdafx.h"
#include "MaxFontStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMaxFontStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CMaxFontStatic::CMaxFontStatic()
{
	m_clrBkgnd = RGB(0, 0, 0);
	m_clrText = RGB(255, 255, 255);
}

void CMaxFontStatic::SetText(const CString& sText)
{
	bool	bLengthChange = sText.GetLength() != m_sText.GetLength();
	m_sText = sText;
	if (bLengthChange && m_hWnd) {
		CRect	rc;
		GetClientRect(rc);
		OnSize(0, rc.Width(), rc.Height());
	}
}

void CMaxFontStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect	rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, m_clrBkgnd);
	dc.SetTextColor(m_clrText);
	HGDIOBJ	hPrevFont = dc.SelectObject(m_font);
	dc.DrawText(m_sText, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	dc.SelectObject(hPrevFont);	
}

BOOL CMaxFontStatic::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// CStatic::OnEraseBkgnd(pDC);
}

void CMaxFontStatic::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	CClientDC	dc(this);
	CFont	font;
	LOGFONT	lf;
	ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 10;
	lf.lfWeight = FW_BLACK;
	lf.lfPitchAndFamily = FF_SWISS;
	lf.lfQuality = ANTIALIASED_QUALITY;
	HGDIOBJ	hDefaultFont = 0;
	while (1) {
		font.DeleteObject();
		if (!font.CreateFontIndirect(&lf))
			return;
		HGDIOBJ	hPrevFont = dc.SelectObject(font);
		if (!hDefaultFont)
			hDefaultFont = hPrevFont;
		CSize	szText(dc.GetTextExtent(m_sText));
		if (szText.cx >= cx || szText.cy >= cy) {
			lf.lfHeight--;
			break;
		}
		lf.lfHeight++;
	}
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&lf);
	dc.SelectObject(hDefaultFont);
}
