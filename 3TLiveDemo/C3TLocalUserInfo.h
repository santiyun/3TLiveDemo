#pragma once

#include "common.h"

class C3TLocalUserInfo
{
public:
	C3TLocalUserInfo();
	virtual ~C3TLocalUserInfo();

	CHANNEL_PROFILE_TYPE  m_channelProfile;
	bool m_enableVideo;
	bool m_enableAudio;
	CLIENT_ROLE_TYPE  m_clientRole;
	rid_ttt  m_roomID;
	void* m_hWnd;
	uid_ttt m_uid;
	int m_renderMode;
	std::string m_channelKey; 
	std::string m_pushUrl;
	int m_videoProfile;
	bool m_bUserHighQualityAudio;
    bool m_bEnable_hwaccel;
    bool m_bEnable_mirror;
	int m_bitrate;
	int m_framerate;

	HWND m_cbMsgHandler;

	std::wstring m_wsDeviceName;


	bool	m_bLocalVideoStream;
	bool	m_bLocalAudioStream;
	bool	m_bLocalNetStatShow;
	bool	m_bLocalAudioDevice;

	VideoDeviceInfo m_vDeviceArray[10];
	int		m_vDeviceCount;  //当前选择的设备总数

	std::string m_sAddress;
	int m_iPort;
	std::string m_sAppID;

	int m_pushSolution;
	int m_pushAudioSolution;

};

