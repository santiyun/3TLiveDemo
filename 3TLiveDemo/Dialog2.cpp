// Dialog2.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "Dialog2.h"
#include "afxdialogex.h"
#include "C3TLocalUserInfo.h"
#include "C3TEngineEventHandler.h"
#include "DialogAnchorLink.h"

#include "map"

extern IRtcEngine* g_TTTEngine;
extern C3TEngineEventHandler g_3TEngineEventHandler;
extern C3TLocalUserInfo g_LocalUser;


// CDialog2 对话框

IMPLEMENT_DYNAMIC(CDialog2, CDialog)

CDialog2::CDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
	, m_csRoomNum(_T(""))
	, m_csClientRole(_T(""))
	, m_csUserID(_T(""))
	, m_csParticipants(_T(""))
	, m_csVideoUpload(_T(""))
	, m_csAudioUpload(_T(""))
	, m_csPushURL(_T(""))
	, m_Video0Info(_T(""))
	, m_Video2Info(_T(""))
	, m_Video3Info(_T(""))
	, m_Video4Info(_T(""))
	, m_Video5Info(_T(""))
	, m_curSelRemoteParticipant(0)
{
	m_bJoinChannel = false;
	m_bSDKTEST = false;
	m_Status = LiveStatus::STATUS_INIT;
	m_TotleParticipants = 0;
	m_CurSelVideoIndex = 0;

	memset(m_hWndsforClient, 0, sizeof(m_hWndsforClient));
	//memset(m_hWndClientUID, 0, sizeof(m_hWndClientUID));
	memset(m_ClientAudioStreamMute, 0, sizeof(m_ClientAudioStreamMute));
	memset(m_ClientVideoStreamMute, 0, sizeof(m_ClientVideoStreamMute));
	_CrtSetBreakAlloc(152);
	m_sharedata = false;
	m_secondMedia = "";
}
long long stringToll(const std::string& strValue)
{
	long long nValue = 0;
	sscanf(strValue.c_str(), "%lld", &nValue);
	return nValue;
}
CDialog2::~CDialog2()
{
}

bool CDialog2::isLiveMaster()
{ 
	return g_LocalUser.m_clientRole == 1;  
}
bool CDialog2::isLiveParticipant()
{ 
	return g_LocalUser.m_clientRole == 2; 
}
bool CDialog2::isGuest()
{ 
	return g_LocalUser.m_clientRole == 3;
}


void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, btnOK);
	DDX_Control(pDX, IDC_LIST1, m_MsgLst);
	DDX_Text(pDX, IDC_STATIC_ROOMNUM, m_csRoomNum);
	DDX_Text(pDX, IDC_STATIC_CLIENTROLE, m_csClientRole);
	DDX_Text(pDX, IDC_STATIC_UID, m_csUserID);
	DDX_Text(pDX, IDC_STATIC_LIVENUM, m_csParticipants);
	DDX_Text(pDX, IDC_STATIC_VIDEO_UPLOAD, m_csVideoUpload);
	DDX_Text(pDX, IDC_STATIC_AUDIO_UPLOAD, m_csAudioUpload);
	DDX_Text(pDX, IDC_STATIC_PUSHUURL, m_csPushURL);
	DDX_Text(pDX, IDC_STATIC_VIDEO_TEXT1, m_Video0Info);
	DDX_Text(pDX, IDC_STATIC_VIDEO_TEXT2, m_Video2Info);
	DDX_Text(pDX, IDC_STATIC_VIDEO_TEXT3, m_Video3Info);
	DDX_Text(pDX, IDC_STATIC_VIDEO_TEXT4, m_Video4Info);
	DDX_Text(pDX, IDC_STATIC_VIDEO_TEXT5, m_Video5Info);
	DDX_Control(pDX, IDC_BTN_MUTE_REMOTE_AUDIO, m_btnMuteRemoteAudio);
	DDX_Control(pDX, IDC_BTN_KICK_OUT, m_btnKickOut);
	DDX_Control(pDX, IDC_BTN_MUTE_UNMUTE_SPEAKER, m_btnMuteUnmuteSpeaker);
	DDX_Control(pDX, IDC_BTN_MUTE_UNMUTE_MIC, m_btnMuteUnmuteMic);
	DDX_Control(pDX, IDC_BTN_MUTE_UNMUTE_CAMERA, m_btnMuteUnmuteCamera);
	DDX_Control(pDX, IDC_BTN_MP4_PLAY, m_btnPlayMp4);
	DDX_Control(pDX, IDC_BTN_MUTE_UNMUTE_NETSTAT, m_btnShowNetStat);
	DDX_Control(pDX, IDC_BTN_UPGRADE_CLIENTROLE, m_btnUpgradeClientrole);
	DDX_Radio(pDX, IDC_RADIO7, m_curSelRemoteParticipant);
	DDX_Control(pDX, IDC_STATIC_MP4, m_ShowMp4);
	DDX_Control(pDX, IDC_BTN_AnchorLink, m_btnAnchorLink);
	DDX_Control(pDX, IDC_SLIDER_MICVOLUME, m_sliderMicVolume);
	DDX_Control(pDX, IDC_SLIDER_MICVOLUME2, m_sliderSpeakerVolume);
}

