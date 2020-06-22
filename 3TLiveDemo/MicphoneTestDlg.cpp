// MicphoneTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "MicphoneTestDlg.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"
///#include "MyAudioApi.h"
#include  "Common.h"
using namespace TTTRtc;
extern IRtcEngine* g_TTTEngine;

extern C3TLocalUserInfo g_LocalUser;
// CMicphoneTestDlg 对话框

IMPLEMENT_DYNAMIC(CMicphoneTestDlg, CDialogEx)

CMicphoneTestDlg::CMicphoneTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MICPHONETEST, pParent)
	, m_csMicphone(_T(""))
{

}

CMicphoneTestDlg::~CMicphoneTestDlg()
{
	g_TTTEngine->stopRecordingDeviceTest();
}

BOOL CMicphoneTestDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		pMsg->wParam = 0;
	}
	return 0;
}

void CMicphoneTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_MIC, m_volumeShowCtrl);
	DDX_Control(pDX, IDC_COMBO_MIC_LIST, m_comboMicphone);
	DDX_CBString(pDX, IDC_COMBO_MIC_LIST, m_csMicphone);
}


BEGIN_MESSAGE_MAP(CMicphoneTestDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_MIC_LIST, &CMicphoneTestDlg::OnSelchangeMicList)
END_MESSAGE_MAP()


// CMicphoneTestDlg 消息处理程序


BOOL CMicphoneTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int num = 0;
	num = g_TTTEngine->getNumOfRecordingDevices();//GetNumOfRecordingDevices(&num);
	if (num > 0)
	{
		for (int index = 0; index < num; index++)
		{
			char szDeviceName[256] = "";
			char szDeviceID[256] = "";
			int theResult = g_TTTEngine->getRecordingDeviceName(index, szDeviceName, szDeviceID);
			std::string deviceName = szDeviceName;
			std::wstring wdeviceName = ws_techapi::utf82ws(deviceName);
			CString Name(wdeviceName.c_str());
			//Name = deviceName.c_str();
			m_comboMicphone.InsertString(index, Name);
			//deviceName = szDeviceName;
			//deviceName = szDeviceID;
			m_mapDeviceIDs.insert(std::make_pair(index, deviceName.c_str()));
		}
		m_comboMicphone.SetCurSel(0);
		//OnSelchangeMicList();
	}

	m_volumeShowCtrl.SetRange(0, 9);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMicphoneTestDlg::OnSelchangeMicList()
{
	UpdateData(true);
	g_TTTEngine->stopRecordingDeviceTest();
	//CString curDeviceName;
	//m_comboMicphone.GetWindowTextA(curDeviceName);
	int cur = m_comboMicphone.GetCurSel();
	if (cur < 0)
		return;

	std::string name = m_mapDeviceIDs.find(cur)->second;
	//std::string name = curDeviceName.GetBuffer(0);
	//std::wstring wname = ws_techapi::s2ws(name);

	//setRecordingDevice(name.c_str());
	Sleep(2000);
	g_TTTEngine->setRecordingDevice(m_comboMicphone.GetCurSel());

	g_TTTEngine->startRecordingDeviceTest(1000);
}
