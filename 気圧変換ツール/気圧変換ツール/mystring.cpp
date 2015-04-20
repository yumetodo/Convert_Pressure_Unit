#if defined _MSC_VER && _MSC_VER >= 1400
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1
#endif
#include "mystring.h"
#include <cstdlib>
#include <ctype.h>
#include <cerrno>//in gcc
using namespace std;
/*
参考サイト
http://web.archive.org/web/20040610164848/http://kitaj.at.infoseek.co.jp/getline.html
*/
/// <summary>wchar_t* から char* への変換を行う</summary>
/// <param name="pSrc">変換するwchar_t型の文字列</param>
/// <param name="pDest">変換結果のchar型文字列</param>
/// <param name="sDestSize">pDestのサイズ</param>
/// <returns>0:正常,その他:異常</returns>
extern inline int wchartToChar(const wchar_t* pSrc, char* pDest, const size_t sDestSize)
{
#if defined _MSC_VER && _MSC_VER >= 1400
	size_t iReturnValue;
	errno_t ret = wcstombs_s(&iReturnValue, pDest, sDestSize, pSrc, _TRUNCATE);
	if (ret != 0)	return ret;
	return 0;
#else
	return wcstombs(pDest, sDestSize, pSrc);
#endif
}
/// <summary>char* から wchar_t* への変換を行う</summary>
/// <param name="pSrc">変換するchar型の文字列</param>
/// <param name="pDest">変換結果のwchar_t型文字列</param>
/// <param name="sDestSize">pDestのサイズ</param>
/// <returns>0:正常,その他:異常</returns>
extern inline int charToWchart(const char* pSrc, wchar_t* pDest, const size_t sDestSize)
{
#if defined _MSC_VER && _MSC_VER >= 1400
	size_t iReturnValue;
	errno_t ret = mbstowcs_s(&iReturnValue, pDest, sDestSize, pSrc, _TRUNCATE);
	if (ret != 0)	return ret;
	return 0;
#else
	return mbstowcs(pDest, sDestSize, pSrc);
#endif
}
/// <summary>ワイド文字列からマルチバイト文字列への変換を行う。ロケール依存</summary>
/// <param name="src">変換するstd::string</param>
/// <param name="dest">変換結果のstd::wstring</param>
void WstrToStr(const std::wstring &src, std::string &dest)
{
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	wchartToChar(src.c_str(), mbs, src.length() * MB_CUR_MAX + 1);
	dest = mbs;
	delete[] mbs;
}
/// <summary>マルチバイト文字列からワイド文字列への変換を行う。ロケール依存</summary>
/// <param name="src">変換するstd::wstring</param>
/// <param name="dest">変換結果のstd::string</param>
void StrToWstr(const std::string &src, std::wstring &dest)
{
	wchar_t *wcs = new wchar_t[src.length() + 1];
	charToWchart(src.c_str(), wcs, src.length() + 1);
	dest = wcs;
	delete[] wcs;
}