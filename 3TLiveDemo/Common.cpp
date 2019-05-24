#include "stdafx.h"
#include "Common.h"
#include <sstream>
#include <regex>

using namespace std;

bool isdigit(std::string strValue)
{
	//bool bValid = false;
	//定义一个正则表达式 ,数字
	regex repPattern("^[0-9]*$", regex_constants::extended);
	// 声明匹配结果变量
	match_results<string::const_iterator> rerResult;
	// 进行匹配
	bool bValid = regex_match(strValue, rerResult, repPattern);
	return bValid;
}

namespace ws_techapi
{
	int gettimeofday(struct timeval *tp, void *tzp)
	{
		time_t clock;
		struct tm tm;
		SYSTEMTIME wtm;
		GetLocalTime(&wtm);
		tm.tm_year = wtm.wYear - 1900;
		tm.tm_mon = wtm.wMonth - 1;
		tm.tm_mday = wtm.wDay;
		tm.tm_hour = wtm.wHour;
		tm.tm_min = wtm.wMinute;
		tm.tm_sec = wtm.wSecond;
		tm.tm_isdst = -1;
		clock = mktime(&tm);
		tp->tv_sec = clock;
		tp->tv_usec = wtm.wMilliseconds * 1000;

		return 0;
	}
	// internal functions
	std::string ws2s(const std::wstring& ws)
	{
		char* ps = NULL;
		std::string strRet;

		int bufSize = WideCharToMultiByte(CP_ACP,
			0,
			ws.c_str(),
			(int)ws.length(),
			ps,
			0,
			NULL,
			NULL);

		ps = new char[bufSize + 1];
		memset(ps, 0, bufSize + 1);

		WideCharToMultiByte(CP_ACP,
			0,
			ws.c_str(),
			(int)ws.length(),
			ps,
			bufSize,
			NULL,
			NULL);

		strRet = ps;
		delete[] ps;

		return strRet;
	}
	std::wstring s2wss(const std::string& s, wchar_t* pws)
	{
		//wchar_t* 
		pws = NULL;
		std::wstring wstrRet;

		int bufSize = MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			s.c_str(),
			(int)s.length(),
			pws,
			0);

		pws = new wchar_t[bufSize + 1];
		memset(pws, 0, (bufSize + 1) * sizeof(wchar_t));

		MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			s.c_str(),
			(int)s.length(),
			pws,
			bufSize);
		return L"";
	}
	std::wstring s2ws(const std::string& s)
	{
		wchar_t* pws = NULL;
		std::wstring wstrRet;

		int bufSize = MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			s.c_str(),
			(int)s.length(),
			pws,
			0);

		pws = new wchar_t[bufSize + 1];
		memset(pws, 0, (bufSize + 1) * sizeof(wchar_t));

		MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			s.c_str(),
			(int)s.length(),
			pws,
			bufSize);

		wstrRet = pws;
		delete[] pws;

		return wstrRet;
	}
	std::string ws2utf8(const std::wstring &ws)
	{
		char* ps = NULL;
		std::string strRet;

		int bufSize = WideCharToMultiByte(CP_UTF8,
			0,
			ws.c_str(),
			(int)ws.length(),
			ps,
			0,
			NULL,
			NULL);

		ps = new char[bufSize + 1];
		memset(ps, 0, bufSize + 1);

		WideCharToMultiByte(CP_UTF8,
			0,
			ws.c_str(),
			(int)ws.length(),
			ps,
			bufSize,
			NULL,
			NULL);

		strRet = ps;
		delete[] ps;

		return strRet;
	}

	std::wstring utf82ws(const std::string &utf8)
	{
		wchar_t* pws = NULL;
		std::wstring wstrRet;

		int bufSize = MultiByteToWideChar(CP_UTF8,
			0,
			utf8.c_str(),
			(int)utf8.length(),
			pws,
			0);

		pws = new wchar_t[bufSize + 1];
		memset(pws, 0, (bufSize + 1) * sizeof(wchar_t));

		MultiByteToWideChar(CP_UTF8,
			0,
			utf8.c_str(),
			(int)utf8.length(),
			pws,
			bufSize);

		wstrRet = pws;
		delete[] pws;

		return wstrRet;
	}
	std::string s2utf8(const std::string &s)
	{
		std::wstring ws = s2ws(s);
		return ws2utf8(ws);
	}

	std::string utf82s(const std::string &utf8)
	{
		std::wstring ws = utf82ws(utf8);
		return ws2s(ws);
	}

	std::string llToString(long long llvalue)
	{
		std::stringstream str;
		str << llvalue;
		return str.str();
	}

	std::string doubleToString(double d)
	{
		char tmp[256] = { 0 };
		_snprintf_s(tmp, sizeof(tmp), "%.6lf", d);
		return std::string(tmp);
	}
}
