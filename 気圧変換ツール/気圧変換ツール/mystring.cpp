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
�Q�l�T�C�g
http://web.archive.org/web/20040610164848/http://kitaj.at.infoseek.co.jp/getline.html
*/
/// <summary>wchar_t* ���� char* �ւ̕ϊ����s��</summary>
/// <param name="pSrc">�ϊ�����wchar_t�^�̕�����</param>
/// <param name="pDest">�ϊ����ʂ�char�^������</param>
/// <param name="sDestSize">pDest�̃T�C�Y</param>
/// <returns>0:����,���̑�:�ُ�</returns>
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
/// <summary>char* ���� wchar_t* �ւ̕ϊ����s��</summary>
/// <param name="pSrc">�ϊ�����char�^�̕�����</param>
/// <param name="pDest">�ϊ����ʂ�wchar_t�^������</param>
/// <param name="sDestSize">pDest�̃T�C�Y</param>
/// <returns>0:����,���̑�:�ُ�</returns>
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
/// <summary>���C�h�����񂩂�}���`�o�C�g������ւ̕ϊ����s���B���P�[���ˑ�</summary>
/// <param name="src">�ϊ�����std::string</param>
/// <param name="dest">�ϊ����ʂ�std::wstring</param>
void WstrToStr(const std::wstring &src, std::string &dest)
{
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	wchartToChar(src.c_str(), mbs, src.length() * MB_CUR_MAX + 1);
	dest = mbs;
	delete[] mbs;
}
/// <summary>�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ����s���B���P�[���ˑ�</summary>
/// <param name="src">�ϊ�����std::wstring</param>
/// <param name="dest">�ϊ����ʂ�std::string</param>
void StrToWstr(const std::string &src, std::wstring &dest)
{
	wchar_t *wcs = new wchar_t[src.length() + 1];
	charToWchart(src.c_str(), wcs, src.length() + 1);
	dest = wcs;
	delete[] wcs;
}