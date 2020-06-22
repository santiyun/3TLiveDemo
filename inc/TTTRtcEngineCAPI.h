#ifndef __TTT_RTCENGINE_CAPI_H__
#define __TTT_RTCENGINE_CAPI_H__
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "TTTBase.h"
#include "TTTstruct.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void(*onJoinChannel)(int64_t channel, int64_t userID, RtcErrorCode result);
    void(*onLeaveChannel)(RtcErrorCode reason);
    void(*onError)(int32_t err, const char* msg);
    void(*onFirstLocalVideoFrame)(const char *mediaID, int32_t width, int32_t height);
    void(*onFirstRemoteVideoFrame)(const char *mediaID, int32_t width, int32_t height);
    void(*onRtcStats)(const RtcStats* stats);
    void(*onLocalVideoStats)(const LocalVideoStats* stats);
    void(*onRemoteVideoStats)(const RemoteVideoStats* stats);
    void(*onUserJoined)(int64_t userID, CLIENT_ROLE_TYPE role);
    void(*onUserOffline)(int64_t userID, RtcErrorCode reason);
    void(*onUserEnableVideo)(int64_t userID, const char *mediaID, int mediaType, int32_t enabled);
    void(*onMixerVideoCreate)(const char *mediaID, const char* mediaURL);
	void(*onMixerVideoRemove)(const char *mediaID, const char* mediaURL);
    void(*onAudioVolumeIndication)(int64_t nUserID, int audioLevel, int audioLevelFullRange);
	void(*onConnectionLost)();
	void(*onSetSEI)(const char* SEI);
	void(*onRTMPsenderror)(const char *err);

	void(*onAudioMixingFinished)();
	void(*onPlayerFinished)(int32_t playerID);
	void(*onRtmpStatusChange)(int64_t roomID, const char* rtmpURL, int32_t status);
	void(*onRemoteAudioStats)(const RemoteAudioStats* stats);
	void(*onRequestChannelKey)();
	void(*onUserMuteAudio)(int64_t userID,int32_t enabled);
	void(*onDisconnected)(const char* uuid);
	void(*OnConnectSuccess)();
}TTTRtcEngineCallback;

typedef enum {
    OB_FRAME_TYPE_YUV420 = 0,
    OB_FRAME_TYPE_H264 = 10,
    OB_FRAME_TYPE_FORCE_DWORD = 0x7fffffff,
}OB_VIDEO_FRAME_TYPE;

typedef struct {
    OB_VIDEO_FRAME_TYPE fmt;   //FRAME_TYPE_H264
    uint8_t *data;
    int32_t dlen;
    int32_t width;
    int32_t height;
    int64_t pts;
}OB_VideoFrame;

typedef struct {
    /* local video */
    void(*onCaptureVideoFrame)(void* userdata, OB_VideoFrame* frame); //YUV420
    void(*onEncodeVideoFrame)(void* userdata, OB_VideoFrame* frame);

    /* remoute video */
    void(*onReceiveVideoFrame)(void* userdata, OB_VideoFrame* frame);
    void(*onRenderVideoFrame)(void* userdata, OB_VideoFrame* frame);
}TTTRtcVideoObserver;

typedef struct {
	uint8_t* data;              //PCM 16bit little endian
	int32_t length;             //samples_per_channel * num_channels * 2
	int32_t num_channels;
	int32_t samples_per_channel;  // 目前仅支持480的倍数
	int32_t sample_rate_hz;     //16000 32000 48000  (暂不支持44100采样率)
	int64_t timestamp;
}OB_AudioFrame;

typedef struct {
	/* 本地麦克风采集的数据 */
	void(*onRecordAudioFrame)(void* userData, OB_AudioFrame* frame);

	/* 单路远端用户的数据 */
	void(*onPlaybackAudioFrame)(void* userData, int64_t userID, OB_AudioFrame* frame);

	/* 所有远端用户混音后的数据 */
	void(*onPlaybackMixedAudioFrame)(void* userData, OB_AudioFrame* frame);

	/* 本地和远端混音后的数据 */
	void(*onMixedAudioFrame)(void* userData, OB_AudioFrame* frame);
}TTTRtcAudioObserver;

TTT_API int32_t TTTRtc_VDeviceGetCount();
TTT_API int32_t TTTRtc_VDeviceGetInfo(int32_t index, VideoDeviceInfo* outInfo);
TTT_API int32_t TTTRtc_VDeviceGetInfoFromPath(const char *devicePath, VideoDeviceInfo* outInfo);

