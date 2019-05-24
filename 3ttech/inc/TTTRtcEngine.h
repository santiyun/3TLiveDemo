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

    class TTT_API IRtcPlayer
    {
    public:
        enum PlayerFlag : int32_t {
            kFlagPlayAudio = 0x00000001,
            kFlagPlayVideo = 0x00000002,
            kFlagLoopback = 0x00000004,

            kFlagAll = 0x000000ff,
        };
        enum ReturnCodes {
            kSuccess = 0,
            kError = -1
        };
        struct AudioConfig {
            float   valume;     //输出音频音量 0.0-2.0
        };
        struct VideoConfig {
             void *viewHwnd;     //显示窗口句柄
             int32_t width;      //输出视频宽度
             int32_t height;     //输出视频高度
             int32_t framerate;  //输出视频帧率

             VIDEO_SCALE_TYPE encScaleType;      //编码输出裁剪方式
             VIDEO_SCALE_TYPE renderScaleType;   //本地回显裁剪方式
        };

        virtual ~IRtcPlayer() {}
        virtual int start(const char* url, int flags, AudioConfig* aconfig, VideoConfig* vconfig) = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual uint32_t volume() = 0;
        virtual void setVolume(uint32_t volume) = 0;
        virtual int duration() = 0;  //length in seconds
        virtual void seek(uint32_t seconds) = 0;
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
		* 说话声音音量提示回调。默认禁用。可以通过 enableAudioVolumeIndication 方法设置。
		* @param [in] nUserID					说话者的用户ID
		* @param [in] audioLevel				说话者的音量，在0-9之间
		* @param [in] audioLevelFullRange		说话者的音量，音量范围更大0-32767.5之间
		*/
		virtual void onAudioVolumeIndication(int64_t nUserID, int audioLevel, int audioLevelFullRange) {
            (void)nUserID;
            (void)audioLevel;
            (void)audioLevelFullRange;
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
        //TODO:音频状态

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
		virtual void onUserEnableVideo(int64_t userID, const char *mediaID, bool enabled) {
            (void)userID;
            (void)mediaID;
            (void)enabled;
        }
        virtual void onMixerVideoCreate(const char *mediaID) {
            (void)mediaID;
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

		}

		/**
		* 收到其他房间用户断开连麦的请求
		* @param [in] roomID  请求断麦的房间号
		* @param [in] operUserID 请求断麦的用户ID
		*/
		virtual void onOtherAnchorUnlink(long long roomID, long long operUserID, int nError) {

		}

		/**
		* 收到用户断开连麦的响应
		* @param [in] roomID  请求断麦的房间号
		* @param [in] operUserID 请求断麦的用户ID
		*/
		virtual void onOtherAnchorUnLinked(long long roomID, long long operUserID) {

		}
	};
    
    class IVideoFrameObserver
    {
    public:
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
		virtual int initialize(RtcEngineContext& context) = 0;
        virtual void release() = 0;
        
		virtual char* getVersion() = 0;
        virtual int enableVideo() = 0;
        virtual int disableVideo() = 0; //需在没有本地或远程视频时调用
        virtual int setAppID(const char *appID) = 0;
		virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;
		virtual int setClientRole(CLIENT_ROLE_TYPE role, const char* permissionKey) = 0; //TODO:去掉无用参数
        virtual int setServerAddr(const char* addr, uint16_t port) = 0;
        virtual int configPublisher(const PublisherConfig& config) = 0;

        virtual int joinChannel(int64_t channelID, char *channelName, int64_t userID) = 0;
        virtual int leaveChannel() = 0;
        virtual int applySpeak() = 0;

        virtual void startLocalVideoTest(LocalVideoConfig& config) = 0;
        virtual void stopLocalVideoTest() = 0;

        //音视频模式下，主播需要在进入房间前最少创建一路本地视频
        //创建视频需要在进入房间前或进入房间成功后，请勿在进房间过程中创建
        //return mediaID
        virtual char* createLocalVideo(LocalVideoConfig& config) = 0;
        virtual void releaseLocalVideo(const char* mediaID) = 0;
        virtual void reconfigLocalVideo(const char* mediaID, LocalVideoConfig& config) = 0;
        virtual int startPreview(const char *mediaID) = 0;
        virtual int stopPreview(const char *mediaID) = 0;
        virtual void inputVideoFrame(const char* mediaID, VideoFrame *frame) = 0;

        virtual IRtcPlayer* createRtcPlayer(int64_t userID) = 0; //TODO: userID???
        virtual void releaseRtcPlayer(IRtcPlayer* player) = 0;

        virtual int createRemoteVideo(RemoteVideoConfig& config) = 0;
        virtual void releaseRemoteVideo(uint64_t userID, const char* mediaID) = 0;
        virtual void releaseAllRemoteVideo() = 0;//TODO:

        virtual int createMixerVideo(MixerVideoConfig& config) = 0;
        virtual void releaseMixerVideo(const char* mediaID) = 0;
        virtual int registerVideoFrameObserver(const char* mediaID, IVideoFrameObserver* observer) = 0;

        virtual void addVideoMixer(int64_t nUserID, const char *mediaID) = 0;
        virtual void delVideoMixer(int64_t nUserID, const char *mediaID) = 0;
        virtual void setVideoMixerBackgroundImgUrl(const char *url) = 0;
        virtual void setVideoCompositingLayout(const VideoCompositingLayout& layout) = 0;
        virtual void setVideoCompositingLayout(const char* sei, const char* seiExt) = 0;
        
        //禁言
        virtual int muteRemoteSpeaking(int64_t userID, bool mute) = 0;
        virtual int muteLocalAudioStream(bool mute) = 0;
        virtual int muteRemoteAudioStream(int64_t userID, bool mute) = 0;
        virtual int muteAllRemoteAudioStreams(bool mute) = 0;

        //暂未实现
        virtual int muteLocalVideoStream(const char* mediaID, bool mute) = 0;
        virtual int muteRemoteVideoStream(int64_t userID, const char* mediaID, bool mute) = 0;
        virtual int muteAllRemoteVideoStreams(bool mute) = 0;
        
        //主播调用，赋予副播发言权限
        virtual int grantSpeakPermission(int64_t userID, bool enable) = 0;
        virtual bool kickChannelUser(int64_t userID) = 0;

		//音频库相关接口
        virtual int setSpeakerphoneVolume(int volume) = 0;//设置自己的音量
		virtual int setRecordDevice(int index) = 0;
		virtual int setPlayDevice(int index) = 0;
		virtual int setRecordVolume(int volume) = 0;
		virtual int getNumOfPlayoutDevices() = 0;  //TODO: 与视频相关接口统一
		virtual int getNumOfRecordingDevices() = 0;
		virtual int getPlayoutDeviceName(int index, char* deviceName) = 0;
		virtual int getRecordingDeviceName(int index, char* deviceName) = 0;
		virtual void pauseAudio() = 0;
		virtual void resumeAudio() = 0;

        //TODO: 目前仅支持固定的PCM格式；后续可以将重采样工作放到音频模块中，以支持不同的PCM格式
        virtual void getSupportedPcmInfo(int& samples_per_channel, int& samplerate, int& channels) = 0;
        //virtual void inputPcmFrame(const char* data, int samples_per_channel, int samplerate, int channels) = 0;
        virtual int registerPcmSource(getPcmDataFunc func, void* userdata) = 0;
        virtual void unregisterPcmSource(int id) = 0;

        //控制音量汇报间隔
		virtual int enableAudioVolumeIndication(int interval, int smooth) = 0;

		virtual int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle) = 0;
		virtual int stopAudioMixing() = 0;
		virtual int pauseAudioMixing() = 0;
		virtual int resumeAudioMixing() = 0;
		virtual int adjustAudioMixingVolume(int volume) = 0;
		virtual int getAudioMixingDuration() = 0;
		virtual int getAudioMixingCurrentPosition() = 0;
		virtual int setAudioMixingPosition(int volume) = 0;

		virtual int setHighQualityAudioParameters(bool enable) = 0;
		
        virtual int sendChatMessage(int64_t nDstUserID, int type, char*  sData) = 0;
		virtual int startRecordingDeviceTest(int indicationInterval) = 0;
		virtual int stopRecordingDeviceTest() = 0;
		virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;
		virtual int stopPlaybackDeviceTest() = 0;

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

		/**
		* 视频是否上行到混屏
		*
		* @param mediaID 视频编号
		* @param enable  true 上行本视频到混屏  false 本视频不上行到混屏
		*/
		virtual int enableVideoMixer(const char* mediaID, bool enable) = 0;

	};
}//namespace TTTRtc
#endif
