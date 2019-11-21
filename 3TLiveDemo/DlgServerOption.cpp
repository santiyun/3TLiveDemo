// DlgServerOption.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "DlgServerOption.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"

extern C3TLocalUserInfo g_LocalUser;

// CDlgServerOption 对话框

IMPLEMENT_DYNAMIC(CDlgServerOption, CDialogEx)

CDlgServerOption::CDlgServerOption(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SERVER_SETTING, pParent)
	, m_csAddr(_T(""))
	, m_iPort(5000)
	, m_csAppID(_T("a967ac491e3acf92eed5e1b5ba641ab7"))
{

}

CDlgServerOption::~CDlgServerOption()
{
}

void CDlgServerOption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_SERVER_ADDR, m_csAddr);
	DDX_Text(pDX, IDC_EDT_SERVER_PORT, m_iPort);
	DDX_Control(pDX, IDC_COMBO_APPID, m_comboAppID);
	DDX_CBString(pDX, IDC_COMBO_APPID, m_csAppID);
}


BEGIN_MESSAGE_MAP(CDlgServerOption, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_APPID, &CDlgServerOption::OnCbnSelchangeComboAppid)
	ON_EN_KILLFOCUS(IDC_EDT_SERVER_PORT, &CDlgServerOption::OnEnKillfocusEdtServerPort)
	ON_EN_KILLFOCUS(IDC_EDT_SERVER_ADDR, &CDlgServerOption::OnEnKillfocusEdtServerAddr)
	ON_NOTIFY(NM_THEMECHANGED, IDC_COMBO_APPID, &CDlgServerOption::OnThemechangedComboAppid)
END_MESSAGE_MAP()


// CDlgServerOption 消息处理程序


BOOL CDlgServerOption::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboAppID.ResetContent();
	m_comboAppID.InsertString(0, "a967ac491e3acf92eed5e1b5ba641ab7");

	this->m_csAppID = g_LocalUser.m_sAppID.c_str();
	m_iPort = g_LocalUser.m_iPort;
	m_csAddr = g_LocalUser.m_sAddress.c_str();
	UpdateData(false);
	//m_comboAppID.SetCurSel(1);
	//UpdateData(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgServerOption::OnCbnSelchangeComboAppid()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString aaid;
	int i = m_comboAppID.GetCurSel();
	m_comboAppID.GetWindowTextA(aaid);
	this->m_csAppID;
	//MessageBox(aaid,)
	//m_comboAppID.
	//m_comboAppID.GetWindowTextA(aaid);
}


void CDlgServerOption::OnEnKillfocusEdtServerPort()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}


void CDlgServerOption::OnEnKillfocusEdtServerAddr()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}


void CDlgServerOption::OnThemechangedComboAppid(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	*pResult = 0;
}
