// MySetting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "MySetting.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"

using namespace TTTRtc;

extern C3TLocalUserInfo g_LocalUser;
extern IRtcEngine* g_TTTEngine;

// CMySetting 对话框

IMPLEMENT_DYNAMIC(CMySetting, CDialogEx)

CMySetting::CMySetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SETTING, pParent)
{

}

CMySetting::~CMySetting()
{
}

void CMySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABSETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(CMySetting, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABSETTING, &CMySetting::OnTcnSelchangeTabsetting)
	ON_BN_CLICKED(IDOK, &CMySetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CMySetting 消息处理程序


BOOL CMySetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_tabSetting.InsertItem(0, "本地设置");
	m_tabSetting.InsertItem(1, "推流设置");
	m_tabSetting.InsertItem(2, "服务器设置");

	m_dlgPushSetting.Create(IDD_DLG_PUSHSETTING, &m_tabSetting);
	m_dlgLocalSetting.Create(IDD_DLG_LOCALSETTING, &m_tabSetting);
	m_dlgServer.Create(IDD_DLG_SERVER_SETTING, &m_tabSetting);

	CRect rc;
	m_tabSetting.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 3;
	rc.left += 2;
	rc.right -= 2;

	m_dlgLocalSetting.MoveWindow(&rc);
	m_dlgPushSetting.MoveWindow(&rc);
	m_dlgServer.MoveWindow(&rc);

	m_tabSetting.SetCurSel(0);

	m_dlgLocalSetting.ShowWindow(true);
	m_dlgPushSetting.ShowWindow(false);
	m_dlgServer.ShowWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMySetting::OnTcnSelchangeTabsetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int cursel = m_tabSetting.GetCurSel();
	switch (cursel)
	{
	case 0:
		m_dlgLocalSetting.ShowWindow(true);
		m_dlgPushSetting.ShowWindow(false);
		m_dlgServer.ShowWindow(false);
		break;
	case 1:
		m_dlgLocalSetting.ShowWindow(false);
		m_dlgPushSetting.ShowWindow(true);
		m_dlgServer.ShowWindow(false);
		break;
	case 2:
		m_dlgLocalSetting.ShowWindow(false);
		m_dlgPushSetting.ShowWindow(false);
		m_dlgServer.ShowWindow(true);
		break;
	}

	*pResult = 0;
}


void CMySetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_dlgPushSetting.UpdateData(true);
	m_dlgLocalSetting.UpdateData(true);
	m_dlgServer.UpdateData(true);

	g_LocalUser.m_videoProfile = m_dlgLocalSetting.m_videoResolution;
	g_LocalUser.m_bUserHighQualityAudio = m_dlgLocalSetting.m_bUserHighQualityAudio;
    g_LocalUser.m_bEnable_hwaccel = m_dlgLocalSetting.m_bEnable_hwaccel;
    g_LocalUser.m_bEnable_mirror = m_dlgLocalSetting.m_bEnable_mirror;
	g_LocalUser.m_iPort = m_dlgServer.m_iPort;
	if (m_dlgServer.m_csAddr != "")
		MessageBox(m_dlgServer.m_csAddr, "服务器地址", MB_OK);
	g_LocalUser.m_sAddress = m_dlgServer.m_csAddr;
	
	////////
	CString aaid;
	m_dlgServer.m_comboAppID.GetWindowTextA(aaid);
	
	g_LocalUser.m_sAppID = aaid; //m_dlgServer.m_csAppID;

	//MessageBox(g_LocalUser.m_sAppID.c_str());


	g_LocalUser.m_bitrate = m_dlgLocalSetting.m_bitrate;
	g_LocalUser.m_framerate = m_dlgLocalSetting.m_framerate;
	g_LocalUser.m_pushSolution = m_dlgPushSetting.m_comboindex;
	g_LocalUser.m_pushAudioSolution = m_dlgPushSetting.m_comboAudioIndex;
	if ( g_TTTEngine != NULL )
		g_TTTEngine->setAppID(g_LocalUser.m_sAppID.c_str());
	CDialogEx::OnOK();
}
