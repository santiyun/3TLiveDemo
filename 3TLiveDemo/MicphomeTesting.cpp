// MicphomeTesting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "MicphomeTesting.h"
#include "afxdialogex.h"


// CMicphomeTesting 对话框

IMPLEMENT_DYNAMIC(CMicphomeTesting, CDialogEx)

CMicphomeTesting::CMicphomeTesting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CMicphomeTesting::~CMicphomeTesting()
{
}

void CMicphomeTesting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMicphomeTesting, CDialogEx)
END_MESSAGE_MAP()


// CMicphomeTesting 消息处理程序