int CDialog2::joinChannel()
{
	int nReponse = 0;
	if (g_TTTEngine != NULL)
	{
		m_Status = LiveStatus::STATUS_JOINING;
		
		g_TTTEngine->setChannelProfile(g_LocalUser.m_channelProfile);

		if(g_LocalUser.m_enableVideo)
			g_TTTEngine->enableVideo();
		g_TTTEngine->setClientRole(g_LocalUser.m_clientRole, NULL);

		g_TTTEngine->setHighQualityAudioParameters(g_LocalUser.m_bUserHighQualityAudio);
		int roomid = stringToll(g_LocalUser.m_roomID.c_str());
		//59.110.220.79 iplocation 端口 11000
		//g_TTTEngine->setServerAddr("47.106.248.181", 5000);
		//g_TTTEngine->setServerAddr("edu.3ttech.cn", 11000);

		if ( g_LocalUser.m_sAddress != "")
			g_TTTEngine->setServerAddr(g_LocalUser.m_sAddress.c_str(), g_LocalUser.m_iPort);
		PublisherConfig cfg;
		memset(cfg.publishUrl, 0, 1024);
		memcpy(cfg.publishUrl, g_LocalUser.m_pushUrl.c_str(), g_LocalUser.m_pushUrl.length());
		//g_TTTEngine->configPublisher(cfg);
		g_TTTEngine->setVideoMixerBackgroundImgUrl("http://3ttech.cn/res/tpl/default/images/bk.png");

		LocalVideoConfig cfg2;


		//LocalVideoConfig cfg;
		cfg2.userID = g_LocalUser.m_uid;
		cfg2.type = VIDEO_CAPTURE_CAMERA;

		switch (g_LocalUser.m_videoProfile)
		{
		case 0:
			cfg2.width = 160;
			cfg2.height = 112;
			cfg2.framerate = 15;
			//config.videoBitRate = 65;
			break;
		case 1:
			cfg2.width = 320;
			cfg2.height = 176;
			cfg2.framerate = 15;
			break;
		case 2:
			cfg2.width = 320;
			cfg2.height = 240;
			cfg2.framerate = 15;
			break;
		case 3:
			cfg2.width = 640;
			cfg2.height = 352;
			cfg2.framerate = 15;
			break;
		case 4:
			cfg2.width = 640;
			cfg2.height = 480;
			cfg2.framerate = 15;
			break;
		case 5:
			cfg2.width = 1280;
			cfg2.height = 720;
			cfg2.framerate = 15;
			break;
		case 6:
			cfg2.width = 1920;
			cfg2.height = 1080;
			cfg2.framerate = 15;
			break;
		default:
			cfg2.width = 640;
			cfg2.height = 480;
			cfg2.framerate = 15;
			break;
		}
		CStatic   *pStatic = NULL;
		int index = 0;
		switch (g_LocalUser.m_clientRole)
		{
		case 1:
			pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MAINVIDEO);
			cfg2.viewHwnd = pStatic->GetSafeHwnd();
			index = 0;
			break;
		case 2:
		case 3:
			pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO1);
			cfg2.viewHwnd = pStatic->GetSafeHwnd();
			index = 1;
			break;
		}

		uid_ttt uid = g_LocalUser.m_uid;
		UserDeviceConfig udc0(uid, "", true);
		udc0.userRole = g_LocalUser.m_clientRole;
		m_mapParticipants.insert(std::make_pair(uid, udc0));
		std::string mediaID = "";
		if (CLIENT_ROLE_AUDIENCE != g_LocalUser.m_clientRole) {
			int count = IVideoDevice::getCount();
			if (count > 0)
				cfg2.devIndex = 0;
			else {
				MessageBox("没有摄像头！", "提示", MB_OK);
				return -1;
			}

			//IVideoDevice::getInfo(0, &cfg.devInfo);

			char* id = g_TTTEngine->createLocalVideo(cfg2);
			if (id) {
				mediaID = id;
			}
			else
			{
				return nReponse;
			}
		}

		m_LivingMemberArray[index].mUserID = uid;
		m_LivingMemberArray[index].mDeviceID = mediaID.c_str();
		//OnClickedBtnDataShare();

		g_TTTEngine->joinChannel(stringToll(g_LocalUser.m_roomID.c_str()), NULL, g_LocalUser.m_uid);
	}
	return nReponse;
}


BEGIN_MESSAGE_MAP(CDialog2, CDialog)
	ON_BN_CLICKED(IDOK, &CDialog2::OnBnClickedOk)
	ON_COMMAND(IDCLOSE, &CDialog2::OnIdclose)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ON_JOINCHANNELSUCCESS, &CDialog2::OnJoinChannel)
	ON_MESSAGE(WM_ON_LEAVECHANNEL, &CDialog2::OnLeaveChannel)
	ON_MESSAGE(WM_ON_ERROR, &CDialog2::OnError)
	ON_MESSAGE(WM_ON_CONNECTLOST, &CDialog2::OnConnectionLost)
	ON_MESSAGE(WM_ON_USEROFFLIEN, &CDialog2::OnUserOffline)
	ON_MESSAGE(WM_ON_USERJOINED, &CDialog2::OnUserOnline)
	ON_MESSAGE(WM_ON_RTCSTATE_REP, &CDialog2::OnRtcState)
	ON_MESSAGE(WM_ON_REMOTE_VIDEO_STATS, &CDialog2::OnRemoteVideoState)
	ON_MESSAGE(WM_ON_REMOTE_USER_VIDEO_ENABLE, &CDialog2::OnRemoteVideoEnable)
	ON_MESSAGE(WM_ON_MP4_JOINED, &CDialog2::OnMP4Joined)
	ON_MESSAGE(WM_ON_MIXERVIDEO_CREATE, &CDialog2::OnMixerVideoCreate)

	ON_BN_CLICKED(IDC_STATIC_MAINVIDEO, &CDialog2::OnBnClickedStaticMainvideo)
	ON_BN_DOUBLECLICKED(IDC_STATIC_MAINVIDEO, &CDialog2::OnBnDoubleclickedStaticMainvideo)
	ON_STN_CLICKED(IDC_STATIC_VIDEO1, &CDialog2::OnClickedStaticVideo1)
	ON_STN_CLICKED(IDC_STATIC_VIDEO2, &CDialog2::OnClickedStaticVideo2)
	ON_STN_CLICKED(IDC_STATIC_VIDEO3, &CDialog2::OnClickedStaticVideo3)
	ON_STN_CLICKED(IDC_STATIC_VIDEO4, &CDialog2::OnClickedStaticVideo4)
	ON_STN_CLICKED(IDC_STATIC_VIDEO5, &CDialog2::OnClickedStaticVideo5)
	ON_BN_CLICKED(IDC_BTN_MUTE_REMOTE_AUDIO, &CDialog2::OnClickedBtnMuteRemoteAudio)
	ON_BN_CLICKED(IDC_BTN_MUTE_UNMUTE_CAMERA, &CDialog2::OnClickedBtnMuteUnmuteCamera)
	ON_BN_CLICKED(IDC_BTN_MUTE_UNMUTE_MIC, &CDialog2::OnClickedBtnMuteUnmuteMic)
	ON_BN_CLICKED(IDC_BTN_MUTE_UNMUTE_NETSTAT, &CDialog2::OnClickedBtnMuteUnmuteNetstat)
	ON_BN_CLICKED(IDC_BTN_MUTE_UNMUTE_SPEAKER, &CDialog2::OnClickedBtnMuteUnmuteSpeaker)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_CLIENTROLE, &CDialog2::OnClickedBtnUpgradeClientrole)
	ON_BN_CLICKED(IDC_BTN_KICK_OUT, &CDialog2::OnClickedBtnKickOut)
	ON_BN_CLICKED(IDC_BTN_MP4_PLAY, &CDialog2::OnClickedBtnMp4Play)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog2::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BTN_AnchorLink, &CDialog2::OnClickedBtnAnchorlink)
	ON_BN_CLICKED(IDC_BTN_MUTE_REMOTE_VIDEO, &CDialog2::OnBnClickedBtnMuteRemoteVideo)
	ON_BN_CLICKED(IDC_BTN_SETVOLUME, &CDialog2::OnBnClickedBtnSetvolume)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SLIDER_MICVOLUME, &CDialog2::OnNMThemeChangedSliderMicvolume)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SETSEI, &CDialog2::OnClickedBtnDataShare)
	ON_BN_CLICKED(IDC_BTN_2_CAMERA, &CDialog2::OnBnClickedBtn2Camera)
