#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Common.h"


// CMicphoneTestDlg 对话框

class CMicphoneTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMicphoneTestDlg)

public:
	CMicphoneTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMicphoneTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MICPHONETEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_volumeShowCtrl;
	CComboBox m_comboMicphone;
	CString m_csMicphone;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMicList();

	DEVICEIDMAP m_mapDeviceIDs;

};
