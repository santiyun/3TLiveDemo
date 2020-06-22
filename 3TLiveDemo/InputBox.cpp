#include "stdafx.h"
//#include "Common/CommonTypes.h"
//#include "Common/CommonWindows.h"
//#include "Windows/InputBox.h"
//#include "Windows/resource.h"
//#include "utf8.h"
#include "InputBox.h"
#include "resource.h"
//use namespace std;
#include "resource.h"
#include <string>
#include <basetsd.h>
#include "InputBox.h"
//#include <static.h>
static std::wstring textBoxContents;
static std::wstring out;
static std::wstring windowTitle;
static bool defaultSelected;

static INT_PTR CALLBACK InputBoxFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		SetWindowTextW(GetDlgItem(hDlg, IDC_INPUTBOX), textBoxContents.c_str());
		SetWindowTextW(hDlg, windowTitle.c_str());
		if (defaultSelected == false) PostMessage(GetDlgItem(hDlg, IDC_INPUTBOX), EM_SETSEL, -1, -1);
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			wchar_t temp[256];
			GetWindowTextW(GetDlgItem(hDlg, IDC_INPUTBOX), temp, 255);
			out = temp;
		}
		EndDialog(hDlg, IDOK);
		return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	default:
		return FALSE;
	}
}

template <bool hex>
void InputBoxFunc()
{

}

bool InputBox_GetString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::string &defaultValue, std::string &outvalue, bool selected)
{
	defaultSelected = selected;
	if (defaultValue.size() < 255)
		textBoxContents = ws_techapi::utf82ws(defaultValue);
	else
		textBoxContents = L"";

	if (title != NULL)
		windowTitle = title;
	else
		windowTitle = L"";
	
	if (IDOK == DialogBoxW(hInst, (LPCWSTR)IDD_INPUTBOX, hParent, InputBoxFunc)) {
		outvalue = ws_techapi::ws2utf8(out);
		return true;
	}
	else
		return false;
}

bool InputBox_GetString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::string &defaultValue, std::string &outvalue)
{
	const wchar_t *defaultTitle = L"Input value";
	defaultSelected = true;

	textBoxContents = ws_techapi::utf82ws(defaultValue);

	if (title && wcslen(title) <= 0)
		windowTitle = defaultTitle;
	else if (title && wcslen(title) < 255)
		windowTitle = title;
	else
		windowTitle = defaultTitle;

	if (IDOK == DialogBoxW(hInst, (LPCWSTR)IDD_INPUTBOX, hParent, InputBoxFunc)) {
		outvalue = ws_techapi::ws2utf8(out);
		return true;
	}
	else
		return false;
}

bool InputBox_GetWString(HINSTANCE hInst, HWND hParent, const wchar_t *title, const std::wstring &defaultValue, std::wstring &outvalue)
{
	const wchar_t *defaultTitle = L"Input value";
	defaultSelected = true;

	textBoxContents = defaultValue;

	if (title && wcslen(title) <= 0)
		windowTitle = defaultTitle;
	else if (title && wcslen(title) < 255)
		windowTitle = title;
	else
		windowTitle = defaultTitle;

	if (IDOK == DialogBoxW(hInst, (LPCWSTR)IDD_INPUTBOX, hParent, InputBoxFunc)) {
		outvalue = out;
		return true;
	}
	else
		return false;
}
//
//bool InputBox_GetHex(HINSTANCE hInst, HWND hParent, const wchar_t *title, u32 defaultvalue, u32 &outvalue)
//{
//	wchar_t temp[256];
//	wsprintf(temp, L"%08x", defaultvalue);
//	textBoxContents = temp;
//
//	INT_PTR value = DialogBox(hInst, (LPCWSTR)IDD_INPUTBOX, hParent, InputBoxFunc);
//
//	if (value == IDOK)
//	{
//		if (swscanf(out.c_str(), L"0x%08x", &outvalue) == 1)
//			return true;
//		if (swscanf(out.c_str(), L"%08x", &outvalue) == 1)
//			return true;
//		return false;
//	}
//	else
//	{
//		outvalue = 0;
//		return false;
//	}
//}