#pragma once
#include "afxcmn.h"
#include "PushSetting.h"
#include "LocalSetting.h"
#include "DlgServerOption.h"


// CMySetting �Ի���

class CMySetting : public CDialogEx
{
	DECLARE_DYNAMIC(CMySetting)

public:
	CMySetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMySetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_tabSetting;

	CPushSetting m_dlgPushSetting;
	CLocalSetting m_dlgLocalSetting;
	CDlgServerOption m_dlgServer;

	afx_msg void OnTcnSelchangeTabsetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
