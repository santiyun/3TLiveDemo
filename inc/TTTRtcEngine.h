#ifndef __TTT_RTCENGINE_H__
#define __TTT_RTCENGINE_H__

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "TTTBase.h"
#include "TTTstruct.h"

#include <iostream>

namespace TTTRtc {
	/* TODO: IAudioDevice */

		/**
		* 收到其他房间用户连麦请求
		* @param roomID  请求连麦的房间号
		* @param operUserID 请求连麦的用户ID
		*/

	class TTT_API IVideoDevice {
	public:
		/**
		* 获取视频数量
		* @return 返回实际视频设备数量
		*/
		static int getCount(void);

		/**
		* 获取视频设备信息
		* @param [in]  index      设备序号
		* @param [out] outInfo    输出设备信息
		* @return 0：成功， 其他：失败
		*/
		static int getInfo(int index, VideoDeviceInfo* outInfo);

		/**
		* 获取视频设备信息
		* @param [in]  devicePath 设备devicePath
		* @param [out] outInfo    输出设备信息
		* @return 0：成功， 其他：失败
		*/
		static int getInfo(const char *devicePath, VideoDeviceInfo* outInfo);
	};

	class TTT_API IRtcPlayerEventHandler
	{
	public:
		virtual ~IRtcPlayerEventHandler() {};
		virtual void onPlayFinished() {};
		virtual void onPlayPosition(uint64_t curPosMS) {};
	};
	class TTT_API IRtcPlayer
	{
	public:
		virtual ~IRtcPlayer() {}
		virtual int setEventHandler(IRtcPlayerEventHandler *event) = 0;
		virtual int open(const char* url, RtcPlayerConfig* config) = 0;
		virtual int close() = 0;
		virtual int start(int loop_count) = 0;
		virtual int stop() = 0;
		virtual int pause() = 0;
		virtual int resume() = 0;
		virtual int adjustPlayoutVolume(int volume) = 0;//本地播放的音量
		virtual int getPlayoutVolume() = 0;
		virtual int adjustPublishVolume(int volume) = 0;//提供给远端的音量
		virtual int getPublishVolume() = 0;
		virtual int adjustVolume(int volume) = 0;//同时修改本地和远端音量
		virtual int duration() = 0; //length in ms
		virtual int position() = 0; //current position in ms
		virtual int seek(uint32_t seek_ms) = 0;

		virtual int audioID() = 0;
		virtual const char* mediaID() = 0;
	};

	/**
	* 主体SDK的回调接收基类，用户可自定义类继承此类，实现SDK回调的接收
	*/
	class IRtcEngineEventHandler
	{
	public:
		virtual ~IRtcEngineEventHandler() {}

		/**
		* 加入频道回调
		* @param [in] channel       频道ID
		* @param [in] userID        用户ID
		* @param [in] result        加入频道结果
		*/
		virtual void onJoinChannel(int64_t channel, int64_t userID, RtcErrorCode result) {
			(void)channel;
			(void)userID;
			(void)result;
		}

		/**
		* 退出频道回调
		* @param [in] result        退出频道结果
		*/
		virtual void onLeaveChannel(RtcErrorCode reason) {
			(void)reason;
		}

		/**
		* 错误消息回调
		* @param [in] err       消息类型
		* @param [in] msg       消息内容
		*/
		virtual void onError(int err, const char* msg) {
			(void)err;
			(void)msg;
		}

		/**
		* 警告消息回调
		* @param [in] warn      消息类型
		* @param [in] msg       消息内容
		*/
		virtual void onWarning(int warn, const char* msg) {
			(void)warn;
			(void)msg;
		}

		/**
		* 接收到本地第一帧视频时回调
		* @param [in] mediaID      视频流的唯一标识
		* @param [in] width	       视频宽度
		* @param [in] height	   视频高度
		*/
		virtual void onFirstLocalVideoFrame(const char *mediaID, int width, int height) {
			(void)mediaID;
			(void)width;
			(void)height;
		}
		/**
		* 接收到远端第一帧视频时回调
		* @param [in] mediaID      视频流的唯一标识
		* @param [in] width	       视频宽度
		* @param [in] height	   视频高度
		*/
		virtual void onFirstRemoteVideoFrame(const char *mediaID, int width, int height) {
			(void)mediaID;
			(void)width;
			(void)height;
		}