END_MESSAGE_MAP()


// CDialog2 消息处理程序


void CDialog2::OnBnClickedOk()
{
	//this->joinChannel();
	ReleaseChannel();
	CDialog::OnOK();
}


void CDialog2::SDKTestTimer()
{
	m_bSDKTEST = true;
	//this->SetTimer(125, 30000, NULL);
}

void CDialog2::KillSDKTimer()
{
	this->KillTimer(125);
}


BOOL CDialog2::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_MsgLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_MsgLst.InsertColumn(0, "类型", LVCFMT_LEFT, 80);
	m_MsgLst.InsertColumn(1, "错误码", LVCFMT_LEFT, 140);
	m_MsgLst.InsertColumn(2, "备注", LVCFMT_LEFT, 100);

	this->initLayout();

	// TODO:  在此添加额外的初始化
	g_3TEngineEventHandler.SetMsgReceiver(this->GetSafeHwnd());
	//g_LocalUser.m_cbMsgHandler = this->GetSafeHwnd();
	if (m_bJoinChannel && m_Status == LiveStatus::STATUS_INIT)
		this->joinChannel();

	m_sliderMicVolume.SetRange(0, 255, true);
	m_sliderMicVolume.SetTicFreq(1);
	m_sliderMicVolume.SetPos(160);
	m_sliderSpeakerVolume.SetRange(0, 255, true);
	m_sliderSpeakerVolume.SetTicFreq(1);
	m_sliderSpeakerVolume.SetPos(160);

	//m_vclayout.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog2::OnIdclose()
{
	// TODO: 在此添加命令处理程序代码
	OnClose();
}

void CDialog2::ReleaseChannel()
{
	//if (m_Status == LiveStatus::STATUS_JOINED)
	{
		int index = 1;
		if (this->isLiveMaster())
			index = 0;
		g_TTTEngine->stopPreview(m_LivingMemberArray[index].mDeviceID.c_str());
		g_TTTEngine->releaseLocalVideo(m_LivingMemberArray[index].mDeviceID.c_str());
		g_TTTEngine->releaseLocalVideo(m_screenMedia.c_str());
		m_screenMedia = "";
		m_sharedata = false;
		g_TTTEngine->releaseLocalVideo(m_secondMedia.c_str());
		m_secondMedia = "";

		
		//g_TTTEngine->releaseAllRemoteVideo();
		if (g_3TEngineEventHandler.getMixerMID() != "")
			g_TTTEngine->releaseMixerVideo(g_3TEngineEventHandler.getMixerMID().c_str());
		g_3TEngineEventHandler.resetMixerMID();
		ReleaseAllVideo();
		if (m_mixing) {
			g_TTTEngine->stopAudioMixing();
			m_mixing = false;
		}
		g_TTTEngine->leaveChannel();
		m_Status = LiveStatus::STATUS_LEAVING;
	}
}


void CDialog2::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseChannel();
	CDialog::OnClose();
}

void CDialog2::ReleaseAllVideo()
{
	for (int i = 0; i < 50; i++)
	{
		if (m_hWndsforClient[i] == 1)
		{
			if (i == 0 && isLiveMaster())
				continue;
			if ( i == 1 && isLiveParticipant())
				continue;
			g_TTTEngine->releaseRemoteVideo(m_LivingMemberArray[i].mUserID, m_LivingMemberArray[i].mDeviceID.c_str());
		}
	}
}


