#pragma once
#include "afxwin.h"


// CDlgServerOption �Ի���

class CDlgServerOption : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgServerOption)

public:
	CDlgServerOption(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgServerOption();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SERVER_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
