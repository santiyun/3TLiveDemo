#ifndef __INTERNALIMPL_H__
#define __INTERNALIMPL_H__
#include <string>
#include <map>

bool isdigit(std::string strValue);


#define WM_ON_JOINCHANNELSUCCESS		WM_USER+200
#define WM_ON_LEAVECHANNEL				WM_USER+201
#define WM_ON_ERROR						WM_USER+202
#define WM_ON_CONNECTLOST				WM_USER+203
#define WM_ON_USEROFFLIEN				WM_USER+204
#define WM_ON_USERJOINED				WM_USER+205
#define WM_ON_RTCSTATE_REP				WM_USER+206
#define WM_ON_REMOTE_VIDEO_STATS		WM_USER+207
#define WM_ON_REMOTE_USER_VIDEO_ENABLE	WM_USER+208
#define WM_ON_MP4_JOINED				WM_USER+209
#define WM_ON_AUDIO_VOLUME_REPORT		WM_USER+210
#define WM_ON_MIXERVIDEO_CREATE			WM_USER+211
#define WM_ON_REMOTE_AUDIO_STATS		WM_USER+212
#define WM_ON_RTMP_SENDERROR		    WM_USER+213
#define WM_ON_EFFECTFINISHED		    WM_USER+214
#define WM_ON_TMPSTATUSCHANGE		    WM_USER+215
#define WM_ON_USERMUTEAUDIO             WM_USER+216
#define WM_ON_CONNECTSUCCESS            WM_USER+217
#define WM_ON_DISCONNECTED              WM_USER+218





enum LiveStatus
{
	STATUS_INIT = 0,
	STATUS_JOINING,
	STATUS_JOINED,
	STATUS_LEAVING
};

typedef  uint64_t  uid_ttt;
typedef  uint64_t  rid_ttt;


typedef struct _LivingMemberInfo {
	long mUserID = 0;
	std::string mDeviceID = "";
	int mHwndindex = 0;
}LivingMemberInfo;

struct  UserDeviceConfig
{
	UserDeviceConfig(uid_ttt UerID, std::string DeviceID, bool IsUse) {
		mUserID = UerID;
		mDeviceID = DeviceID;
		mIsUse = IsUse;
		mIsOpen = false;
		mIsDefault = false;
		islocal = false;
		userRole = 1;
		hwndindex = 1;
	}

	uid_ttt mUserID;
	std::string mDeviceID;
	bool mIsUse;
	bool mIsOpen;
	bool mIsDefault = false;
	bool islocal = false;
	int mRender_mode = 1;
	int userRole = 1;
	int hwndindex = 1;
 
	std::string getDeviceID() {
		return mDeviceID;
	}

	bool isUse() {
		return mIsUse;
	}

	void setIsUse(bool mIsUse) {
		mIsUse = mIsUse;
	}
	void setIsOpen(bool IsOpen) {
		mIsOpen = IsOpen;
	}
	void setIsDefault(bool IsDefault) {
		mIsDefault = IsDefault;
	}

	int hashCode() {
		int prime = 31;
		int result = 1;
		result = prime * result + ((mDeviceID.empty()) ? 0 : 1);
		//result = prime * result + (int)(mUserID ^ (mUserID >> > 32));
		return result;
	}
};

typedef  std::map<std::string, UserDeviceConfig> PARTICIPANTSTREAMS;
typedef  std::map<uid_ttt, UserDeviceConfig> PARTICIPANTS;
typedef  std::map<int, std::string> DEVICEIDMAP;


namespace ws_techapi
{
	// internal functions
	std::string ws2s(const std::wstring& ws);
	std::wstring s2ws(const std::string& s);
	std::wstring s2wss(const std::string& s, wchar_t* pws);
	std::string s2utf8(const std::string& s);
	std::string utf82s(const std::string& s);
	std::wstring utf82ws(const std::string &utf8);
	std::string ws2utf8(const std::wstring &ws);
	std::string llToString(long long llvalue);
	std::string doubleToString(double d);

}
#endif