LRESULT CDialog2::OnJoinChannel(WPARAM wParam, LPARAM lParam)
{
	uid_ttt uid = lParam;
	g_LocalUser.m_uid = uid;

	//set push url
	g_LocalUser.m_pushUrl = "rtmp://push.3ttech.cn/sdk/";
	g_LocalUser.m_pushUrl = g_LocalUser.m_pushUrl + g_LocalUser.m_roomID;


	m_TotleParticipants++;
	m_csParticipants = std::to_string(m_TotleParticipants).c_str();

	UpdateBtnStatus();

	this->m_Status = LiveStatus::STATUS_JOINED;

	m_csRoomNum = g_LocalUser.m_roomID.c_str();
	std::string clientRole = "";
	if (1 == g_LocalUser.m_clientRole) {
		clientRole = "主播";
	}
	else if (2 == g_LocalUser.m_clientRole) {
		clientRole = "副播";
	}
	else if (3 == g_LocalUser.m_clientRole) {
		clientRole = "观众";
	}
	m_csClientRole = clientRole.c_str();
	m_csUserID = std::to_string(g_LocalUser.m_uid).c_str();
	m_csPushURL = g_LocalUser.m_pushUrl.c_str();

	InsertMsgAndEvent("event", "0", "JoinChannelSuccess");
	UpdateData(false);
	LocalVideoConfig cfg;
	cfg.userID = g_LocalUser.m_uid;
	cfg.type = VIDEO_CAPTURE_CAMERA;
	cfg.renderScaleType = VIDEO_SCALE_FIT;
	cfg.encScaleType = VIDEO_SCALE_FIT;
	//cfg.devIndex = 454646445;

	switch (g_LocalUser.m_videoProfile)
	{
	case 0:
		cfg.width = 160;
		cfg.height = 112;
		cfg.framerate = 15;
		//config.videoBitRate = 65;
		break;
	case 1:
		cfg.width = 320;
		cfg.height = 176;
		cfg.framerate = 15;
		break;
	case 2:
		cfg.width = 320;
		cfg.height = 240;
		cfg.framerate = 15;
		break;
	case 3:
		cfg.width = 640;
		cfg.height = 352;
		cfg.framerate = 15;
		break;
	case 4:
		cfg.width = 640;
		cfg.height = 480;
		cfg.framerate = 15;
		break;
	case 5:
		cfg.width = 1280;
		cfg.height = 720;
		cfg.framerate = 15;
		break;
	case 6:
		cfg.width = 1920;
		cfg.height = 1080;
		cfg.framerate = 15;
		break;
	default:
		cfg.width = 640;
		cfg.height = 480;
		cfg.framerate = 15;
		break;
	}
	CStatic   *pStatic = NULL;
	int index = 0;
	switch (g_LocalUser.m_clientRole)
	{
	case 1:
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MAINVIDEO);
		cfg.viewHwnd = pStatic->GetSafeHwnd();
		index = 0;
		break;
	case 2:
	case 3:
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO1);
		cfg.viewHwnd = pStatic->GetSafeHwnd();
		index = 1;
		break;
	}

	//UserDeviceConfig udc0(uid, "", true);
	//udc0.userRole = g_LocalUser.m_clientRole;
	//m_mapParticipants.insert(std::make_pair(uid, udc0));

	//int count = IVideoDevice::getCount();
	//if (count > 0)
	//	cfg.devIndex = 0;
	//	//IVideoDevice::getInfo(0, &cfg.devInfo);

	//std::string mediaID = g_TTTEngine->createLocalVideo(cfg);
	//
	//addMixerVideo(uid, mediaID.c_str(), isLiveMaster());

	//g_TTTEngine->startPreview(mediaID.c_str());
	//UserDeviceConfig udc(uid, mediaID, true);
	//udc.hwndindex = index;
	//m_mapStreams.insert( std::make_pair(mediaID, udc) );

	//m_hWndsforClient[index] = 1;
	////m_LivingMemberArray[index].mHwndindex = index; 
	//m_LivingMemberArray[index].mUserID = uid;
	//m_LivingMemberArray[index].mDeviceID = mediaID;
	////m_btnMuteRemoteAudio.set
	
	// merge with zkb   for  capture camera before enter room
	//UserDeviceConfig udc0(uid, "", true);
	//udc0.userRole = g_LocalUser.m_clientRole;
	//m_mapParticipants.insert(std::make_pair(uid, udc0));

	//int count = IVideoDevice::getCount();
	//if (count > 0)
	//	cfg.devIndex = 0;
	//	//IVideoDevice::getInfo(0, &cfg.devInfo);

	//std::string mediaID = g_TTTEngine->createLocalVideo(cfg);
	//g_TTTEngine->stopPreview(m_LivingMemberArray[index].mDeviceID.c_str());
	m_LivingMemberArray[index].mUserID = g_LocalUser.m_uid;
	addMixerVideo(uid, m_LivingMemberArray[index].mDeviceID.c_str(), isLiveMaster());

	//addMixerVideo(uid, mediaID.c_str(), isLiveMaster());
	g_TTTEngine->startPreview(m_LivingMemberArray[index].mDeviceID.c_str());
	m_openedCamera = true;
	//g_TTTEngine->startPreview(mediaID.c_str());
	UserDeviceConfig udc(uid, m_LivingMemberArray[index].mDeviceID.c_str(), true);
	udc.hwndindex = index;
	m_mapStreams.insert( std::make_pair(m_LivingMemberArray[index].mDeviceID.c_str(), udc) );

	m_hWndsforClient[index] = 1;
	//m_LivingMemberArray[index].mHwndindex = index; 
	//m_LivingMemberArray[index].mUserID = uid;
	//m_LivingMemberArray[index].mDeviceID = m_LivingMembferArray[index].mDeviceID.c_str();
	//m_btnMuteRemoteAudio.set
	g_TTTEngine->setSpeakerphoneVolume(160);

	if (m_bSDKTEST)
		this->SetTimer(125, 15000, NULL);

	return 0;
}

LRESULT CDialog2::OnLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	ReleaseChannel();
	m_Status = LiveStatus::STATUS_INIT;

	//////if (g_TTTEngine != NULL)
	//////	g_TTTEngine->stopPreview();
	if (g_LocalUser.m_clientRole == 1)
	{
		m_hWndsforClient[0] = 0;
		m_mapStreams.erase(m_LivingMemberArray[0].mDeviceID);
	}
	else {
		m_hWndsforClient[1] = 0;
		m_mapStreams.erase(m_LivingMemberArray[1].mDeviceID);
	}

	m_TotleParticipants--;
	m_csParticipants = std::to_string(m_TotleParticipants).c_str();
	UpdateData(false);

	int reson = lParam;
	//RtcStats_TTT  *lpData = (RtcStats_TTT *)wParam;
	//delete lpData;
	//lpData = NULL;

	m_mapParticipants.erase(g_LocalUser.m_uid);

	InsertMsgAndEvent("Event", "0", "OnLeaveChannel");
	
	//判断是否离开，是就关闭
	if (m_bSDKTEST)
		this->KillSDKTimer();
	OnBnClickedOk();
	return 0;
}

LRESULT CDialog2::OnError(WPARAM wParam, LPARAM lParam)
{
	//////if (m_Status == LiveStatus::STATUS_JOINING)
	//////	g_TTTEngine->stopPreview();

	int code = lParam;
	std::string scode = std::to_string(code);
	InsertMsgAndEvent("Error", scode.c_str(), "OnError");
	return 0;
}

