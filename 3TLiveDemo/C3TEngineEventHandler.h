#pragma once
#include "TTTRtcEngine.h"
#include "TTTstruct.h"

using namespace TTTRtc;

class C3TEngineEventHandler :
	public IRtcEngineEventHandler
{
public:
	C3TEngineEventHandler();
	virtual ~C3TEngineEventHandler();

	void SetMsgReceiver(HWND hWnd);
	std::string  getMixerMID() { return  mid; }
	void resetMixerMID() { mid = ""; }


	virtual void onJoinChannel(int64_t channel, int64_t userID, RtcErrorCode result);
	virtual void onError(int err, const char* msg);
	virtual void onWarning(int warn, const char* msg);
	virtual void onAudioVolumeIndication(AudioLevelInfo* info);

	virtual void onLeaveChannel(RtcErrorCode reason);
	virtual void onRtcStats(const RtcStats& stats);

	//lost these call back func
	virtual void onLastmileQuality(int quality);
	virtual void OnChatMessageSent(const char* sSeqID, int error);
	virtual void OnChatMessageRecived(long nSrcUserID, int type, const char* sSeqID, const char* strData);
	//virtual void onRemoteVideoDecoded(long long uid, VideoFrame_TTT& mVideoFrame);
	//virtual void onRemoteAudioDecoded(long long uid, AudioFrame_TTT& mAudioFrame);
	//virtual void onMp4Joined(uid_ttt uid);
	//virtual void onMp4Offline(uid_ttt uid);
	virtual void onOtherAnchorLink(long long roomID, long long operUserID)override;
	virtual void onOtherAnchorLinked(long long roomID, long long operUserID, const char* operDevID, int nError) override;
	virtual void onOtherAnchorUnlink(long long roomID, long long operUserID, int nError)override;
	virtual void onOtherAnchorUnLinked(long long roomID, long long operUserID)override;
	//virtual void OnUserH264Push(const char* data, int len, const char* devId, long long ts, int width, int height, VideoFrameType_TTT frameType);

	//virtual void onNetworkQuality(int quality);
	//virtual void onFirstLocalVideoFrame(int width, int height, int elapsed);
	//virtual void onFirstRemoteVideoDecoded(uid_ttt uid, int width, int height, int elapsed);
	//virtual void onFirstRemoteVideoFrame(uid_ttt uid, int width, int height, int elapsed);
	virtual void onUserJoined(int64_t userID, CLIENT_ROLE_TYPE role);
	//virtual void onUserJoined(uid_ttt uid, const char* devId, int elapsed);
	virtual void onUserOffline(int64_t userID, RtcErrorCode reason);

	virtual void onLocalVideoStats(const LocalVideoStats& stats);
	virtual void onRemoteVideoStats(const RemoteVideoStats& stats);
	virtual void onRemoteAudioStats(const RemoteAudioStats& stats);
	virtual void onConnectionLost();

	virtual void onUserEnableVideo(int64_t userID, const char *mediaID, int mediaType, bool enabled) override;

	//virtual void OnUserPcmPush(char *data, int samples_per_channel, int samplerate, int channels, int channelid);
	//virtual void OnUserYuvPush(long long uid, unsigned char *YUV, unsigned int width, unsigned int height);
	virtual void onMixerVideoCreate(const char *mediaID);
	virtual void onSetSEI(const char* SEI);
	virtual void onRTMPsenderror(const char * err);
	virtual void onAudioEffectFinished(int id);
	virtual void onRequestChannelKey() override;


	

private:
	HWND		m_hMainWnd;
	std::string mid;
};

