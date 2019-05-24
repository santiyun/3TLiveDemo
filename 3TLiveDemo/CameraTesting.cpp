// CameraTesting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "CameraTesting.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"
//#include "MyVideoApi.h"
#include  "Common.h"

using namespace TTTRtc;

extern IRtcEngine* g_TTTEngine;

extern C3TLocalUserInfo g_LocalUser;

// CCameraTesting 对话框

IMPLEMENT_DYNAMIC(CCameraTesting, CDialogEx)

CCameraTesting::CCameraTesting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CAMERTEST, pParent)
	, m_csDeviceName(_T(""))
{

}

CCameraTesting::~CCameraTesting()
{
}

void CCameraTesting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEST_VIDEO_SHOW, m_videoShowCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_comboDeviceEnum);
	DDX_CBString(pDX, IDC_COMBO1, m_csDeviceName);
}


BEGIN_MESSAGE_MAP(CCameraTesting, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCameraTesting::OnCurCameraSelchange)
END_MESSAGE_MAP()


// CCameraTesting 消息处理程序


BOOL CCameraTesting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int num = IVideoDevice::getCount();
	if (num > 0 )
	{
		for (int index = 0; index < num; index++)
		{
			wchar_t szDeviceName[256] = L"";
			VideoDeviceInfo devinfo;
			int theResult = IVideoDevice::getInfo(index, &devinfo);
			std::string deviceName = devinfo.frendlyName;
			//unsigned int nameLength = sizeof(szDeviceName) / sizeof(szDeviceName[0]);
			//::GS_GetVideoDeviceName(index, szDeviceName, &deviceType);
			//std::wstring deviceName = szDeviceName;
			CString Name(deviceName.c_str());
			Name = deviceName.c_str();
			m_comboDeviceEnum.InsertString(index, Name);
			//deviceName = szDeviceName;
		}
		m_comboDeviceEnum.SetCurSel(0);
		OnCurCameraSelchange();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCameraTesting::OnCurCameraSelchange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	g_TTTEngine->stopLocalVideoTest();

	LocalVideoConfig cfg;
	cfg.userID = g_LocalUser.m_uid;
	cfg.type = VIDEO_CAPTURE_CAMERA;
	cfg.devIndex = m_comboDeviceEnum.GetCurSel();
	cfg.height = 480;
	cfg.width = 640;
	cfg.framerate = 15;
	cfg.viewHwnd = m_videoShowCtrl.GetSafeHwnd();

	g_TTTEngine->startLocalVideoTest(cfg);
}