LRESULT CDialog2::OnConnectionLost(WPARAM wParam, LPARAM lParam)
{
	InsertMsgAndEvent("Error", "Connection lost!", "OnError");
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CDialog2::OnRemoteVideoEnable(WPARAM wParam, LPARAM lParam)
{
	RemoteVideoConfig* cfg = (RemoteVideoConfig*)wParam;
	cfg->renderScaleType = VIDEO_SCALE_FIT;
	uint64_t uid = cfg->userID;
	std::string mid = cfg->mediaID;
	bool enabled = (bool)lParam;

	char buf[256] = { 0 };
	sprintf(buf, "用户 设置视频状态onUserEnableVideo，enable = %d \n",  enabled);
	OutputDebugStringA(buf);
	InsertMsgAndEvent("Select user", buf, buf);

	int role = 1;
	if (m_mapParticipants.find(uid) != m_mapParticipants.end())
		role = m_mapParticipants.at(uid).userRole;

	if (true == enabled)
	{
		int index = 0;
		if (role == 1 && m_hWndsforClient[0] != 1) //主播
		{
			//vc.uid = uid;
			CStatic   *pStatic = NULL;
			pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MAINVIDEO);
			//debug 2019-3-28
			cfg->hwnd = pStatic->GetSafeHwnd();
			//cfg->hwnd = (void *)-123;
			//open remote video stream 
			if (g_TTTEngine != NULL)
			{
				int rs = g_TTTEngine->createRemoteVideo(*cfg);
				//assert(rs == 0);
			}
			OutputDebugStringA("onUserEnableVideo master create");
		}
		else {
			for (index = 1; index < 50; index++)
			{
				if (g_LocalUser.m_clientRole != 1 && index == 1)
					continue;
				if (m_hWndsforClient[index] == 0)
				{
					CStatic   *pStatic = NULL;

					switch (index)
					{
					case 1:
						pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO1);
						//pStatic->set
						cfg->hwnd = pStatic->GetSafeHwnd();
						break;
					case 2:
						pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO2);
						cfg->hwnd = pStatic->GetSafeHwnd();
						break;
					case 3:
						pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO3);
						cfg->hwnd = pStatic->GetSafeHwnd();
						break;
					case 4:
						pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO4);
						cfg->hwnd = pStatic->GetSafeHwnd();
						break;
					case 5:
						pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO5);
						cfg->hwnd = pStatic->GetSafeHwnd();
						break;
					default:
						cfg->hwnd = (void *)-123;
						break;
					}
					//open remote video stream 
					if (g_TTTEngine != NULL && index < 50)
						g_TTTEngine->createRemoteVideo(*cfg);
					OutputDebugStringA("onUserEnableVideo slave create");
					break;
				}
			}
		}
		
		bool master = false;
		if (m_mapParticipants.find(uid) != m_mapParticipants.end())
			master = m_mapParticipants.at(uid).userRole == 1;

		addMixerVideo(uid, mid.c_str(), master);

		//assert(index < 6);
		UserDeviceConfig udc(uid, mid, true);
		udc.hwndindex = index;
		m_mapStreams.insert(std::make_pair(mid, udc));

		m_hWndsforClient[index] = 1;
		//m_LivingMemberArray[index].mHwndindex = index; 
		m_LivingMemberArray[index].mUserID = uid;
		m_LivingMemberArray[index].mDeviceID = mid;

	}
	else
	{
		OutputDebugStringA("onUserEnableVideo enabale  false");
		int index = -1;
		if ( m_mapStreams.find(mid) != m_mapStreams.end())
			index = m_mapStreams.at(mid).hwndindex;// m_mapparticipants[uid].hwndindex;
		
		if (index >= 0 && index < 50)  //原来是1，改成0了，应该把主播也考虑吧？需要检查一下
		{
			delMixerVideo(m_LivingMemberArray[index].mUserID, m_LivingMemberArray[index].mDeviceID.c_str());
			m_LivingMemberArray[index].mUserID = 0;
			m_LivingMemberArray[index].mDeviceID = "";
			m_hWndsforClient[index] = 0;
			if (g_TTTEngine)
				g_TTTEngine->releaseRemoteVideo(m_mapStreams.at(mid).mUserID, m_mapStreams.at(mid).mDeviceID.c_str());
		}

		m_mapStreams.erase(mid);
	}
	delete cfg;
	return 0;
}

LRESULT CDialog2::OnMP4Joined(WPARAM wParam, LPARAM lParam)
{
	uid_ttt uid = wParam;

	char buf[256] = { 0 };
	sprintf(buf, "Mp4 play userid：%d", uid);
	InsertMsgAndEvent("MP4 Play ", buf, buf);
	return 0;
}

LRESULT CDialog2::OnRtcState(WPARAM wParam, LPARAM lParam)
{
	RtcStats  *lpData = (RtcStats *)wParam;
	std::string kbps = "kbps";
	m_csAudioUpload = (std::to_string(lpData->txAudioKBitRate ) + kbps).c_str();
	m_csVideoUpload = (std::to_string(lpData->txVideoKBitRate ) + kbps).c_str();

	UpdateData(false);
	delete lpData;
	lpData = NULL;


	//InsertMsgAndEvent("Event", "Rtc State", "OnRtcState");
	return 0;
}

LRESULT CDialog2::OnRemoteVideoState(WPARAM wParam, LPARAM lParam)
{
	RemoteVideoStats  *lpData = (RemoteVideoStats *)wParam;
	std::string mediaID = lpData->mediaID;
	//uid_ttt uid = lpData->userID;
	int index = -1;
	if ( m_mapStreams.find(mediaID) != m_mapStreams.end())
		index = m_mapStreams.at(mediaID).hwndindex;

	if (index > -1 && index < 5)
	{
		char  buf[256] = { 0 };
		sprintf(buf, "视频：%d kbps", lpData->bitrateKbps);
		switch (index) {
		case 0:
		case 1:
			m_Video0Info = buf;
			break;
		case 2:
			m_Video2Info = buf;
			break;
		case 3:
			m_Video3Info = buf;
			break;
		case 4:
			m_Video4Info = buf;
			break;
		case 5:
			m_Video5Info = buf;
			break;
		}
	}
	UpdateData(false);
	delete lpData;
	lpData = NULL;


	//InsertMsgAndEvent("Event", "Rtc State", "OnRtcState");
	return 0;
}

LRESULT CDialog2::OnUserOffline(WPARAM wParam, LPARAM lParam)
{
	uint64_t uid = lParam;
	int reason = wParam;

	m_mapParticipants.erase(uid);

	m_TotleParticipants--;
	m_csParticipants = std::to_string(m_TotleParticipants).c_str();
	UpdateData(false);

	std::string value = "User offline, id = ";
	value = value + std::to_string(uid);
	//InsertMsgAndEvent("Event", value.c_str(), "OnUserOffline");
	return 0;
}

LRESULT CDialog2::OnUserOnline(WPARAM wParam, LPARAM lParam)
{
	uint64_t uid = lParam;
	int role = wParam;

	UserDeviceConfig udc(uid, "", true);
	udc.userRole = role;
	m_mapParticipants.insert(std::make_pair(uid, udc));

	m_TotleParticipants++;
	m_csParticipants = std::to_string(m_TotleParticipants).c_str();
	UpdateData(false);

	std::string value = "User online, id = ";
	value = value + std::to_string(uid);
	//InsertMsgAndEvent("Event", value.c_str(), "OnUserOnline");
	return 0;
}

