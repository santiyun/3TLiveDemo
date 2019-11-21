// DialogAnchorLink.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "DialogAnchorLink.h"
#include "afxdialogex.h"


// CDialogAnchorLink 对话框

IMPLEMENT_DYNAMIC(CDialogAnchorLink, CDialogEx)

CDialogAnchorLink::CDialogAnchorLink(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ANCHORLINK, pParent)
	, m_llRoomID(1231)
	, m_llUserID(1234567)
{

}

CDialogAnchorLink::~CDialogAnchorLink()
{
}

void CDialogAnchorLink::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_llRoomID);
	DDX_Text(pDX, IDC_EDIT2, m_llUserID);
}


BEGIN_MESSAGE_MAP(CDialogAnchorLink, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogAnchorLink::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogAnchorLink 消息处理程序


void CDialogAnchorLink::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);
	CDialogEx::OnOK();
}
