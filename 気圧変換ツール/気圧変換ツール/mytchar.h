#ifndef _MY_INC_TCHAR_H
#define _MY_INC_TCHAR_H
#if _MSC_VER > 1000
#pragma once
#endif
#include <tchar.h>
#include <string>
#if defined UNICODE && !defined _UNICODE
#define _UNICODE 1
#endif
namespace std{
	typedef std::basic_string<TCHAR> tstring;
	typedef std::basic_ios<TCHAR> tios;
	typedef std::basic_streambuf<TCHAR> tstreambuf;
	typedef std::basic_istream<TCHAR> tistream;
	typedef std::basic_ostream<TCHAR> tostream;
	typedef std::basic_iostream<TCHAR> tiostream;
	typedef std::basic_stringbuf<TCHAR> tstringbuf;
	typedef std::basic_istringstream<TCHAR> tistringstream;
	typedef std::basic_ostringstream<TCHAR> tostringstream;
	typedef std::basic_stringstream<TCHAR> tstringstream;
	typedef std::basic_filebuf<TCHAR> tfilebuf;
	typedef std::basic_ifstream<TCHAR> tifstream;
	typedef std::basic_ofstream<TCHAR> tofstream;
	typedef std::basic_fstream<TCHAR> tfstream;
}
#ifdef _UNICODE
namespace std{
	inline tstring to_tstring(int value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(unsigned int value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(long value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(unsigned long value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(_Longlong value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(_ULonglong value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(long double value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(double value){
		return std::to_wstring(value);
	}
	inline tstring to_tstring(float value){
		return std::to_wstring(value);
	}
}
#else
namespace std{
	inline tstring to_tstring(int value){
		return std::to_string(value);
	}
	inline tstring to_tstring(unsigned int value){
		return std::to_string(value);
	}
	inline tstring to_tstring(long value){
		return std::to_string(value);
	}
	inline tstring to_tstring(unsigned long value){
		return std::to_string(value);
	}
	inline tstring to_tstring(_Longlong value){
		return std::to_string(value);
	}
	inline tstring to_tstring(_ULonglong value){
		return std::to_string(value);
	}
	inline tstring to_tstring(long double value){
		return std::to_string(value);
	}
	inline tstring to_tstring(double value){
		return std::to_string(value);
	}
	inline tstring to_tstring(float value){
		return std::to_string(value);
	}
}
#endif
#ifdef _MYSTRING_H
#if defined(UNICODE) || defined(_UNICODE)
#define _tparseInt wparseInt
#define _tparseDouble wparseDouble
#else
#define _tparseInt parseInt
#define _tparseDouble parseDouble
#endif //UNICODE || _UNICODE
#endif //_MYSTRING_H

#if defined(UNICODE) || defined(_UNICODE)
# define tcout std::wcout
# define tcin std::wcin
# define tcerr std::wcerr
# define tclog std::wclog
#else
# define tcout std::cout
# define tcin std::cin
# define tcerr std::cerr
# define tclog std::clog
#endif
#endif //_MY_INC_TCHAR_H