void CDialog2::InsertMsgAndEvent(std::string stype, std::string errcode, std::string msg)
{
	int count = m_MsgLst.GetItemCount();

	m_MsgLst.InsertItem(count, stype.c_str());
	m_MsgLst.SetItemText(count, 1, errcode.c_str());
	m_MsgLst.SetItemText(count, 2, msg.c_str());

}

void CDialog2::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialog2::OnBnClickedStaticMainvideo()
{
	// TODO: 在此添加控件通知处理程序代
	m_CurSelVideoIndex = 0;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	
	//InsertMsgAndEvent("Select user", buf, buf);
}


void CDialog2::OnBnDoubleclickedStaticMainvideo()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialog2::OnClickedStaticVideo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CurSelVideoIndex = 1;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	//InsertMsgAndEvent("Select user", buf, buf);
}


void CDialog2::OnClickedStaticVideo2()
{
	m_CurSelVideoIndex = 2;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	//InsertMsgAndEvent("Select user", buf, buf);
}


void CDialog2::OnClickedStaticVideo3()
{
	m_CurSelVideoIndex = 3;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	//InsertMsgAndEvent("Select user", buf, buf);
}


void CDialog2::OnClickedStaticVideo4()
{
	m_CurSelVideoIndex = 4;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	//InsertMsgAndEvent("Select user", buf, buf);
}


void CDialog2::OnClickedStaticVideo5()
{
	m_CurSelVideoIndex = 5;
	m_curSelRemoteParticipant = m_CurSelVideoIndex;
	UpdateData(false);
	char buf[256] = { 0 };
	sprintf(buf, "当前选择用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
	//InsertMsgAndEvent("Select user", buf, buf);
}

void CDialog2::UpdateBtnStatus()
{
	//bool isLiveMaster = g_LocalUser.m_clientRole == 1;
	//bool isGuest = g_LocalUser.m_clientRole == 3;
	m_btnMuteRemoteAudio.EnableWindow(isLiveMaster());
	m_btnKickOut.EnableWindow(isLiveMaster());
	//m_btnPlayMp4.EnableWindow(isLiveMaster());
	m_btnUpgradeClientrole.EnableWindow(isGuest());

	m_btnMuteUnmuteCamera.EnableWindow(isLiveParticipant() || isLiveMaster());
	this->m_btnMuteUnmuteMic.EnableWindow(isLiveParticipant() || isLiveMaster());
	this->m_btnMuteUnmuteSpeaker.EnableWindow(false);
	return;
}

void CDialog2::OnClickedBtnMuteRemoteAudio()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		//this->m_btnMuteRemoteAudio.SetCheck(false);
		bool mute = m_ClientAudioStreamMute[m_CurSelVideoIndex];
		g_TTTEngine->muteRemoteAudioStream(m_LivingMemberArray[m_CurSelVideoIndex].mUserID, !mute);
		m_ClientAudioStreamMute[m_CurSelVideoIndex] = !mute;
		char buf[256] = { 0 };
		sprintf(buf, "设置远端音频流：uid= %d， mute = %d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID, !mute);
		InsertMsgAndEvent("Mute Remote Audio Stream", buf, buf);
	}
}

int CDialog2::getLocalVideoHwndindex()
{
	if (g_LocalUser.m_clientRole == 1)
		return 0;
	else
		return 1;
}


void CDialog2::OnClickedBtnMuteUnmuteCamera()
{
	//static bool  bopened = true;
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		if (m_openedCamera)  //tobe release local video
		{
			
			int index = getLocalVideoHwndindex();
			delMixerVideo(g_LocalUser.m_uid, m_LivingMemberArray[index].mDeviceID.c_str());
			g_TTTEngine->releaseLocalVideo(m_LivingMemberArray[index].mDeviceID.c_str());
			m_openedCamera = false;
		}
		else  // tobe open localvidep
		{
			LocalVideoConfig cfg;
			cfg.userID = g_LocalUser.m_uid;
			cfg.type = VIDEO_CAPTURE_CAMERA;

			switch (g_LocalUser.m_videoProfile)
			{
			case 0:
				cfg.width = 160;
				cfg.height = 112;
				cfg.framerate = 15;
				//config.videoBitRate = 65;
				break;
			case 1:
				cfg.width = 320;
				cfg.height = 176;
				cfg.framerate = 15;
				break;
			case 2:
				cfg.width = 320;
				cfg.height = 240;
				cfg.framerate = 15;
				break;
			case 3:
				cfg.width = 640;
				cfg.height = 352;
				cfg.framerate = 15;
				break;
			case 4:
				cfg.width = 640;
				cfg.height = 480;
				cfg.framerate = 15;
				break;
			case 5:
				cfg.width = 1280;
				cfg.height = 720;
				cfg.framerate = 15;
				break;
			case 6:
				cfg.width = 1920;
				cfg.height = 1080;
				cfg.framerate = 15;
				break;
			default:
				cfg.width = 640;
				cfg.height = 480;
				cfg.framerate = 15;
				break;
			}
			CStatic   *pStatic = NULL;
			int index = 0;
			switch (g_LocalUser.m_clientRole)
			{
			case 1:
				pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MAINVIDEO);
				cfg.viewHwnd = pStatic->GetSafeHwnd();
				index = 0;
				break;
			case 2:
			case 3:
				pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO1);
				cfg.viewHwnd = pStatic->GetSafeHwnd();
				index = 1;
				break;
			}

			UserDeviceConfig udc0(g_LocalUser.m_uid, "", true);
			udc0.userRole = g_LocalUser.m_clientRole;
			m_mapParticipants.insert(std::make_pair(g_LocalUser.m_uid, udc0));

			int count = IVideoDevice::getCount();
			if (count > 0)
				cfg.devIndex = 0;
			//IVideoDevice::getInfo(0, &cfg.devInfo);
			std::string mediaID = "";
			char* id = g_TTTEngine->createLocalVideo(cfg);
			if (id) {
				mediaID = id;
			}
			else
			{
				return;
			}

			addMixerVideo(g_LocalUser.m_uid, mediaID.c_str(), isLiveMaster());

			g_TTTEngine->startPreview(mediaID.c_str());
			UserDeviceConfig udc(g_LocalUser.m_uid, mediaID, true);
			udc.hwndindex = index;
			m_mapStreams.insert(std::make_pair(mediaID, udc));

			m_hWndsforClient[index] = 1;
			//m_LivingMemberArray[index].mHwndindex = index; 
			m_LivingMemberArray[index].mUserID = g_LocalUser.m_uid;
			m_LivingMemberArray[index].mDeviceID = mediaID;
			m_openedCamera = true;
		}

		g_LocalUser.m_bLocalVideoStream = m_openedCamera;
		if (g_LocalUser.m_bLocalVideoStream)
			m_btnMuteUnmuteCamera.SetWindowTextA("关闭摄像头");
		else
			m_btnMuteUnmuteCamera.SetWindowTextA("打开摄像头");
	}
}