		/**
		 * 流控导致视频编码参数发生改变时的回调
		 * @param [in] mediaID      视频流唯一标识
		 * @param [in] bitrate      流控期待的新码率（kbps）
		 * @param [in] fps          流控期待的新帧率
		 * */
		virtual void onEncodeParamChanged(const char *mediaID, int bitrate, int fps) {
			(void)mediaID;
			(void)bitrate;
			(void)fps;
		}

		/**
		* 说话声音音量提示回调。默认禁用。可以通过 enableAudioVolumeIndication 方法设置。
		* @param [in] nUserID					说话者的用户ID
		* @param [in] audioLevel				说话者的音量，在0-9之间
		* @param [in] audioLevelFullRange		说话者的音量，音量范围更大0-32767.5之间
		*/
		virtual void onAudioVolumeIndication(AudioLevelInfo* info) {
			(void)info;
		}

		virtual void onAudioVadIndication(int64_t userID, int active) {
			(void)userID;
			(void)active;
		}
		/**
		* 连接丢失回调
		*/
		virtual void onConnectionLost() {}

		/**
		* 统计数据回调。该回调定期上报 Engine 的运行时的状态，每两秒触发一次
		*
		* @param [in]  stats 通话相关的统计信息
		*/
		virtual void onRtcStats(const RtcStats& stats) {
			(void)stats;
		}

		/**
		* 本地视频统计回调，报告更新本地视频统计信息，该回调函数每两秒触发一次
		*
		* @param [in] stats 本地视频相关的统计信息
		*/
		virtual void onLocalVideoStats(const LocalVideoStats& stats) {
			(void)stats;
		}

		/**
		* 远端视频统计回调，报告更新远端视频统计信息，该回调函数每两秒触发一次
		*
		* @param [in] stats 远端视频的统计信息
		*/
		virtual void onRemoteVideoStats(const RemoteVideoStats& stats) {
			(void)stats;
		}


		virtual void onLocalAudioStats(const LocalAudioStats& stats) {
			(void)stats;
		}
		virtual void onRemoteAudioStats(const RemoteAudioStats& stats) {
			(void)stats;
		}

		/**
		* 自己修改角色后的回调
		*
		* @param [in] newRole   改变后的新角色，副播或观众
		*/
		virtual void onRoleChanged(const CLIENT_ROLE_TYPE newRole) {
			(void)newRole;
		}

		/**
		* 其他用户加入当前频道回调
		*
		* @param [in] userID     加入频道的用户ID
		* @param [in] role		 加入频道的用户的身份，副播或观众
		*/
		virtual void onUserJoined(int64_t userID, CLIENT_ROLE_TYPE role) {
			(void)userID;
			(void)role;
		}
		/**
		* 其他用户离开当前频道回调，主动离开或掉线
		*
		* @param [in] userID    离开频道的用户ID
		* @param [in] reason	该用户离开频道的原因
		*/
		virtual void onUserOffline(int64_t userID, RtcErrorCode reason) {
			(void)userID;
			(void)reason;
		}
		/**
		* 提示有其他用户启用/关闭了视频功能。关闭视频功能是指该用户只能进行语音通话，不能显示、
		* 发送自己的视频，也不能接收、显示别人的视频。
		*
		* @param [in] userID     用户ID
		* @param [in] mediaID	媒体ID
		* @param [in] enabled	用户已启用/关闭了视频功能
		*/
		virtual void onUserEnableVideo(int64_t userID, const char *mediaID, int mediaType, bool enabled) {
			(void)userID;
			(void)mediaID;
			(void)enabled;
		}

		virtual void onMixerVideoCreate(const char *mediaID, const char * mediaURL) {
			(void)mediaID;
			(void)mediaURL;
		}

		virtual void onMixerVideoRemove(const char *mediaID, const char * mediaURL) {
			(void)mediaID;
			(void)mediaURL;

		}

		virtual void onAudioMixingFinished() {}
		virtual void onAudioMixingPosition(uint64_t curPosMS) {
			(void)curPosMS;
		}
		virtual void onAudioEffectFinished(int id) {
			(void)id;
		}
		/**
		* 收到其他房间用户连麦请求
		* @param [in] roomID  请求连麦的房间号
		* @param [in] operUserID 请求连麦的用户ID
		*/
		virtual void onOtherAnchorLink(long long roomID, long long operUserID) {
			(void)roomID;
			(void)operUserID;
		}

