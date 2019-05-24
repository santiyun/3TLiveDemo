//
// 3TLiveDemoDlg.h : 头文件
//

#pragma once

// CMy3TLiveDemoDlg 对话框
class CMy3TLiveDemoDlg : public CDialog
{
// 构造
public:
	CMy3TLiveDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY3TLIVEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//SDK Engin
	//TTTRtcEngine *m_pRtcEngine;
	//RtcEngineContext_TTT context;
	//CDialog2* pTestDlg;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusEditRoomid();
	CString m_sRoomID;
	afx_msg void OnBnClickedRadioM();
	//  用户类型，主播，副播，观众//  用户类型，主播，副播，观众
	int m_ClientRole;
	afx_msg void OnClickedRadioM();

	afx_msg LRESULT OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnsetting();
	afx_msg void OnBnClickedBtndevicetest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedBtnNewChannelNum();
};
