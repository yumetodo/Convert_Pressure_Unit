#ifndef _MYTSTRING_H
#define _MYSTRING_H
#if _MSC_VER > 1000
#pragma once
#endif
#include <cstdio>
#include <string>
#include "mytchar.h"
#include <climits>
#include <cfloat>
#ifdef _MSC_VER
#define _T(x) __T(x)
#endif //_MSC_VER
#ifdef _INC_TCHAR
#if defined(UNICODE) || defined(_UNICODE)
#define _tparseInt wparseInt
#define _tparseDouble wparseDouble
#else
#define _tparseInt parseInt
#define _tparseDouble parseDouble
#endif //UNICODE || _UNICODE
#endif // _INC_TCHAR

/// <summary>wchar_t* から char* への変換を行う</summary>
/// <param name="pSrc">変換するwchar_t型の文字列</param>
/// <param name="pDest">変換結果のchar型文字列</param>
/// <param name="sDestSize">pDestのサイズ</param>
/// <returns>0:正常,その他:異常</returns>
int wchartToChar(const wchar_t* pSrc, char* pDest, const size_t sDestSize);

/// <summary>char* から wchar_t* への変換を行う</summary>
/// <param name="pSrc">変換するchar型の文字列</param>
/// <param name="pDest">変換結果のwchar_t型文字列</param>
/// <param name="sDestSize">pDestのサイズ</param>
/// <returns>0:正常,その他:異常</returns>
int charToWchart(const char* pSrc, wchar_t* pDest, const size_t sDestSize);

/// <summary>ワイド文字列からマルチバイト文字列への変換を行う。ロケール依存</summary>
/// <param name="src">変換するstd::string</param>
/// <param name="dest">変換結果のstd::wstring</param>
void WstrToStr(const std::wstring &src, std::string &dest);

/// <summary>マルチバイト文字列からワイド文字列への変換を行う。ロケール依存</summary>
/// <param name="src">変換するstd::wstring</param>
/// <param name="dest">変換結果のstd::string</param>
void StrToWstr(const std::string &src, std::wstring &dest);
inline void WstrToTstr(const std::wstring& src, std::tstring& dest){
#ifdef _UNICODE
	dest = src;
#else
	WstrToStr(src, dest);
#endif
}
inline void StrToTstr(const std::string& src, std::tstring& dest){
#ifdef _UNICODE
	StrToWstr(src, dest);
#else
	dest = src;
#endif
}
#endif //_MYTSTRING_H