		/**
		* 用户发起连麦请求后的回调方法
		* @param [in] roomID  远端房间的ID，
		* @param [in] operUserID 远端房间的用户ID
		* @param [in] operDevID 远端用户的设备描述，列表
		* @param [in] nError 0表示成功，其他表示失败
		*/
		virtual void onOtherAnchorLinked(long long roomID, long long operUserID, const char* operDevID, int nError) {
			(void)roomID;
			(void)operUserID;
			(void)operDevID;
			(void)nError;
		}

		/**
		* 收到其他房间用户断开连麦的请求
		* @param [in] roomID  请求断麦的房间号
		* @param [in] operUserID 请求断麦的用户ID
		*/
		virtual void onOtherAnchorUnlink(long long roomID, long long operUserID, int nError) {
			(void)roomID;
			(void)operUserID;
			(void)nError;
		}

		/**
		* 收到用户断开连麦的响应
		* @param [in] roomID  请求断麦的房间号
		* @param [in] operUserID 请求断麦的用户ID
		*/
		virtual void onOtherAnchorUnLinked(long long roomID, long long operUserID) {
			(void)roomID;
			(void)operUserID;
		}
		/**
		* 根据服务器返回的Sei，获得副播的显示信息。
		* @param [in] SEI 主播设置的SEI值，json格式的字符串
		*/
		virtual void onSetSEI(const char* SEI) {

		}
		/**
		* 本地推流端口收到的回调
		* @param [in] err  回调的提示信息
		* @param [in] operUserID 请求断麦的用户ID
		*/
		virtual void onRTMPsenderror(const char * err) {

		}

		/**
		* 服务器推流状态的回调
		* @param [in] roomID   房间号
		* @param [in] szRTMPURL 有状态变化的旁路推流地址
		* @param [in] status	状态值
		*/
		virtual void onRTMPStatusChange(long long roomID, const char* szRTMPURL, bool status) {
			(void)roomID;
			(void)szRTMPURL;
			(void)status;
		}
		virtual void onRequestChannelKey() {
		}
		virtual void onUserMuteAudio(int64_t userID, bool muted) {
			(void)userID;
			(void)muted;
		}
		virtual void OnConnectSuccess() {}
		virtual void onDisconnected(const char * uuid) {}
	};

	class IVideoFrameObserver
	{
	public:
		//TODO: to TVideoFrame
		enum VIDEO_FRAME_TYPE {
			FRAME_TYPE_YUV420 = 0,  //YUV 420 format

			FRAME_TYPE_H264 = 10,
		};
		struct VideoFrameYUV {
			VIDEO_FRAME_TYPE fmt;
			uint8_t *data[3];       //FRAME_TYPE_YUV420 : 0-y, 1-u, 2-v
			int linesize[3];
			int32_t width;
			int32_t height;
			int64_t pts;
		};
		struct VideoFrameES {
			VIDEO_FRAME_TYPE fmt;   //FRAME_TYPE_H264
			uint8_t *data;
			int len;
			int32_t width;
			int32_t height;
			int64_t pts;
		};
	public:
		virtual ~IVideoFrameObserver() {}

		/* local video */
		virtual void onCaptureVideoFrame(VideoFrameYUV& frame)
		{
			(void)frame;
		}
		virtual void onEncodeVideoFrame(VideoFrameES& frame)
		{
			(void)frame;
		}

		/* remote/mixer video */
		virtual void onReceiveVideoFrame(VideoFrameES& frame)
		{
			(void)frame;
		}
		virtual void onRenderVideoFrame(VideoFrameYUV& frame)
		{
			(void)frame;
		}
	};

	class IAudioFrameObserver
	{
	public:
		virtual ~IAudioFrameObserver() {}

		// 本地麦克风采集的数据
		virtual void onRecordAudioFrame(TAudioFrame* frame)
		{
			(void)frame;
		}

		// 单路远端用户的数据
		virtual void onPlaybackAudioFrame(int64_t userID, TAudioFrame* frame)
		{
			(void)userID;
			(void)frame;
		}

