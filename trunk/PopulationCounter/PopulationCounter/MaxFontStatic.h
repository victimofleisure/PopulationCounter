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

#pragma once

class CMaxFontStatic : public CStatic {
public:
	CMaxFontStatic();
	void	SetText(const CString& sText);
	COLORREF	m_clrBkgnd;		// background color
	COLORREF	m_clrText;		// font color

protected:
	CFont	m_font;				// current font
	CString	m_sText;			// text to display

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
