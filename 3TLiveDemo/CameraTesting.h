#pragma once
#include "afxwin.h"


// CCameraTesting �Ի���

class CCameraTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraTesting)
	virtual BOOL PreTranslateMessage(MSG* pMsg);


public:
	CCameraTesting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCameraTesting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CAMERTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_videoShowCtrl;
	virtual BOOL OnInitDialog();
	CComboBox m_comboDeviceEnum;
	afx_msg void OnCurCameraSelchange();
	CString m_csDeviceName;
};