TTT_API int32_t TTTRtcEngine_Initialize(TTTRtcEngineCallback *cbk, const char* workPath, RTC_SDK_LOG_LEVEL logLevel);
TTT_API void TTTRtcEngine_Release();
TTT_API const char* TTTRtcEngine_GetVersion();
TTT_API int32_t TTTRtcEngine_EnableVideo();
TTT_API int32_t TTTRtcEngine_DisableVideo();
TTT_API int32_t TTTRtcEngine_SetAppID(const char *appID);
TTT_API int32_t TTTRtcEngine_SetChannelProfile(CHANNEL_PROFILE_TYPE profile);
TTT_API int32_t TTTRtcEngine_SetClientRole(CLIENT_ROLE_TYPE role, const char* permissionKey);
TTT_API int32_t TTTRtcEngine_SetServerAddr(const char* addr, uint16_t port);
TTT_API int32_t TTTRtcEngine_ConfigPublisher(const PublisherConfig* config);
TTT_API int32_t TTTRtcEngine_JoinChannel(int64_t channelID, const char *channelName, int64_t optionalUid);
TTT_API int32_t TTTRtcEngine_LeaveChannel();
TTT_API int32_t TTTRtcEngine_ApplySpeak();

TTT_API void TTTRtcEngine_StartLocalVideoTest(LocalVideoConfig* config);
TTT_API void TTTRtcEngine_StopLocalVideoTest();
TTT_API char* TTTRtcEngine_CreateLocalVideo(LocalVideoConfig* config);
TTT_API void TTTRtcEngine_ReleaseLocalVideo(const char* mediaID);
TTT_API void TTTRtcEngine_ReconfigLocalVideo(const char *mediaID, LocalVideoConfig* config);
TTT_API int32_t TTTRtcEngine_StartPreview(const char *mediaID);
TTT_API int32_t TTTRtcEngine_StopPreview(const char *mediaID);

TTT_API int32_t TTTRtcEngine_CreateRemoteVideo(RemoteVideoConfig* config);
TTT_API void TTTRtcEngine_ReleaseRemoteVideo(uint64_t userID, const char* mediaID);
TTT_API void TTTRtcEngine_ReleaseAllRemoteVideo();

TTT_API int32_t TTTRtcEngine_CreateMixerVideo(MixerVideoConfig* config);
TTT_API void TTTRtcEngine_ReleaseMixerVideo(const char* mediaID);

TTT_API int TTTRtcEngine_RegisterVideoFrameObserver(const char* mediaID, TTTRtcVideoObserver* observer, void* userdata);
TTT_API void TTTRtcEngine_UnregisterVideoFrameObserver(const char* mediaID);

TTT_API int TTTRtcEngine_RegisterAudioFrameObserver( TTTRtcAudioObserver* observer, void* userdata);
TTT_API void TTTRtcEngine_UnregisterAudioFrameObserver(TTTRtcAudioObserver* observer, void* userdata);

TTT_API void TTTRtcEngine_addPublishStreamUrl(const char* streamUrl);
TTT_API void TTTRtcEngine_removePublishStreamUrl(const char* streamUrl);
TTT_API void TTTRtcEngine_AddVideoMixer(int64_t nUserID, const char *mediaID, const char* streamUrl);
TTT_API void TTTRtcEngine_DelVideoMixer(int64_t nUserID, const char *mediaID, const char* streamUrl);
TTT_API void TTTRtcEngine_AddAudioMixer(int64_t nUserID, const char* streamUrl);
TTT_API void TTTRtcEngine_DelAudioMixer(int64_t nUserID, const char* streamUrl);
TTT_API void TTTRtcEngine_SetVideoMixerBackgroundImgUrl(const char *url, const char* streamUrl);

TTT_API void TTTRtcEngine_SetVideoCompositingLayout(const VideoCompositingLayout* layout, const char* streamUrl);
TTT_API void TTTRtcEngine_SetVideoCompositingLayoutJson(const char* sei, const char* seiExt, const char* streamUrl);
TTT_API int TTTRtcEngine_setVideoMixerParams(int32_t bitrate, int32_t fps, int32_t width, int32_t height, int32_t encodeMode);
TTT_API int	TTTRtcEngine_setAudioMixerParams(int bitrate, int samplerate, int channels);
TTT_API int	TTTRtcEngine_SetPreferAudioCodec(int audioCodec, int bitrate, int channels);

