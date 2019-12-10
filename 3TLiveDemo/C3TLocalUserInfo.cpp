#include "stdafx.h"
#include "C3TLocalUserInfo.h"


C3TLocalUserInfo::C3TLocalUserInfo()
{
	m_channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	m_enableVideo = true;
	m_enableAudio =  true;
	m_clientRole = CLIENT_ROLE_BROADCASTER;
	m_roomID = "987987";
	m_hWnd = NULL;
	srand(time(0));
	m_uid = rand();
	m_renderMode = 1;//RENDER_MODE_TYPE_TTT::RENDER_MODE_FIT_TTT;
	m_channelKey = "Omygode!";
	m_pushUrl = "rtmp://push.3ttech.cn/sdk/12321";
	m_videoProfile = 5;// VIDEO_PROFILE_120P;
	m_bUserHighQualityAudio = true;
	m_bitrate = 4000;
	m_framerate = 15;

	m_cbMsgHandler = NULL;
	
	m_bLocalVideoStream = false;
	m_bLocalAudioStream = false;
	m_bLocalNetStatShow = true;
	m_bLocalAudioDevice = false;
	memset(m_vDeviceArray,0,sizeof(VideoDeviceInfo)*10);
	m_vDeviceCount = 0;  //当前选择的设备总数


	m_sAddress = "";
	m_iPort = 0;// 11000; //11000
	m_sAppID = 请到官网申请APPID;
	
	m_pushSolution = -1;
	m_pushAudioSolution = -1;
}


C3TLocalUserInfo::~C3TLocalUserInfo()
{
}
