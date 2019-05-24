#pragma once
#include "afxcmn.h"
#include "CameraTesting.h"
#include "MicphoneTestDlg.h"
#include  "SpeakerTesting.h"
#include  "SpeakerTesting.h"
#include  "TestResultDlg.h"
#include "afxwin.h"


// CTestDlg 对话框

class CTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabTestStepByStep;
	virtual BOOL OnInitDialog();

	void UpdateTabStatus();

	CCameraTesting m_dlgCameraTesting;
	CMicphoneTestDlg m_dlgMicphoneTesting;
	CSpeakerTesting m_dlgSpeading;
	CTestResultDlg m_dlgResult;
	afx_msg void OnTcnSelchangeTabTesting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSelchangingTabTesting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedNext();
	afx_msg LRESULT OnAudioVolume(WPARAM wParam, LPARAM lParam);
	
	CString m_csMsgShow;
	CString m_csMsg;

	bool m_bCamera;
	bool m_bMicphone;
	bool m_bSpeaker;
	CButton m_btnCheck;
	CButton m_btnCheckError;
};
