
// 3TLiveDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "vld.h"


// CMy3TLiveDemoApp:
// �йش����ʵ�֣������ 3TLiveDemo.cpp
//

class CMy3TLiveDemoApp : public CWinAppEx
{
public:
	CMy3TLiveDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy3TLiveDemoApp theApp;