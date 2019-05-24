
// stdafx.cpp : source file that includes just the standard includes
// PopulationCounter.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

bool FormatNumberCommas(LPCTSTR pszSrc, CString& sDst, int nPrecision)
{
	USES_CONVERSION;
	WCHAR	szDecimal[4];
	WCHAR	szThousand[4];
	if (!GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SDECIMAL, szDecimal, _countof(szDecimal)))
		return false;
	if (!GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_STHOUSAND, szThousand, _countof(szThousand)))
		return false;
	NUMBERFMTW	fmt = {nPrecision, 0, 3, szDecimal, szThousand};
	int	nLen = GetNumberFormatEx(LOCALE_NAME_USER_DEFAULT, 0, T2CW(pszSrc), &fmt, NULL, 0);
	CStringW	sBuf;
	LPWSTR	pBuf = sBuf.GetBuffer(nLen);
	if (!GetNumberFormatEx(LOCALE_NAME_USER_DEFAULT, 0, T2CW(pszSrc), &fmt, pBuf, nLen))
		return false;
	sBuf.ReleaseBuffer();
	sDst = sBuf;
	return true;
}

