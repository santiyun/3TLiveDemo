// SpeakerTesting.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "SpeakerTesting.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"
//#include "MyAudioApi.h"
#include  "Common.h"
using namespace TTTRtc;
extern IRtcEngine* g_TTTEngine;

extern C3TLocalUserInfo g_LocalUser;


// CSpeakerTesting 对话框

IMPLEMENT_DYNAMIC(CSpeakerTesting, CDialogEx)

CSpeakerTesting::CSpeakerTesting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_csSpeakerName(_T(""))
{

}

CSpeakerTesting::~CSpeakerTesting()
{
}

BOOL CSpeakerTesting::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		pMsg->wParam = 0;
	}
	return 0;
}

void CSpeakerTesting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderVolumeSetting);
	DDX_Control(pDX, IDC_COMBO1, m_comboSpeakerEnum);
	DDX_CBString(pDX, IDC_COMBO1, m_csSpeakerName);
}


BEGIN_MESSAGE_MAP(CSpeakerTesting, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSpeakerTesting::OnSelchangeSpeaker)
	ON_BN_CLICKED(IDC_BUTTON1, &CSpeakerTesting::OnBnClickedPlayMusic)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SLIDER1, &CSpeakerTesting::OnThemechangedSlider1)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CSpeakerTesting::OnThumbposchangingSlider1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CSpeakerTesting::OnBnClickedMfcbutton1)
END_MESSAGE_MAP()


// CSpeakerTesting 消息处理程序


BOOL CSpeakerTesting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int num = 0;
	 num = g_TTTEngine->getNumOfPlayoutDevices();//GetNumOfPlayoutDevices(&num);
	if (num > 0)
	{
		for (int index = 0; index < num; index++)
		{
			char szDeviceName[256] = "";
			char szDeviceID[256] = "";
			int theResult = g_TTTEngine->getPlayoutDeviceName(index, szDeviceName, szDeviceID);
			std::string deviceName = szDeviceName;
			std::wstring wdeviceName = ws_techapi::utf82ws(deviceName);
			CString Name(wdeviceName.c_str());
			//Name = deviceName.c_str();
			m_comboSpeakerEnum.InsertString(index, Name);

			//char CApichar[2048];
			//memset(CApichar, 0, sizeof(CApichar));
			//TTTRtcEngine_GetPlayoutDeviceName(0, CApichar);

			//deviceName = szDeviceID;
			m_mapDeviceIDs.insert(std::make_pair(index, deviceName.c_str()));
			//deviceName = szDeviceName;
		}
		m_comboSpeakerEnum.SetCurSel(0);
		//OnSelchangeMicList();
	}

	m_sliderVolumeSetting.SetRange(0, 255,true);
	m_sliderVolumeSetting.SetPos(160);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSpeakerTesting::OnSelchangeSpeaker()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	g_TTTEngine->stopPlaybackDeviceTest();
}


void CSpeakerTesting::OnBnClickedPlayMusic()
{
	static bool played = false;
	if (played == false)
	{
		int cur = m_comboSpeakerEnum.GetCurSel();
		if (cur < 0) {
			return;
		}
		std::string name = m_mapDeviceIDs.find(cur)->second;
		//std::wstring wname = ws_techapi::s2ws(name);

		//GS_SetDefaultDevice(wname.c_str());
		//setPlaybackDevice(name.c_str());
		g_TTTEngine->setPlayoutDevice(m_comboSpeakerEnum.GetCurSel());
		TCHAR szFilePath[MAX_PATH + 1] = { 0 };
		GetModuleFileName(NULL, szFilePath, MAX_PATH);
		(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
		CString str_url = szFilePath;
		//str_url.Append("TestSnd.wav");
		str_url.Append("01.mp3");

		std::string s_utf8 = ws_techapi::s2utf8(str_url.GetBuffer(str_url.GetLength()));

		g_TTTEngine->startPlaybackDeviceTest(s_utf8.c_str());//  "TestSnd.wav");
	}
	else 
		g_TTTEngine->stopPlaybackDeviceTest();
	played = !played;
}


void CSpeakerTesting::OnThemechangedSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CSpeakerTesting::OnThumbposchangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CSpeakerTesting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int volume = m_sliderVolumeSetting.GetPos();
	g_TTTEngine->setSpeakerVolume(volume);
	//SetSpeakerVolume(volume);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSpeakerTesting::OnBnClickedMfcbutton1()
{
	static bool bPause = false;
	// TODO: 在此添加控件通知处理程序代码
	if (g_TTTEngine != NULL)
	{
		if (bPause == false)
		{
			g_TTTEngine->pauseAudioMixing();
		} else
		{
			g_TTTEngine->resumeAudioMixing();
		}
		bPause = !bPause;
	}
}
