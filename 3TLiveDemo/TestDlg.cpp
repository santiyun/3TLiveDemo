// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "C3TEngineEventHandler.h"
#include "C3TLocalUserInfo.h"
#include "OptionDlg.h"
extern IRtcEngine* g_TTTEngine;
extern C3TLocalUserInfo g_LocalUser;
extern C3TEngineEventHandler g_3TEngineEventHandler;


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_TEST, pParent)
	, m_csMsgShow(_T(""))
	, m_csMsg(_T("�Ƿ���Կ�����Ƶ���棿"))
{
	m_bCamera = false;
	m_bMicphone = false;
	m_bSpeaker = false;
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_TESTING, m_tabTestStepByStep);
	//DDX_Text(pDX, IDC_STATIC_MSG_SHOW, m_csMsgShow);
	DDX_Text(pDX, IDC_STATIC_MSG, m_csMsg);
	DDX_Control(pDX, IDC_BUTTON2, m_btnCheck);
	DDX_Control(pDX, IDC_BUTTON1, m_btnCheckError);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_TESTING, &CTestDlg::OnTcnSelchangeTabTesting)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_TESTING, &CTestDlg::OnSelchangingTabTesting)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnClickedNext)
	ON_MESSAGE(WM_ON_AUDIO_VOLUME_REPORT, &CTestDlg::OnAudioVolume)
	
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������


BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tabTestStepByStep.InsertItem(0, "����ͷ");
	m_tabTestStepByStep.InsertItem(1, "��˷�");
	m_tabTestStepByStep.InsertItem(2, "������");
	m_tabTestStepByStep.InsertItem(3, "���Խ��");

	m_dlgCameraTesting.Create(IDD_DLG_CAMERTEST, &m_tabTestStepByStep);
	m_dlgMicphoneTesting.Create(IDD_DLG_MICPHONETEST, &m_tabTestStepByStep);
	m_dlgSpeading.Create(IDD_DIALOG4, &m_tabTestStepByStep);
	m_dlgResult.Create(IDD_DLG_RESULT, &m_tabTestStepByStep);

	CRect rc;
	m_tabTestStepByStep.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 3;
	rc.left += 2;
	rc.right -= 2;

	m_dlgCameraTesting.MoveWindow(&rc);
	m_dlgMicphoneTesting.MoveWindow(&rc);
	m_dlgSpeading.MoveWindow(&rc);
	m_dlgResult.MoveWindow(&rc);
	m_tabTestStepByStep.SetCurSel(0);

	UpdateTabStatus();

	g_3TEngineEventHandler.SetMsgReceiver(GetSafeHwnd());


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CTestDlg::UpdateTabStatus()
{
	m_dlgCameraTesting.ShowWindow(m_tabTestStepByStep.GetCurSel() == 0);
	m_dlgMicphoneTesting.ShowWindow(m_tabTestStepByStep.GetCurSel() == 1);
	m_dlgSpeading.ShowWindow(m_tabTestStepByStep.GetCurSel() == 2);
	m_dlgResult.ShowWindow(m_tabTestStepByStep.GetCurSel() == 3);
}