		// 所有远端用户混音后的数据
		virtual void onPlaybackMixedAudioFrame(TAudioFrame* frame)
		{
			(void)frame;
		}

		// 本地和远端混音后的数据
		virtual void onMixedAudioFrame(TAudioFrame* frame)
		{
			(void)frame;
		}
	};

	struct RtcEngineContext
	{
		IRtcEngineEventHandler* eventHandler;
		const char *workPath;
		RTC_SDK_LOG_LEVEL logLevel;

		RtcEngineContext()
			: eventHandler(NULL)
			, workPath(NULL)
			, logLevel(RTC_LOG_LEVEL_DEBUG)
		{}
	};

	class TTT_API IRtcEngine
	{
	public:
		static IRtcEngine* createInstance();
		static const char *getVersion();

		virtual ~IRtcEngine() {};
		virtual int initialize(RtcEngineContext& context) = 0;
		virtual void release() = 0;

		virtual int enableVideo() = 0;
		virtual int disableVideo() = 0; //需在没有本地或远程视频时调用
		virtual int setAppID(const char *appID) = 0;
		// audioOnly 表明 broadcasting profile 时，只 broadcasting 音频数据
		virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;
		virtual int setClientRole(CLIENT_ROLE_TYPE role, const char* permissionKey) = 0; //TODO:去掉无用参数
		virtual int setServerAddr(const char* addr, uint16_t port) = 0;

		virtual void enableAudioAGC(bool enable, bool exp_enable) = 0;
		virtual void enableAudioEC(bool enable, bool exp_enable) = 0;
		virtual void enableAudioNS(bool enable, bool exp_enable) = 0;

		virtual int joinChannel(int64_t channelID, const char *tokenid, int64_t userID) = 0;
		virtual int leaveChannel() = 0;
		virtual int applySpeak(bool speak) = 0;

		virtual void startLocalVideoTest(LocalVideoConfig& config) = 0;
		virtual void stopLocalVideoTest() = 0;

		//音视频模式下，主播需要在进入房间前最少创建一路本地视频
		//创建视频需要在进入房间前或进入房间成功后，请勿在进房间过程中创建
		//return mediaID
		//跨房间连麦时不支持调用此接口
		virtual char* createLocalVideo(LocalVideoConfig& config) = 0;
		//跨房间连麦时不支持调用此接口
		virtual void releaseLocalVideo(const char* mediaID) = 0;

		virtual void reconfigLocalVideo(const char* mediaID, LocalVideoConfig& config) = 0;
		virtual int startPreview(const char *mediaID) = 0;
		virtual int stopPreview(const char *mediaID) = 0;
		virtual void inputVideoFrame(const char* mediaID, TVideoFrame *frame) = 0;

		virtual IRtcPlayer* createRtcPlayer(int64_t userID) = 0; //TODO: userID???
		virtual void releaseRtcPlayer(IRtcPlayer* player) = 0;

		virtual int createRemoteVideo(RemoteVideoConfig& config) = 0;
		virtual void releaseRemoteVideo(uint64_t userID, const char* mediaID) = 0;
		virtual void releaseAllRemoteVideo() = 0;//TODO:

		virtual int createMixerVideo(MixerVideoConfig& config) = 0;
		virtual void releaseMixerVideo(const char* mediaID) = 0;
		virtual int registerVideoFrameObserver(const char* mediaID, IVideoFrameObserver* observer) = 0;
		virtual int registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;
		virtual int unRegisterAudioFrameObserver(IAudioFrameObserver* observer) = 0;
		virtual int enableAllAudioMix(bool enable) = 0;

		virtual int configPublisher(const PublisherConfig& config) = 0;
		//virtual void addPublishStreamUrl(const char* streamUrl) = 0;
		virtual void addPublishStreamUrl(const char* streamUrl, bool bAudioOnly = false) = 0;
		virtual void removePublishStreamUrl(const char* streamUrl) = 0;

