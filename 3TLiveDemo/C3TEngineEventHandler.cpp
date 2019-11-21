#include "stdafx.h"
#include "C3TEngineEventHandler.h"
#include "Common.h"

C3TEngineEventHandler::C3TEngineEventHandler()
{

}


C3TEngineEventHandler::~C3TEngineEventHandler()
{
}


void C3TEngineEventHandler::SetMsgReceiver(HWND hWnd)
{
	m_hMainWnd = hWnd;
}

//void C3TEngineEventHandler::OnUserPcmPush(char *data, int samples_per_channel, int samplerate, int channels, int channelid) 
//{
//	//static FILE *audio_fp_pcm2 = fopen("d:\\bbb.pcm", "wb");
//	//fwrite(data, samples_per_channel * channels, 1, audio_fp_pcm2);
//
//}
//void C3TEngineEventHandler::OnUserYuvPush(long long uid, unsigned char *YUV, unsigned int width, unsigned int height)
//{
//
//
//}
void C3TEngineEventHandler::onJoinChannel(int64_t channel, int64_t userID, RtcErrorCode result)
{
	//LPAGE_JOINCHANNEL_SUCCESS lpData = new AGE_JOINCHANNEL_SUCCESS;

	//int nChannelLen = strlen(channel) + 1;
	//lpData->channel = new char[nChannelLen];
	//lpData->uid = uid;
	//lpData->elapsed = 1;

	//strcpy_s(lpData->channel, nChannelLen, channel);

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_JOINCHANNELSUCCESS, result, userID);
}

void C3TEngineEventHandler::onWarning(int warn, const char* msg)
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_ERROR, 0, warn);
}

void C3TEngineEventHandler::onError(int err, const char* msg)
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_ERROR, 0, err);

}

void C3TEngineEventHandler::onMixerVideoCreate(const char *mediaID)
{
	mid = mediaID;
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_MIXERVIDEO_CREATE, 0, 0);
	return;
}


void C3TEngineEventHandler::onAudioVolumeIndication(AudioLevelInfo* info)
{
	//LPAGE_AUDIO_VOLUME_INDICATION lpData = new AGE_AUDIO_VOLUME_INDICATION;

	////lpData->speakers = new AudioVolumeInfo[speakerNumber];
	////memcpy(lpData->speakers, speakers, speakerNumber*sizeof(AudioVolumeInfo));
	//lpData->userid = nUserID;
	//lpData->speakerNumber = 1;
	//lpData->totalVolume = audioLevel;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_AUDIO_VOLUME_REPORT, (WPARAM)0, info->local_level);

}
void C3TEngineEventHandler::onLeaveChannel(RtcErrorCode reason)
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_LEAVECHANNEL, 0, reason);
}

void C3TEngineEventHandler::onRtcStats(const RtcStats& stats)
{
	RtcStats *lpdata = new RtcStats;


	memcpy(lpdata, &stats, sizeof(RtcStats));

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_RTCSTATE_REP, (WPARAM)lpdata, 0);
}


//void C3TEngineEventHandler::onNetworkQuality(int quality)
//{
//	//LPAGE_NETWORK_QUALITY lpData = new AGE_NETWORK_QUALITY;
//
//	//lpData->quality = quality;
//
//	//if (m_hMainWnd != NULL)
//	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_NETWORK_QUALITY), (WPARAM)lpData, 0);
//
//}

//void C3TEngineEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed)
//{
//	//LPAGE_FIRST_LOCAL_VIDEO_FRAME lpData = new AGE_FIRST_LOCAL_VIDEO_FRAME;
//
//	//lpData->width = width;
//	//lpData->height = height;
//	//lpData->elapsed = elapsed;
//
//	//if (m_hMainWnd != NULL)
//	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), (WPARAM)lpData, 0);
//
//}
//
//void C3TEngineEventHandler::onFirstRemoteVideoDecoded(uid_ttt uid, int width, int height, int elapsed)
//{
//	//LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = new AGE_FIRST_REMOTE_VIDEO_DECODED;
//
//	//lpData->uid = uid;
//	//lpData->width = width;
//	//lpData->height = height;
//	//lpData->elapsed = elapsed;
//
//	//if (m_hMainWnd != NULL)
//	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), (WPARAM)lpData, 0);
//
//}
//
//void C3TEngineEventHandler::onFirstRemoteVideoFrame(uid_ttt uid, int width, int height, int elapsed)
//{
//	//LPAGE_FIRST_REMOTE_VIDEO_FRAME lpData = new AGE_FIRST_REMOTE_VIDEO_FRAME;
//
//	//lpData->uid = uid;
//	//lpData->width = width;
//	//lpData->height = height;
//	//lpData->elapsed = elapsed;
//
//	//if (m_hMainWnd != NULL)
//	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_REMOTE_VIDEO_FRAME), (WPARAM)lpData, 0);
//
//}

//void C3TEngineEventHandler::onUserJoined(uid_ttt uid, const char* devId, int elapsed)
//{
	//LPAGE_USER_JOINED lpData = new AGE_USER_JOINED;

	//int nMsgLen;
	//if (devId != NULL) {
	//	nMsgLen = strlen(devId) + 1;
	//	lpData->devId = new char[nMsgLen];
	//	strcpy_s(lpData->devId, nMsgLen, devId);
	//}
	//else
	//	lpData->devId = NULL;
	//uid = 1000000000 * m_nSecondaryIndex + uid;
	//m_nSecondaryIndex++;
	//lpData->uid = uid;
	//lpData->elapsed = elapsed;
	//lpData->height = 320;
	//lpData->width = 240;

	//if (m_hMainWnd != NULL)
	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_JOINED), (WPARAM)lpData, 0);

