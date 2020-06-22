#pragma once
#include "afxwin.h"


// CDlgServerOption 对话框

class CDlgServerOption : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgServerOption)

public:
	CDlgServerOption(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgServerOption();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SERVER_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csAddr;
	int m_iPort;
	CComboBox m_comboAppID;
	CString m_csAppID;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboAppid();
	afx_msg void OnEnKillfocusEdtServerPort();
	afx_msg void OnEnKillfocusEdtServerAddr();
	afx_msg void OnThemechangedComboAppid(NMHDR *pNMHDR, LRESULT *pResult);
};