		virtual void addVideoMixer(int64_t nUserID, const char *mediaID, const char *streamUrl = nullptr) = 0;
		virtual void delVideoMixer(int64_t nUserID, const char *mediaID, const char *streamUrl = nullptr) = 0;
		virtual void addAudioMixer(int64_t nUserID, const char *streamUrl = nullptr) = 0;
		virtual void delAudioMixer(int64_t nUserID, const char *streamUrl = nullptr) = 0;
		virtual void setVideoMixerBackgroundImgUrl(const char *url, const char *streamUrl = nullptr) = 0;
		virtual void setVideoCompositingLayout(const VideoCompositingLayout& layout, const char* streamUrl = nullptr) = 0;
		virtual void setVideoCompositingLayout(const char* sei, const char* seiExt, const char* streamUrl = nullptr) = 0;
		virtual int setVideoMixerParams(int32_t bitrate, int32_t fps, int32_t width, int32_t height, int32_t encodeMode = 0) = 0;
		virtual int	setAudioMixerParams(int bitrate, int samplerate, int channels) = 0;
		virtual int	SetPreferAudioCodec(AUDIOCODEC audioCodec, int kbitrate, int channels) = 0;


		virtual int muteLocalVideoStream(const char* mediaID, bool mute) = 0;
		virtual int muteRemoteVideoStream(int64_t userID, const char* mediaID, bool mute) = 0;
		virtual int muteAllRemoteVideoStreams(bool mute) = 0;

		virtual bool kickChannelUser(int64_t userID) = 0;

		// 发言权限：主播调用，允许或禁止副播发言
		// TODO: 这俩接口功能一直，留一个即可
		virtual int grantSpeakPermission(int64_t userID, bool enable) = 0;
		virtual int muteRemoteSpeaking(int64_t userID, bool mute) = 0;

		// 音频场景
		//virtual int setAudioProfile(AUDIO_PROFILE_TYPE 	profile,
		//                            AUDIO_SCENARIO_TYPE scenario ) = 0;

		// 音量控制及汇报
		virtual int enableAudioVolumeIndication(int interval) = 0;

		// mode: 0/1/2/3 值越大检测越严格
		virtual int enableAudioVad(int64_t userID, bool enable, int mode) = 0;
		virtual int adjustLocalAudioVolume(int volume) = 0;      // 调节信号强度,原始为100 
		virtual int adjustRemoteAudioVolume(int64_t userID, int volume) = 0;
		virtual int adjustRemoteAudioMixedVolume(int volume) = 0;

		virtual int muteLocalAudioStream(bool mute) = 0;
		virtual int muteRemoteAudioStream(int64_t userID, bool mute) = 0;
		virtual int muteAllRemoteAudioStreams(bool mute) = 0;

		// 耳返
		virtual int enableEarphoneMonitor(int enable) = 0;
		virtual int adjustEarphoneMonitorVolume(int volume) = 0;

		// 音频设备管理
		virtual int getNumOfPlayoutDevices() = 0;
		virtual int getNumOfRecordingDevices() = 0;
		virtual int getPlayoutDeviceName(int index, char deviceName[DEVICE_NAME_LENGTH], char devicePath[DEVICE_NAME_LENGTH]) = 0;
		virtual int getRecordingDeviceName(int index, char deviceName[DEVICE_NAME_LENGTH], char devicePath[DEVICE_NAME_LENGTH]) = 0;
		virtual int setPlayoutDevice(int index) = 0;
		virtual int setRecordingDevice(int index) = 0;
		virtual int setSpeakerVolume(int volume) = 0;       // 设置应用程序播放音量
		virtual int getSpeakerVolume(int* volume) = 0;
		virtual int setMicrophoneVolume(int volume) = 0;    // 设置系统麦克风音量
		virtual int getMicrophoneVolume(int* volume) = 0;

		virtual int startRecordingDeviceTest(int indicationInterval) = 0;
		virtual int stopRecordingDeviceTest() = 0;
		virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;
		virtual int stopPlaybackDeviceTest() = 0;

		// 自定义音频源
		virtual int createExtAudioSource(ExtAudioConfig* config) = 0;
		virtual int releaseExtAudioSource(int id) = 0;
		virtual int reconfigExtAudio(int id, ExtAudioConfig* config) = 0;
		virtual int pushExtAudioFrame(int id, TAudioFrame* frame) = 0;
		virtual int clearExtAudioCache(int id) = 0;
        virtual int setExtAudioPaused(int id, int paused) = 0;
		virtual int adjustExtAudioVolume(int id,
			int playout_volume,
			int publish_volume) = 0;

