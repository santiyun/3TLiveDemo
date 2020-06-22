#pragma once
#include "afxwin.h"


// CLocalSetting 对话框

class CLocalSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CLocalSetting)

public:
	CLocalSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLocalSetting();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LOCALSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	CComboBox m_comboLevel;
	int m_videoResolution;
	CEdit m_edtResolutionCtrl;
	CEdit m_edtRateCtrl;
	CEdit m_edtFramerateCtrl;
	BOOL m_bUserHighQualityAudio;
    BOOL m_bEnable_hwaccel;
    BOOL m_bEnable_mirror;
	afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedCheckHW();
	CButton m_chkUseHighQualityAudio;
    CButton m_chkEnable_hwaccel;
    CButton m_chkEnable_mirror;
	int m_bitrate;
	int m_framerate;
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
};