TTT_API int TTTRtcEngine_SetSpeakerphoneVolume(int volume);
TTT_API int TTTRtcEngine_GetSpeakerphoneVolume(int* volume);
TTT_API int TTTRtcEngine_SetRecordDevice(int index);
TTT_API int TTTRtcEngine_SetPlayDevice(int index) ;
TTT_API int TTTRtcEngine_SetRecordVolume(int volume);
TTT_API int TTTRtcEngine_GetRecordVolume(int* volume);
TTT_API int TTTRtcEngine_GetNumOfPlayoutDevices();
TTT_API int TTTRtcEngine_GetNumOfRecordingDevices();
TTT_API int TTTRtcEngine_GetPlayoutDeviceName(int index, char deviceName[DEVICE_NAME_LENGTH], char devicePath[DEVICE_NAME_LENGTH]);
TTT_API int TTTRtcEngine_GetRecordingDeviceName(int index, char deviceName[DEVICE_NAME_LENGTH], char devicePath[DEVICE_NAME_LENGTH]);
TTT_API int TTTRtcEngine_EnableAudioVolumeIndication(int interval, int smooth);
TTT_API int TTTRtcEngine_StartAudioMixing(AudioMixingConfig* config);
TTT_API int TTTRtcEngine_StopAudioMixing();
TTT_API int TTTRtcEngine_PauseAudioMixing();
TTT_API int TTTRtcEngine_ResumeAudioMixing();
TTT_API int TTTRtcEngine_AdjustAudioMixingVolume(int volume);
TTT_API int TTTRtcEngine_GetAudioMixingDuration();
TTT_API int TTTRtcEngine_GetAudioMixingCurrentPosition();
TTT_API int TTTRtcEngine_SetAudioMixingPosition(int pos_ms);
TTT_API int TTTRtcEngine_SetHighQualityAudioParameters(int enable);
TTT_API int TTTRtcEngine_SendChatMessage(int64_t nDstUserID, int type, const char* sData);
TTT_API int TTTRtcEngine_StartRecordingDeviceTest(int indicationInterval);
TTT_API int TTTRtcEngine_StopRecordingDeviceTest();
TTT_API int TTTRtcEngine_StartPlaybackDeviceTest(const char* testAudioFilePath);
TTT_API int TTTRtcEngine_StopPlaybackDeviceTest();
TTT_API int TTTRtcEngine_AdjustLocalAudioVolume(int volume);      // 调节信号强度,原始为100 
TTT_API int TTTRtcEngine_AdjustRemoteAudioVolume(int64_t userID, int volume);
TTT_API int TTTRtcEngine_AdjustRemoteAudioMixedVolume(int volume);

TTT_API int TTTRtcEngine_EnableEarphoneMonitor(int enable);
TTT_API int TTTRtcEngine_AdjustEarphoneMonitorVolume(int volume);

TTT_API void TTTRtcEngine_LinkOtherAnchor(int64_t sessionId, int64_t userId);
TTT_API void TTTRtcEngine_UnlinkOtherAnchor(int64_t sessionId, int64_t userId, const char* devId);
TTT_API void TTTRtcEngine_subscribeOtherChannel(int64_t sessionId);
TTT_API void TTTRtcEngine_unsubscribeOtherChannel(int64_t sessionId);

TTT_API int TTTRtcEngine_MuteRemoteSpeaking(int64_t userID, int mute);
TTT_API int TTTRtcEngine_MuteLocalAudioStream(int mute);
TTT_API int TTTRtcEngine_MuteRemoteAudioStream(int64_t userID, int mute);
TTT_API int TTTRtcEngine_MuteAllRemoteAudioStreams(int mute);
TTT_API int TTTRtcEngine_StartPushScreenCaptureRect(int iOffsetX, int iOffsetY, int iWidth, int iHeight, AV_PUSH_TYPE type, const char* mp4FilePath, const char *mCDNPullAddress);
TTT_API int TTTRtcEngine_StopPushScreenCapture();
TTT_API int TTTRtcEngine_EnableVideoMixer(const char* mediaID, int enable);
TTT_API int TTTRtcEngine_StartPushLocalVideo(LocalVideoConfig* config, AV_PUSH_TYPE type, const char* mp4FilePath, const char *mCDNPullAddress);
TTT_API int TTTRtcEngine_StopPushLocalVideo();

TTT_API void TTTRtcEngine_InputVideoFrame(const char *mediaID, TVideoFrame *frame);

TTT_API int32_t TTTRtcEngine_PlayerCreate(int64_t userID);
TTT_API int32_t TTTRtcEngine_PlayerRelease(int playerID);
TTT_API int32_t TTTRtcEngine_PlayerOpen(int playerID, const char* url, RtcPlayerConfig* config);
TTT_API int32_t TTTRtcEngine_PlayerClose(int playerID);
TTT_API int32_t TTTRtcEngine_PlayerStart(int playerID, int loopCount);
TTT_API int32_t TTTRtcEngine_PlayerStop(int playerID);
TTT_API int32_t TTTRtcEngine_PlayerSeek(int playerID, uint32_t pos_ms);
TTT_API int32_t TTTRtcEngine_PlayerAdjustPlayoutVolume(int playerID, int volume);
TTT_API int32_t TTTRtcEngine_PlayerAdjustPublishVolume(int playerID, int volume);
TTT_API int32_t TTTRtcEngine_PlayerPause(int playerID);
TTT_API int32_t TTTRtcEngine_PlayerResume(int playerID);
TTT_API int32_t TTTRtcEngine_GetVideoID(int playerID, char id[128]);
TTT_API int32_t TTTRtcEngine_GetAudioID(int playerID, int* id);
TTT_API int32_t TTTRtcEngine_GetDuration(int playerID, int* duration);

TTT_API int32_t TTTRtcEngine_AddVideoWatermark(const RtcImage* 	watermark);
TTT_API int32_t TTTRtcEngine_ClearVideoWatermarks();

#ifdef __cplusplus
}
#endif

#endif
