#pragma once
#include "afxwin.h"


// CPushSetting �Ի���

class CPushSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPushSetting)

public:
	CPushSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPushSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PUSHSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboSolution;
	int m_comboindex;
	int m_comboCodecIndex;
	CComboBox m_comboCodec;
	CComboBox m_comboAudiofrequnce;
	int m_comboAudioIndex;
	afx_msg void OnCbnSelchangeComboSolution();
	CEdit m_edtSize;
	CEdit m_edtBitrate;
	CEdit m_edtFramerate;
};
