// LocalSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "LocalSetting.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"

extern C3TLocalUserInfo g_LocalUser;


// CLocalSetting 对话框

IMPLEMENT_DYNAMIC(CLocalSetting, CDialogEx)

CLocalSetting::CLocalSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_LOCALSETTING, pParent)
	, m_videoResolution(5)
	, m_bUserHighQualityAudio(TRUE)
	, m_bitrate(1103)
	, m_framerate(15)
{

}

CLocalSetting::~CLocalSetting()
{
}

BOOL CLocalSetting::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		pMsg->wParam = 0;
	}
	return 0;
}

void CLocalSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboLevel);
	DDX_CBIndex(pDX, IDC_COMBO1, m_videoResolution);
	DDV_MinMaxInt(pDX, m_videoResolution, 0, 6);
	DDX_Control(pDX, IDC_EDIT1, m_edtResolutionCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_edtRateCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_edtFramerateCtrl);
	DDX_Check(pDX, IDC_CHECK1, m_bUserHighQualityAudio);
	DDX_Control(pDX, IDC_CHECK1, m_chkUseHighQualityAudio);
	DDX_Text(pDX, IDC_EDIT2, m_bitrate);
	DDX_Text(pDX, IDC_EDIT3, m_framerate);
}


BEGIN_MESSAGE_MAP(CLocalSetting, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLocalSetting::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK1, &CLocalSetting::OnBnClickedCheck1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CLocalSetting::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CLocalSetting::OnEnKillfocusEdit3)
END_MESSAGE_MAP()


// CLocalSetting 消息处理程序


void CLocalSetting::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	switch (m_videoResolution)
	{
	case 0:
		m_edtResolutionCtrl.SetWindowTextA("160*120");
		m_edtRateCtrl.SetWindowTextA("64");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 1:
		m_edtResolutionCtrl.SetWindowTextA("320*180");
		m_edtRateCtrl.SetWindowTextA("140");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 2:
		m_edtResolutionCtrl.SetWindowTextA("320*240");
		m_edtRateCtrl.SetWindowTextA("200");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 3:
		m_edtResolutionCtrl.SetWindowTextA("640*360");
		m_edtRateCtrl.SetWindowTextA("400");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 4:
		m_edtResolutionCtrl.SetWindowTextA("640*480");
		m_edtRateCtrl.SetWindowTextA("500");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 5:
		m_edtResolutionCtrl.SetWindowTextA("1280*720");
		m_edtRateCtrl.SetWindowTextA("1130");
		m_edtFramerateCtrl.SetWindowTextA("15");
		break;
	case 6:
		m_edtResolutionCtrl.SetWindowTextA("1920*1080");
		m_edtRateCtrl.SetWindowTextA("4096");
		m_edtFramerateCtrl.SetWindowTextA("30");
		break;
	}
}


BOOL CLocalSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboLevel.ResetContent();
	m_comboLevel.InsertString(0, "120P");
	m_comboLevel.InsertString(1, "180P");
	m_comboLevel.InsertString(2, "240P");
	m_comboLevel.InsertString(3, "360P");
	m_comboLevel.InsertString(4, "480P");
	m_comboLevel.InsertString(5, "720P");
	m_comboLevel.InsertString(6, "1080P");
	m_comboLevel.SetCurSel(g_LocalUser.m_videoProfile);
	m_chkUseHighQualityAudio.SetCheck(g_LocalUser.m_bUserHighQualityAudio);
	OnCbnSelchangeCombo1();
	//UpdateData(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLocalSetting::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}


void CLocalSetting::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}


void CLocalSetting::OnEnKillfocusEdit3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
}
