// LiveChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "LiveChatDlg.h"


// CLiveChatDlg 对话框

IMPLEMENT_DYNAMIC(CLiveChatDlg, CDialog)

CLiveChatDlg::CLiveChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLiveChatDlg::IDD, pParent)
{
	
}

CLiveChatDlg::~CLiveChatDlg()
{
}

void CLiveChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLiveChatDlg, CDialog)
END_MESSAGE_MAP()


// CLiveChatDlg 消息处理程序
