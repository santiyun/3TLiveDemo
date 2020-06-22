#pragma once
#include <Windows.h>
#include <string>
#include "Common.h"
//
//std::wstring s2ws(const std::string& s)
//{
//	wchar_t* pws = NULL;
//	std::wstring wstrRet;
//
//	int bufSize = MultiByteToWideChar(CP_ACP,
//		MB_PRECOMPOSED,
//		s.c_str(),
//		(int)s.length(),
//		pws,
//		0);
//
//	pws = new wchar_t[bufSize + 1];
//	memset(pws, 0, (bufSize + 1) * sizeof(wchar_t));
//
//	MultiByteToWideChar(CP_ACP,
//		MB_PRECOMPOSED,
//		s.c_str(),
//		(int)s.length(),
//		pws,
//		bufSize);
//
//	wstrRet = pws;
//	delete[] pws;
//
//	return wstrRet;
//}
//
//std::string ws2utf8(const std::wstring &ws)
//{
//	char* ps = NULL;
//	std::string strRet;
//
//	int bufSize = WideCharToMultiByte(CP_UTF8,
//		0,
//		ws.c_str(),
//		(int)ws.length(),
//		ps,
//		0,
//		NULL,
//		NULL);
//
//	ps = new char[bufSize + 1];
//	memset(ps, 0, bufSize + 1);
//
//	WideCharToMultiByte(CP_UTF8,
//		0,
//		ws.c_str(),
//		(int)ws.length(),
//		ps,
//		bufSize,
//		NULL,
//		NULL);
//
//	strRet = ps;
//	delete[] ps;
//
//	return strRet;
//}
//std::string s2utf8(const std::string &s)
//{
//	std::wstring ws = s2ws(s);
//	return ws2utf8(ws);
//}
// All I/O is in UTF-8
bool InputBox_GetString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::string &defaultvalue, std::string &outvalue, bool selected);
bool InputBox_GetString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::string &defaultvalue, std::string &outvalue);
bool InputBox_GetWString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::wstring &defaultvalue, std::wstring &outvalue);
//bool //InputBox_GetHex(HINSTANCE hInst, HWND hParent, const wchar_t *title, u32 defaultvalue, u32 &outvalue);