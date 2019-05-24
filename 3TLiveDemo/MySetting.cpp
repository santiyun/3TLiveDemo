// MySetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "MySetting.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"

using namespace TTTRtc;

extern C3TLocalUserInfo g_LocalUser;
extern IRtcEngine* g_TTTEngine;

// CMySetting �Ի���

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


// CMySetting ��Ϣ�������


BOOL CMySetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tabSetting.InsertItem(0, "��������");
	m_tabSetting.InsertItem(1, "��������");
	m_tabSetting.InsertItem(2, "����������");

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
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMySetting::OnTcnSelchangeTabsetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_LocalUser.m_videoProfile = m_dlgLocalSetting.m_videoResolution;
	g_LocalUser.m_bUserHighQualityAudio = m_dlgLocalSetting.m_bUserHighQualityAudio;
	g_LocalUser.m_iPort = m_dlgServer.m_iPort;
	g_LocalUser.m_sAddress = m_dlgServer.m_csAddr;
	g_LocalUser.m_sAppID = m_dlgServer.m_csAppID;
	if ( g_TTTEngine != NULL )
		g_TTTEngine->setAppID(g_LocalUser.m_sAppID.c_str());
	CDialogEx::OnOK();
}
