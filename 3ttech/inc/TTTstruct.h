#ifndef __TTTSTRUCT_H__
#define __TTTSTRUCT_H__
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
//typedef long long uid_t;
typedef void* view_t;
typedef int (*getPcmDataFunc)(char *buffer, int buffer_size, void* userdata);

typedef enum {
	/* 通信模式，频道中的任何用户可以自由说话 */
	CHANNEL_PROFILE_COMMUNICATION = 0,

	/* 直播模式，有主播、副播、观众三种角色（默认） */
	CHANNEL_PROFILE_LIVE_BROADCASTING = 1,

    CHANNEL_PROFILE_FORCE_DWORD = 0x7fffffff,
} CHANNEL_PROFILE_TYPE;

typedef enum {
	/*默认状态，没有连接*/
	CONNECT_STATE_DEFAULT = 0,
	CONNECT_STATE_CONNECTING,
	CONNECT_STATE_CONNECTFAIL,
	CONNECT_STATE_CONNECTED,
	CONNECT_STATE_DISCONNECT,
	CONNECT_STATE_RECONNECTTIMEOUT,
	CONNECT_STATE_FORCE_DWORD = 0x7fffffff

}CONNECT_STATE_TYPE;

typedef enum {
	/* 主播 */
    CLIENT_ROLE_BROADCASTER = 1,

	/* 副播 */
    CLIENT_ROLE_ANCHOR = 2,
	
	/* 观众(默认) */
	CLIENT_ROLE_AUDIENCE = 3,

    CLIENT_ROLE_FORCE_DWORD = 0x7fffffff,
} CLIENT_ROLE_TYPE;

typedef enum {
	/* 录制mp4 */
	AV_RECORD_MP4 = 1,
	/* 推流到cdn */
	AV_PUSH_CDN = 2,
	/* 录制mp4 同时 推流到cdn */
	AV_PUSH_MP4_CDN = 3,
	AV_PUSH_FORCE_DWORD = 0x7fffffff,
} AV_PUSH_TYPE;

typedef enum {
    AUDIO_RECORDING_QUALITY_LOW = 0,
    AUDIO_RECORDING_QUALITY_MEDIUM,
    AUDIO_RECORDING_QUALITY_HIGH,

    AUDIO_RECORDING_QUALITY_DWORD = 0x7fffffff,
} AUDIO_RECORDING_QUALITY;


typedef enum {
    VIDEO_CAPTURE_CAMERA,
    VIDEO_CAPTURE_SCREEN,
    VIDEO_CAPTURE_RAWDATA,

    VIDEO_CAPTURE_FORCE_DWORD = 0x7fffffff,
} VIDEO_CAPTURE_TYPE;

typedef enum {
    VIDEO_SCALE_HIDDEN,
    VIDEO_SCALE_FIT,

    VIDEO_SCALE_FORCE_DWORD = 0x7fffffff,
} VIDEO_SCALE_TYPE;

typedef enum 
{
    RTC_LOG_LEVEL_NULL = 0,
    RTC_LOG_LEVEL_FATAL,
    RTC_LOG_LEVEL_ERROR,
    RTC_LOG_LEVEL_WARN,
    RTC_LOG_LEVEL_INFO,
    RTC_LOG_LEVEL_DEBUG,
    RTC_LOG_LEVEL_TRACE,

    RTC_LOG_LEVEL_FORCE_DWORD = 0x7fffffff,
} RTC_SDK_LOG_LEVEL;

/* TODO: 统一格式，如ERR_XXXX_XXXX */
typedef enum {
    ENTERCONFAPI_NOERROR = 0, // 成功
    ENTERCONFAPI_TIMEOUT = 1, // 超时,5秒未收到服务器返回结果
    ENTERCONFAPI_ENTER_FAILED = 2, // 无法连接服务器
    ENTERCONFAPI_VERIFY_FAILED = 3, // 验证码错误
    ENTERCONFAPI_BAD_VERSION = 4, // 版本错误

    //DISCONNECT RESOON 会议被踢出原因
    KICKEDBYHOST = 101,  // 被主播踢出
    PUSHRTMPFAILED = 102, // rtmp推流失败
    SERVEROVERLOAD = 103, // 服务器过载
    MASTER_EXIT = 104,   // 主播已退出
    RELOGIN = 105,      // 重复登录
    NOAUDIODATA = 106,    // 长时间没有上行音频数据
    NOVIDEODATA = 107,   // 长时间没有上行视频数据
    NEWCHAIRENTER = 108,  // 其他人以主播身份进入
    CHANNELKEYEXPIRED = 109, // Channel Key失效

    USER_EXIT_REASON_TIMEOUT = 201,   // 超时退出
    USER_EXIT_REASON_LINKCLOSE = 202, // 网络断开退出
	PARAMERR = 203,            //参数错误
    RE_NEW_CHANNEL_KEY_FAILD = 401,  // 重新鉴权失败

    ERRCODE_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
} RtcErrorCode;


