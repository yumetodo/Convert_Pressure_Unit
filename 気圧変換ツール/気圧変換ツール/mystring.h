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

/// <summary>wchar_t* ���� char* �ւ̕ϊ����s��</summary>
/// <param name="pSrc">�ϊ�����wchar_t�^�̕�����</param>
/// <param name="pDest">�ϊ����ʂ�char�^������</param>
/// <param name="sDestSize">pDest�̃T�C�Y</param>
/// <returns>0:����,���̑�:�ُ�</returns>
int wchartToChar(const wchar_t* pSrc, char* pDest, const size_t sDestSize);

/// <summary>char* ���� wchar_t* �ւ̕ϊ����s��</summary>
/// <param name="pSrc">�ϊ�����char�^�̕�����</param>
/// <param name="pDest">�ϊ����ʂ�wchar_t�^������</param>
/// <param name="sDestSize">pDest�̃T�C�Y</param>
/// <returns>0:����,���̑�:�ُ�</returns>
int charToWchart(const char* pSrc, wchar_t* pDest, const size_t sDestSize);

/// <summary>���C�h�����񂩂�}���`�o�C�g������ւ̕ϊ����s���B���P�[���ˑ�</summary>
/// <param name="src">�ϊ�����std::string</param>
/// <param name="dest">�ϊ����ʂ�std::wstring</param>
void WstrToStr(const std::wstring &src, std::string &dest);

/// <summary>�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ����s���B���P�[���ˑ�</summary>
/// <param name="src">�ϊ�����std::wstring</param>
/// <param name="dest">�ϊ����ʂ�std::string</param>
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