//}
void C3TEngineEventHandler::onUserJoined(int64_t userID, CLIENT_ROLE_TYPE role)
{
	//LPAGE_USER_JOINED lpData = new AGE_USER_JOINED;
	//std::string devid = "";
	//lpData->devId = NULL;
	//lpData->uid = uid;
	//lpData->elapsed = elapsed;
	//lpData->height = 320;
	//lpData->width = 240;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_USERJOINED, role, userID);
	OutputDebugStringA("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  onUserJoined   1");

}

void C3TEngineEventHandler::onUserOffline(int64_t userID, RtcErrorCode reason)
{
	//LPAGE_USER_OFFLINE lpData = new AGE_USER_OFFLINE;

	//lpData->uid = uid;
	//lpData->reason = reason;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_USEROFFLIEN, reason, userID);
	OutputDebugStringA("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  onUserOffline   1");
}

void C3TEngineEventHandler::onLocalVideoStats(const LocalVideoStats& stats)
{
	//LPAGE_LOCAL_VIDEO_STAT lpData = new AGE_LOCAL_VIDEO_STAT;

	//lpData->sentBitrate = stats.sentBitrate;
	//lpData->sentFrameRate = stats.sentFrameRate;

	//if (m_hMainWnd != NULL)
	//	::PostMessage(m_hMainWnd, WM_MSGID(EID_LOCAL_VIDEO_STAT), (WPARAM)lpData, 0);

}

void C3TEngineEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats)
{
	RemoteVideoStats *lpdata = new RemoteVideoStats;


	memcpy(lpdata, &stats, sizeof(RemoteVideoStats));

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_REMOTE_VIDEO_STATS, (WPARAM)lpdata, 0);
}

void C3TEngineEventHandler::onRemoteAudioStats(const RemoteAudioStats & stats)
{
	RemoteAudioStats *lpdata = new RemoteAudioStats;

	memcpy(lpdata, &stats, sizeof(RemoteAudioStats));

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_REMOTE_AUDIO_STATS, (WPARAM)lpdata, 0);
}

void C3TEngineEventHandler::onConnectionLost()
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_CONNECTLOST, 0, 0);
}

void C3TEngineEventHandler::onUserEnableVideo(int64_t userID, const char *mediaID, int mediaType, bool enabled)
{
	//TODO   user video enable tatus change 
	std::string mid = mediaID;
	RemoteVideoConfig* cfg = new RemoteVideoConfig;
	memset(cfg, 0, sizeof(RemoteVideoConfig));
	cfg->userID = userID;
	//memset(cfg->mediaID, 0, 128);
	memcpy(cfg->mediaID, mediaID, mid.length());
	OutputDebugStringA("On onUserEnableVideo ddd/\n");


	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_REMOTE_USER_VIDEO_ENABLE, (WPARAM)cfg, enabled);
}

void C3TEngineEventHandler::onLastmileQuality(int quality)
{
	return;
}


void C3TEngineEventHandler::OnChatMessageSent(const char* sSeqID, int error)
{
	return;
}

void C3TEngineEventHandler::OnChatMessageRecived(long nSrcUserID, int type, const char* sSeqID, const char* strData)
{
	return;
}
//void C3TEngineEventHandler::onRemoteVideoDecoded(long long uid, VideoFrame_TTT& mVideoFrame)
//{
//
//}
//void C3TEngineEventHandler::onRemoteAudioDecoded(long long uid, AudioFrame_TTT& mAudioFrame)
//{
//
//}
//void C3TEngineEventHandler::onMp4Joined(uid_ttt uid)
//{
//	//TODO   user video enable tatus change 
//	if (m_hMainWnd != NULL)
//		::PostMessage(m_hMainWnd, WM_ON_MP4_JOINED, uid, 0);
//}
//void C3TEngineEventHandler::onMp4Offline(uid_ttt uid)
//{
//
//}
void C3TEngineEventHandler::onOtherAnchorLink(long long roomID, long long operUserID)
{


}

void C3TEngineEventHandler::onOtherAnchorLinked(long long roomID, long long operUserID, const char* operDevID, int nError)
{

}
void C3TEngineEventHandler::onOtherAnchorUnlink(long long roomID, long long operUserID, int nError)
{

}
void C3TEngineEventHandler::onOtherAnchorUnLinked(long long roomID, long long operUserID)
{
}

void C3TEngineEventHandler::onSetSEI(const char* SEI)
{
	//if (m_hMainWnd != NULL)
	//	::PostMessage(m_hMainWnd, WM_ON_REMOTE_VIDEO_STATS, (WPARAM)0, 0);
}
void C3TEngineEventHandler::onRTMPsenderror(const char * err)
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_RTMP_SENDERROR, (WPARAM)0, 0);
}
void C3TEngineEventHandler::onAudioEffectFinished(int id)
{
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_ON_EFFECTFINISHED, (WPARAM)id, 0);
	//
}
void C3TEngineEventHandler::onRequestChannelKey()
{
	//
	{
		char szDbg[128];
		sprintf_s(szDbg, "@@@ 2019-10-25  onRequestChannelKey\n");
		OutputDebugStringA(szDbg);
	}
}
//void C3TEngineEventHandler::OnUserH264Push(const char* data, int len, const char* devId, long long ts, int width, int height, VideoFrameType_TTT frameType)
//{
//
//}