#pragma pack(1)
typedef struct  {
    int32_t index;
    char frendlyName[128];
    char devicePath[128];
    int32_t maxWidth;
    int32_t maxHeight;
} VideoDeviceInfo;

typedef struct {
    int32_t fmt;  //unused, only support I420 now
    uint8_t *data[3];   //YUV: 0-y, 1-u, 2-v,  RGB: 0-data
    int linesize[3];
    int32_t width;
    int32_t height;
    int64_t timestamp;
    int32_t framerate;
} TVideoFrame;

typedef struct {
    uint8_t* data;              //PCM 16bit little endian
    int32_t length;             //samples_per_channel * num_channels * 2
    int32_t num_channels;
    int32_t samples_per_channel;  // 目前仅支持480的倍数
    int32_t sample_rate_hz;     //16000 32000 48000  (暂不支持44100采样率)
    int64_t timestamp;
} TAudioFrame;

typedef struct {
    int32_t enable_playout;
    int32_t enable_publish;
    int32_t cache_ms;
} ExtAudioConfig;

typedef struct {
    char filePath[512];
    int32_t enable_playout;
    int32_t enable_publish;
    int32_t cycle;
} AudioMixingConfig;

typedef struct  {
    int64_t user_id;
    int level;
} RemoteAudioLevel;
typedef struct {
    int id;
    int playout_level;
    int publish_level;
} ExtAudioLevel;
typedef struct {
    // Local
    int local_level;

    // Remote
    RemoteAudioLevel remote[32];
    int remote_num;

    // AudioMixing
    int mixing_playout_level;
    int mixing_publish_level;

    // ExtAudio and AudioEffect
    ExtAudioLevel external[32];
    int external_num;
} AudioLevelInfo;

typedef struct {
	int32_t muted;
    int32_t muted_ms;    //总静音时长
	int64_t cap_samples;                  // 总采样点数
	int64_t bytes_encoded;
	int32_t bitrate_kbps;
    int32_t retrans_bitrate_kbps;
    int32_t rtt_ms;
    float fraction_lost;
	int32_t audio_level;                 // FullRange
    int32_t original_level;
    float voluem_set;
} LocalAudioStats;

typedef struct {
    int64_t userID;
	uint32_t ssrc;
	int32_t muted;
    int32_t muted_ms;
    int32_t remote_muted;  //muted by is self
    int32_t bitrate_kbps;
    int32_t rtt_ms;
    int32_t audio_level;
    float volume_set;

    float lost_rate;
    float fraction_lost;
    int32_t delay_estimate_ms;
    int32_t jitter_ms;
    int32_t max_jitter_ms;
    int32_t jitter_buffer_ms;

	int64_t bytes_rcvd;
    int64_t bytes_decoded;
	int32_t carton_ms;
    int32_t carton_count;
    int32_t carton_rate;
} RemoteAudioStats;

typedef struct {
    int64_t userID;
    VIDEO_CAPTURE_TYPE type;
    void *viewHwnd;

    VIDEO_SCALE_TYPE encScaleType;
    VIDEO_SCALE_TYPE renderScaleType;

    int32_t width;      //编码输出视频宽度
    int32_t height;     //编码输出视频高度
    int32_t framerate;  //编码输出视频帧率

    int32_t bitrateKbps; //视频编码码率，为0时内部自行计算 h * w / 800

    /* for camera capture */
    int32_t devIndex;

    /* for screen capture */
    int32_t fullScreen; //0：采集screenRect区域，1：采集全屏
    struct {
        int32_t x, y, w, h;  //采集区域, x: 左上角x坐标, y: 左上角y坐标, w: 采集宽度, h: 采集高度
    } screenRect;

    /* for rawdata input */
    int32_t srcWidth; //yuv 输入源视频宽
    int32_t srcHeight; //yuv 输入视频源高
    int32_t srcFramerate;
} LocalVideoConfig;

typedef struct {
    int32_t enable_video;
    int32_t enable_audio;

    // auddio
    int32_t enable_playout;
    int32_t enable_publish;
    int playout_volume;
    int publish_volume;

    // video
    void *viewHwnd;     //显示窗口句柄
    int32_t width;      //输出视频宽度
    int32_t height;     //输出视频高度
    int32_t framerate;  //输出视频帧率

    VIDEO_SCALE_TYPE encScaleType;      //编码输出裁剪方式
    VIDEO_SCALE_TYPE renderScaleType;   //本地回显裁剪方式
} RtcPlayerConfig;