void CTestDlg::OnTcnSelchangeTabTesting(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateTabStatus();
	int cursel = m_tabTestStepByStep.GetCurSel();
	switch (cursel)
	{
	case 0:
		//g_TTTEngine->stopVideoDeviceTest();
		this->m_csMsg = "�Ƿ���Կ�����Ƶ���棿";
		this->m_dlgCameraTesting.OnCurCameraSelchange();
		this->m_btnCheck.ShowWindow(SW_SHOW);
		this->m_btnCheckError.ShowWindow(SW_SHOW);
		this->m_btnCheck.SetWindowTextA("���õ�");
		this->m_btnCheckError.SetWindowTextA("������");
		break;
	case 1:
		this->m_csMsg = "�Ƿ���Կ�������������";
		this->m_dlgMicphoneTesting.OnSelchangeMicList();
		this->m_btnCheck.ShowWindow(SW_SHOW);
		this->m_btnCheckError.ShowWindow(SW_SHOW);
		this->m_btnCheck.SetWindowTextA("���õ�");
		this->m_btnCheckError.SetWindowTextA("������");
		//g_TTTEngine->stopRecordingDeviceTest();
		break;
	case 2:
		this->m_csMsg = "�Ƿ��������������";
		this->m_dlgSpeading.OnSelchangeSpeaker();
		this->m_btnCheck.ShowWindow(SW_SHOW);
		this->m_btnCheckError.ShowWindow(SW_SHOW);
		this->m_btnCheck.SetWindowTextA("���õ�");
		this->m_btnCheckError.SetWindowTextA("������");
		break;
	case 3:
		m_dlgResult.showResult(m_bCamera, m_bMicphone, m_bSpeaker);
		this->m_btnCheck.ShowWindow(SW_HIDE);
		this->m_btnCheckError.ShowWindow(SW_HIDE);
		this->m_btnCheckError.SetWindowTextA("ȷ��");
		break;
	}
	UpdateData(false);

	*pResult = 0;
}


void CTestDlg::OnBnClickedButton1()
{
	// TODO: Show Message to close test proce
	int cursel = m_tabTestStepByStep.GetCurSel();
	if (cursel == 3)
		return;
	COptionDlg dlg;
	dlg.DoModal();

	long res = 0;
	OnSelchangingTabTesting(NULL, &res);

	switch (cursel)
	{
	case 0:
		//g_TTTEngine->stopVideoDeviceTest();
		m_bCamera = false;
		break;
	case 1:
		m_bMicphone = false;
		//g_TTTEngine->stopRecordingDeviceTest();
		break;
	case 2:
		m_bSpeaker = false;
		//g_TTTEngine->stopPlaybackDeviceTest();
		break;
	}

	this->m_tabTestStepByStep.SetCurSel(m_tabTestStepByStep.GetCurSel() + 1);
	UpdateData(true);
	OnTcnSelchangeTabTesting(NULL, &res);
	UpdateTabStatus();
}


void CTestDlg::OnSelchangingTabTesting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cursel = m_tabTestStepByStep.GetCurSel();
	switch (cursel)
	{
	case 0:
		g_TTTEngine->stopLocalVideoTest();
		break;
	case 1:
		g_TTTEngine->stopRecordingDeviceTest();
		break;
	case 2:
		g_TTTEngine->stopPlaybackDeviceTest();
		break;
	}
	*pResult = 0;
}


void CTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::string name = this->m_dlgCameraTesting.m_csDeviceName.GetBuffer(0);
	//std::wstring wname = ws_techapi::s2ws(name);
	g_LocalUser.m_wsDeviceName = ws_techapi::s2ws(name);

	CDialogEx::OnOK();
}


void CTestDlg::OnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������y
	long res = 0;
	OnSelchangingTabTesting(NULL, &res);

	int cursel = m_tabTestStepByStep.GetCurSel();
	switch (cursel)
	{
	case 0:
		//g_TTTEngine->stopVideoDeviceTest();
		m_bCamera = true;
		break;
	case 1:
		m_bMicphone = true;
		//g_TTTEngine->stopRecordingDeviceTest();
		break;
	case 2:
		m_bSpeaker = true;
		//g_TTTEngine->stopPlaybackDeviceTest();
		break;
	case 3:
		//dlgResult.showResult(m_bCamera, m_bMicphone, m_bSpeaker);
		break;
	}

	this->m_tabTestStepByStep.SetCurSel(m_tabTestStepByStep.GetCurSel() + 1);
	UpdateData(true);
	OnTcnSelchangeTabTesting(NULL, &res);
	UpdateTabStatus();

}

LRESULT CTestDlg::OnAudioVolume(WPARAM wParam, LPARAM lParam)
{
	int volume = lParam % 10;
	m_dlgMicphoneTesting.m_volumeShowCtrl.SetPos(volume);
	return 0;
}

