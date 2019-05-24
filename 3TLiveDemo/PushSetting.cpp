// PushSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "PushSetting.h"
#include "afxdialogex.h"


// CPushSetting 对话框

IMPLEMENT_DYNAMIC(CPushSetting, CDialogEx)

CPushSetting::CPushSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_PUSHSETTING, pParent)
	, m_comboindex(0)
	, m_comboCodecIndex(0)
	, m_comboAudioIndex(0)
{

}

CPushSetting::~CPushSetting()
{
}

void CPushSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboSolution);
	DDX_CBIndex(pDX, IDC_COMBO1, m_comboindex);
	DDX_CBIndex(pDX, IDC_COMBO2, m_comboCodecIndex);
	DDX_Control(pDX, IDC_COMBO2, m_comboCodec);
	DDX_Control(pDX, IDC_COMBO3, m_comboAudiofrequnce);
	DDX_CBIndex(pDX, IDC_COMBO3, m_comboAudioIndex);
	DDX_Control(pDX, IDC_EDIT1, m_edtSize);
	DDX_Control(pDX, IDC_EDIT2, m_edtBitrate);
	DDX_Control(pDX, IDC_EDIT3, m_edtFramerate);
}


BEGIN_MESSAGE_MAP(CPushSetting, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPushSetting::OnCbnSelchangeComboSolution)
END_MESSAGE_MAP()


// CPushSetting 消息处理程序


BOOL CPushSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboSolution.ResetContent();
	m_comboSolution.InsertString(0, "480P");
	m_comboSolution.InsertString(1, "720P");
	m_comboSolution.InsertString(2, "1080P");
	m_comboSolution.SetCurSel(0);

	m_comboCodec.ResetContent();
	m_comboCodec.InsertString(0, "H.264");
	m_comboCodec.InsertString(1, "H.265");
	m_comboCodec.SetCurSel(0);

	m_comboAudiofrequnce.ResetContent();
	m_comboAudiofrequnce.InsertString(0, "48kHz-单声道");
	m_comboAudiofrequnce.InsertString(1, "44.1kHz-双声道");
	m_comboAudiofrequnce.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPushSetting::OnCbnSelchangeComboSolution()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	switch (m_comboindex)
	{
	case 0:
		m_edtSize.SetWindowTextA("640*480");
		m_edtBitrate.SetWindowTextA("500Kbps");
		m_edtFramerate.SetWindowTextA("15fps");
		break;
	case 1:
		m_edtSize.SetWindowTextA("1280*720");
		m_edtBitrate.SetWindowTextA("1130Kbps");
		m_edtFramerate.SetWindowTextA("15fps");
		break;
	case 2:
		m_edtSize.SetWindowTextA("1920&1080");
		m_edtBitrate.SetWindowTextA("2080Kbps");
		m_edtFramerate.SetWindowTextA("15fps");
		break;
	}

}