typedef struct {
    int64_t userID;
    char mediaID[128];
    void *hwnd;
    VIDEO_SCALE_TYPE renderScaleType;
} RemoteVideoConfig;

typedef struct {
    char mediaID[128];
    void *hwnd;
    VIDEO_SCALE_TYPE renderScaleType;
} MixerVideoConfig;

typedef struct {
    /* 通话时长(秒)，累计值 */
    uint32_t duration;

    /* 发送字节数(bytes), 累计值 */
    uint32_t txBytes;

    /* 接收字节数(bytes)，累计值 */
    uint32_t rxBytes;

    /* 接受音频码率(kbps)，瞬时值 */
    uint16_t rxAudioKBitRate;

    /* 发送音频码率(kbps)，瞬时值 */
    uint16_t txAudioKBitRate;

    /* 接受视频码率(kbps)，瞬时值 */
    uint16_t rxVideoKBitRate;

    /* 发送视频码率(kbps)，瞬时值 */
    uint16_t txVideoKBitRate;
    uint32_t users;
    double cpuAppUsage;
    double cpuTotalUsage;
} RtcStats;

typedef struct {
	/*视频流所属的用户ID*/
    int64_t userID;
	/*视频流的媒体ID*/
    char mediaID[128];
	/*视频流的宽度*/
    int32_t width;
	/*视频流的高度*/
	int32_t height;
	/*视频流的码率*/
	int32_t bitrateKbps;
	/*视频流的帧率*/
	int32_t frameRate;
} RemoteVideoStats;

typedef struct {
    char mediaID[128];

    /* 发送码率(kbps) */
    int32_t sentBitrate;

    /* 发送帧率(fps) */
    int32_t sentFrameRate;
} LocalVideoStats;

/**
* 配置旁路直播推流的类
*/
typedef struct {
    /**
    * Description: 设置推流的地址.
    *
    * @param url 推流的地址
    * @return the builder
    */
    char publishUrl[1024];

	//是否纯音频
	int bAudioOnly;

}PublisherConfig;

/**
* 画中画布局
*/
typedef struct {
    /* 小视频的用户ID, 为0时无效 */
    int64_t userID;
    char mediaID[128];
    /* 小视频X坐标 [0,1] */
    double x;
    /* 小视频Y坐标 [0,1] */
    double y;
    /* 小视频宽度 [0,1] */
    double width;
    /* 小视频高度 [0,1] */
    double height;
    /* 小视频层级关系 */
    int32_t zOrder;

    double alpha;
    int32_t isRegin;
} VideoRegion;

#define MAX_VIDEO_REGIONS 32
typedef struct {
    int32_t canvasWidth;
    int32_t canvasHeight;
    /* 视频背景颜色，RGB值，[0-255 , 0-255 , 0-255] */
    /* e.g. "#C0C0C0" in RGB */
    char backgroundColor[8];

    /* 小视频窗口数据集合 */
    VideoRegion regions[MAX_VIDEO_REGIONS];
    int32_t regionCount;

    char appData[1024];
    int32_t appDataLength;
} VideoCompositingLayout;

typedef enum  {
	kFlagPlayAudio = 0x00000001,
	kFlagPlayVideo = 0x00000002,
	kFlagLoopback = 0x00000004,

	kFlagAll = 0x000000ff,
} PlayerFlag;
typedef struct {
	float   volume;     //输出音频音量 0.0-2.0
} AudioConfig;
typedef struct  {
	void *viewHwnd;     //显示窗口句柄
	int32_t width;      //输出视频宽度
	int32_t height;     //输出视频高度
	int32_t framerate;  //输出视频帧率

	VIDEO_SCALE_TYPE encScaleType;      //编码输出裁剪方式
	VIDEO_SCALE_TYPE renderScaleType;   //本地回显裁剪方式
} VideoConfig;

typedef struct {
	char url[1024]; //直播视频上图片的地址。字符长度不得超过 1024 字节。
	int32_t x;      //水印或背景图片在视频帧左上角的横轴坐标。
	int32_t y;     //水印或背景图片在视频帧左上角的纵轴坐标。
	int32_t width;  //水印或背景图片在视频帧上的宽度。
	int32_t height;  //水印或背景图片在视频帧上的高度。
} RtcImage;
typedef enum
{
	CODEC_DEFAULT = 0,
	CODEC_AAC = 1,
	CODEC_ISAC_WB = 2,
	CODEC_ISAC_UWB = 3,
	CODEC_OPUS = 4,
	CODEC_HEAAC = 5
} AUDIOCODEC;
#pragma pack()

#endif
