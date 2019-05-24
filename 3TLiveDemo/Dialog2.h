#pragma once
#include "afxwin.h"
#include "Common.h"
#include "afxcmn.h"
#include "afxbutton.h"


// CDialog2 对话框

class CDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CDialog2)

public:
	CDialog2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog2();

	bool m_bJoinChannel;
	bool m_bSDKTEST;
	LiveStatus  m_Status;
	int m_CurSelVideoIndex;

	int joinChannel();
	VideoCompositingLayout m_vclayout;
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton btnOK;

	void SDKTestTimer();
	void KillSDKTimer();

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnIdclose();
	afx_msg void OnClose();

	afx_msg LRESULT OnJoinChannel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLeaveChannel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnectionLost(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserOffline(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserOnline(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRtcState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoteVideoState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoteVideoEnable(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMP4Joined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMixerVideoCreate(WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_MsgLst;

private:
	void InsertMsgAndEvent(std::string stype, std::string errcode, std::string msg);
	void UpdateBtnStatus();
	bool isLiveMaster(); 
	bool isLiveParticipant();
	bool isGuest(); 
	int  getLocalVideoHwndindex();
	void ReleaseAllVideo();
	void ReleaseChannel();
	void addMixerVideo(int64_t userID, const char *mediaID, bool isMaster);
	void delMixerVideo(int64_t userID, const char *mediaID);
	void initLayout();
public:
	CString m_csRoomNum;
	CString m_csClientRole;
	CString m_csUserID;
	CString m_csParticipants;
	CString m_csVideoUpload;
	CString m_csAudioUpload;
	CString m_csPushURL;

	int m_TotleParticipants;
	PARTICIPANTSTREAMS m_mapStreams; //当前系统中可以显示的所有流；一个用户可以有多个流。
	PARTICIPANTS m_mapParticipants;
	int m_hWndsforClient[50];   //0 表示该窗口未被占用，1表示被占用
	//uid_ttt m_hWndClientUID[6]; //可以合并到m_LivingMemberArray里去，表示每个窗口显示的那个刘；userID不再唯一，要改成mediaID
	bool m_ClientAudioStreamMute[10];
	bool m_ClientVideoStreamMute[10];
	LivingMemberInfo m_LivingMemberArray[50];  //当前显示在界面的视频流
	std::string m_screenMedia; //屏幕共享的mediaid
	std::string m_secondMedia; //第二路视频的mediaid
	bool m_mixing = false;
	bool m_openedCamera = false;


	bool m_sharedata;
	CString m_Video0Info;
	CString m_Video2Info;
	CString m_Video3Info;
	CString m_Video4Info;
	CString m_Video5Info;
	afx_msg void OnClickedButton1();
	afx_msg void OnBnClickedStaticMainvideo();
	afx_msg void OnBnDoubleclickedStaticMainvideo();
	afx_msg void OnClickedStaticVideo1();
	afx_msg void OnClickedStaticVideo2();
	afx_msg void OnClickedStaticVideo3();
	afx_msg void OnClickedStaticVideo4();
	afx_msg void OnClickedStaticVideo5();
	CMFCButton m_btnMuteRemoteAudio;
	CMFCButton m_btnKickOut;
	CMFCButton m_btnMuteUnmuteSpeaker;
	CMFCButton m_btnMuteUnmuteMic;
	CMFCButton m_btnMuteUnmuteCamera;
	CMFCButton m_btnPlayMp4;
	CMFCButton m_btnShowNetStat;
	CMFCButton m_btnUpgradeClientrole;
	afx_msg void OnClickedBtnMuteRemoteAudio();
	afx_msg void OnClickedBtnMuteUnmuteCamera();
	afx_msg void OnClickedBtnMuteUnmuteMic();
	afx_msg void OnClickedBtnMuteUnmuteNetstat();
	afx_msg void OnClickedBtnMuteUnmuteSpeaker();
	afx_msg void OnClickedBtnUpgradeClientrole();
	int m_curSelRemoteParticipant;
	afx_msg void OnClickedBtnKickOut();
	afx_msg void OnClickedBtnMp4Play();
	CStatic m_ShowMp4;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnClickedBtnAnchorlink();
	CMFCButton m_btnAnchorLink;
	afx_msg void OnBnClickedBtnMuteRemoteVideo();
	afx_msg void OnBnClickedBtnSetvolume();
	CSliderCtrl m_sliderMicVolume;
	CSliderCtrl m_sliderSpeakerVolume;
	afx_msg void OnNMThemeChangedSliderMicvolume(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedBtnDataShare();
	afx_msg void OnBnClickedBtn2Camera();
};