void CDialog2::OnClickedBtnMuteUnmuteMic()
{
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		bool mute = !g_LocalUser.m_bLocalAudioStream;
		g_TTTEngine->muteLocalAudioStream(mute);

		g_LocalUser.m_bLocalAudioStream = mute;

		if (g_LocalUser.m_bLocalAudioStream)
			m_btnMuteUnmuteMic.SetWindowTextA("打开麦克风");
		else
			m_btnMuteUnmuteMic.SetWindowTextA("关闭麦克风");
	}
}


void CDialog2::OnClickedBtnMuteUnmuteNetstat()
{
	// TODO: 在此添加控件通知处理程序代码
	bool showed = !g_LocalUser.m_bLocalNetStatShow;
	for (int i = 0; i < 5; i++)
	{
		CStatic   *pStatic = NULL;
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_VIDEO_TEXT1 + i);
		pStatic->ShowWindow(showed);
	}
	g_LocalUser.m_bLocalNetStatShow = showed;
	if (g_LocalUser.m_bLocalNetStatShow)
		m_btnShowNetStat.SetWindowTextA("关闭远端网络显示");
	else
		m_btnShowNetStat.SetWindowTextA("打开远端网络显示");
}


void CDialog2::OnClickedBtnMuteUnmuteSpeaker()
{
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		//g_TTTEngine->muteLocalAudioStream();
	}
}


void CDialog2::OnClickedBtnUpgradeClientrole()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialog2::OnClickedBtnKickOut()
{
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		g_TTTEngine->kickChannelUser(m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
		char buf[256] = { 0 };
		sprintf(buf, "移除当前用户：%d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID);
		InsertMsgAndEvent("kickout", buf, buf);
	}
}


void CDialog2::OnClickedBtnMp4Play()
{
	CString strFile = _T("");
	
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.mp4)|*.jpg|All Files (*.*)|*.*||"), NULL);
		
	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
		{
			//////g_TTTEngine->startPlayMp4(strFile.GetBuffer(), m_ShowMp4.GetSafeHwnd());
		}
	}
}


void CDialog2::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//////g_TTTEngine->setVideoProfile(g_LocalUser.m_videoProfile - 1, false);
}


void CDialog2::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//////g_TTTEngine->setVideoProfile(g_LocalUser.m_videoProfile+1, false);
}


void CDialog2::OnClickedBtnAnchorlink()
{
	static bool linkotherRoom = false;
	static LONGLONG llinkroomid = 0;
	if (g_TTTEngine != NULL && linkotherRoom == false && m_Status == LiveStatus::STATUS_JOINED && isLiveMaster())
	{
		CDialogAnchorLink dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			g_TTTEngine->subscribeOtherChannel(dlg.m_llRoomID);
			llinkroomid = dlg.m_llRoomID;
			linkotherRoom = true;
			//g_TTTEngine->linkOtherAnchor(dlg.m_llRoomID, dlg.m_llUserID);
		}
	}
	else if (linkotherRoom == true)
	{
		g_TTTEngine->unsubscribeOtherChannel(llinkroomid);
		linkotherRoom = false;
		llinkroomid = 0;
	}
}


void CDialog2::OnBnClickedBtnMuteRemoteVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		//this->m_btnMuteRemoteAudio.SetCheck(false);
		bool mute = m_ClientVideoStreamMute[m_CurSelVideoIndex];
		g_TTTEngine->muteRemoteVideoStream(m_LivingMemberArray[m_CurSelVideoIndex].mUserID, m_LivingMemberArray[m_CurSelVideoIndex].mDeviceID.c_str(), !mute);
		m_ClientVideoStreamMute[m_CurSelVideoIndex] = !mute;
		char buf[256] = { 0 };
		sprintf(buf, "设置远端视频流：uid= %d， mute = %d", m_LivingMemberArray[m_CurSelVideoIndex].mUserID, !mute);
		InsertMsgAndEvent("Mute Remote Video Stream", buf, buf);
	}
}


void CDialog2::OnBnClickedBtnSetvolume()
{
	if (g_TTTEngine != NULL && m_Status == LiveStatus::STATUS_JOINED)
	{
		if (m_mixing) {
			g_TTTEngine->stopAudioMixing();
			m_mixing = false;
		}
		else
		{
			TCHAR szFilePath[MAX_PATH + 1] = { 0 };
			GetModuleFileName(NULL, szFilePath, MAX_PATH);
			(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
			CString str_url = szFilePath;  // 例如str_url==e:\program\Debug\

			str_url.Append("\\01.mp3");
            g_TTTEngine->startAudioMixing(str_url.GetBuffer(str_url.GetLength()), false, false, 20);
			m_mixing = true;
		}
	}
}


void CDialog2::OnNMThemeChangedSliderMicvolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}