		// 音乐文件播放及混音
		// struct AudioMixingConfig
		virtual int startAudioMixing(AudioMixingConfig* config) = 0;
		virtual int stopAudioMixing() = 0;
		virtual int pauseAudioMixing() = 0;
		virtual int resumeAudioMixing() = 0;
		virtual int adjustAudioMixingVolume(int volume) = 0;
		virtual int adjustAudioMixingPlayoutVolume(int volume) = 0;
		virtual int getAudioMixingPlayoutVolume() = 0;
		virtual int adjustAudioMixingPublishVolume(int volume) = 0;
		virtual int getAudioMixingPublishVolume() = 0;
		virtual int getAudioMixingDuration() = 0;
		virtual int getAudioMixingCurrentPosition() = 0;
		virtual int setAudioMixingPosition(int pos) = 0;

		// 音效管理
		virtual int loadAudioEffect(const char* filePath) = 0;  //失败返回0，成功返回id
		virtual int unloadAudioEffect(int id) = 0;
		virtual int playAudioEffect(int id, int loop_count, bool publish) = 0;
		virtual int stopAudioEffect(int id) = 0;
		virtual int pauseAudioEffect(int id) = 0;
		virtual int resumeAudioEffect(int id) = 0;
		virtual int setAudioEffectVolume(int id, int volume) = 0;
		virtual int getAudioEffectVolume(int id, int &volume) = 0;

		// 录音
		virtual int startAudioRecording(const char* filepath, AUDIO_RECORDING_QUALITY quality) = 0;
		virtual int stopAudioRecording() = 0;

		//virtual int setHighQualityAudioParameters(bool enable) = 0;

		virtual int sendChatMessage(int64_t nDstUserID, int type, const char* sData) = 0;

		/**
		* 请求和远端房间连麦
		*
		* @param sessionId 远端房间号
		* @param userId 远端主播号码
		*/
		virtual void  linkOtherAnchor(int64_t sessionId, int64_t userId) = 0;

		/**
		* 断开与远端房间的连麦
		*
		* @param sessionId 远端房间号
		* @param userId 远端主播号码
		* @param devId   远端视频设备ID
		*/
		virtual void  unlinkOtherAnchor(int64_t sessionId, int64_t userId, const char* devId) = 0;

		virtual void  subscribeOtherChannel(int64_t sessionId) = 0;
		virtual void  unsubscribeOtherChannel(int64_t sessionId) = 0;
		//virtual bool StartPlay(const char*  rtmpurl, long long userId, void* hVideoWnd) = 0;
		//virtual void StopPlay() = 0;
		virtual int startPushScreenCaptureRect(int iOffsetX, int iOffsetY, int iWidth, int iHeight, AV_PUSH_TYPE type = AV_PUSH_CDN, const char* mp4FilePath = NULL, const char *mCDNPullAddress = NULL) = 0;
		virtual int stopPushScreenCapture() = 0;
		virtual int startPushLocalVideo(LocalVideoConfig& config, AV_PUSH_TYPE type, const char* mp4FilePath, const char *mCDNPullAddress) = 0;
		virtual int stopPushLocalVideo() = 0;

		/**
		* 视频是否上行到混屏
		*
		* @param mediaID 视频编号
		* @param enable  true 上行本视频到混屏  false 本视频不上行到混屏
		*/
		virtual int enableVideoMixer(const char* mediaID, bool enable) = 0;
		/**
		* 更新当前频道所使用的token。如果启用了 Token 机制，过一段时间后使用的 Token 会失效。<br/>
		* 发生 onTokenPrivilegeWillExpire 回调时，应重新获取 Token，然后调用该 API 更新 Token，否则 SDK 无法和服务器建立连接。
		*
		* @param token token值
		* @return 0代表方法调用成功，其他代表失败。see {@link LocalSDKConstants#FUNCTION_SUCCESS}
		*/
		virtual int renewToken(const char *token) = 0;
		virtual int addVideoWatermark(const RtcImage & 	watermark) = 0;
		virtual int clearVideoWatermarks() = 0;
		virtual int getConnectionState() = 0; //网络状态 断线还是重连
	};
}//namespace TTTRtc
#endif
