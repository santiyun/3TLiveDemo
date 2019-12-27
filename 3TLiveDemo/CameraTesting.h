#pragma once
#include "afxwin.h"


// CCameraTesting 对话框

class CCameraTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraTesting)
	virtual BOOL PreTranslateMessage(MSG* pMsg);


public:
	CCameraTesting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraTesting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CAMERTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_videoShowCtrl;
	virtual BOOL OnInitDialog();
	CComboBox m_comboDeviceEnum;
	afx_msg void OnCurCameraSelchange();
	CString m_csDeviceName;
};