void CDialog2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(true);
	switch (pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_MICVOLUME:
		break;
	case IDC_SLIDER_MICVOLUME2:
		g_TTTEngine->setSpeakerphoneVolume(m_sliderSpeakerVolume.GetPos());
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDialog2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 125)
	{
		this->KillTimer(125);
		//this->PostMessageA(WM_TIMER,)
		this->OnClose();
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialog2::initLayout()
{
	memset(&m_vclayout, 0, sizeof(VideoCompositingLayout));
	m_vclayout.canvasWidth = 720;
	m_vclayout.canvasHeight = 640;
	strcpy(m_vclayout.backgroundColor, "#FF0000");
	m_vclayout.regionCount = 0;

	//mVideoRegins = 5;
	VideoRegion *r;
	r = &m_vclayout.regions[0];
	r->x = 0;
	r->y = 0;
	r->width = 1;
	r->height = 1;
	r->zOrder = 0;
	r->alpha = 1;

	for (int i = 1; i < 10; i++) {
		r = &m_vclayout.regions[i];
		r->x = ((i - 1) % 3)*0.3;
		r->y = ((i-1)/3)*0.5;
		r->width = 0.3;
		r->height = 0.5;
		r->zOrder = 1;
		r->alpha = 1;
	}
}


BOOL CDialog2::PreTranslateMessage(MSG* pMsg)
{
	if (
		pMsg->message == WM_KEYDOWN
		&& (pMsg->wParam == VK_ESCAPE
			|| pMsg->wParam == VK_CANCEL
			|| pMsg->wParam == VK_RETURN
			))
		return TRUE;


	return CDialog::PreTranslateMessage(pMsg);
}
void CDialog2::OnClickedBtnDataShare()  //屏幕分享
{
	//static bool shared = false;
	//static std::string m_screenMedia = "";
	if (m_sharedata == false)
	{
		LocalVideoConfig cfg;
		cfg.userID = g_LocalUser.m_uid;
		cfg.type = VIDEO_CAPTURE_SCREEN;
		cfg.width = 1280;// 640;
		cfg.height = 720;// 480;
		cfg.screenRect.x = 0;
		cfg.screenRect.y = 0;
		//RECT rect;
		//SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rect, 0);
		cfg.screenRect.w = 1280;// GetSystemMetrics(SM_CXSCREEN);
		cfg.screenRect.h = 720;// GetSystemMetrics(SM_CYSCREEN);
		cfg.framerate = 5;
		CStatic *pStatic = NULL;
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_DATASHARE);
		cfg.viewHwnd = pStatic->GetSafeHwnd();
		//cfg.viewHwnd = NULL;
		char* id = g_TTTEngine->createLocalVideo(cfg);
		if (id) {
			m_screenMedia = id;
		}
		else
		{
			return;
		}
		g_TTTEngine->startPreview(m_screenMedia.c_str());
		m_sharedata = true;
	}
	else 
	{
		g_TTTEngine->stopPreview(m_screenMedia.c_str());
		g_TTTEngine->releaseLocalVideo(m_screenMedia.c_str());
		m_screenMedia = "";
		m_sharedata = false;
	}
	m_screenMedia = m_screenMedia;
}

void CDialog2::addMixerVideo(int64_t userID, const char *mediaID, bool isMaster)
{
	VideoRegion *r = NULL;
	if (isMaster) {
		//自己的userid不一定为0
		//if (m_vclayout.regions[0].userID != 0) {
			//LOGI("Error: please del mix video 0 first\n");
		//	return;
		//}
		r = &m_vclayout.regions[0];
	}
	else {
		for (int i = 1; i <9/* mVideoRegins*/; i++) {
			if (m_vclayout.regions[i].userID == 0) {
				r = &m_vclayout.regions[i];
				break;
			}
		}
	}

	if (r) {
		r->userID = userID;
		strcpy(r->mediaID, mediaID);
		m_vclayout.regionCount = 7;// ++;
		g_TTTEngine->setVideoCompositingLayout(m_vclayout);
		g_TTTEngine->addVideoMixer(userID, mediaID);
	}

}
void CDialog2::delMixerVideo(int64_t userID, const char *mediaID)
{
	for (int i = m_vclayout.regionCount-1; i > -1 ; i--) {
		VideoRegion *r = &m_vclayout.regions[i];
		if ((r->userID == g_LocalUser.m_uid) && (1 == m_vclayout.regionCount)){ //关闭自己的视频，要保留底图，矩形设0，避免停留最有一帧。
			m_vclayout.regions[0].x = 0;
			m_vclayout.regions[0].y = 0;
			m_vclayout.regions[0].height = 0;
			m_vclayout.regions[0].width = 0;
			g_TTTEngine->setVideoCompositingLayout(m_vclayout);
			initLayout();
			r->userID = 0;
		}
		else 
			if (r->userID == userID && !strcmp(r->mediaID, mediaID)) {
				m_vclayout.regionCount = 7;// --;
			g_TTTEngine->delVideoMixer(userID, mediaID);
			r->userID = 0;
			g_TTTEngine->setVideoCompositingLayout(m_vclayout);
			
			break;
		}
	}
}

LRESULT CDialog2::OnMixerVideoCreate(WPARAM wParam, LPARAM lParam)
{
	std::string mid = g_3TEngineEventHandler.getMixerMID();
	CStatic   *pStatic = NULL;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_MP4);
	MixerVideoConfig config;
	config.hwnd = pStatic->GetSafeHwnd();
	strcpy(config.mediaID, mid.c_str());
	g_TTTEngine->createMixerVideo(config);
	//g_TTTEngine->createMixerVideo(config);
	return 0;
}




void CDialog2::OnBnClickedBtn2Camera()
{
	bool bOpen = false;

	bOpen = (m_secondMedia != "");
	if (bOpen)
	{
		bOpen = false;
		delMixerVideo(g_LocalUser.m_uid, m_secondMedia.c_str());

		g_TTTEngine->releaseLocalVideo(m_secondMedia.c_str());
		m_secondMedia = "";
		return;
	}
	int count = IVideoDevice::getCount();
	if (count < 2)
	{
		MessageBox("请至少链接两个摄像头！", "提示", MB_OK);
		return;
	}


	LocalVideoConfig cfg;
	cfg.userID = g_LocalUser.m_uid;
	cfg.type = VIDEO_CAPTURE_CAMERA;
	cfg.encScaleType = VIDEO_SCALE_FIT;
	cfg.renderScaleType = VIDEO_SCALE_FIT;

		cfg.width = 640;
		cfg.height = 480;
		cfg.framerate = 15;

	CStatic   *pStatic = NULL;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_SEC_CAMERA);
	cfg.viewHwnd = pStatic->GetSafeHwnd();
		//cfg.viewHwnd = NULL;
	cfg.devIndex = 1;

	char* id = g_TTTEngine->createLocalVideo(cfg);
	if (id) {
		m_secondMedia = id;
	}
	else
	{
		return;
	}

	g_TTTEngine->startPreview(m_secondMedia.c_str());
	addMixerVideo(g_LocalUser.m_uid, m_secondMedia.c_str(), false);
	bOpen = true;
}
