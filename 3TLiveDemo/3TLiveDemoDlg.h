//
// 3TLiveDemoDlg.h : ͷ�ļ�
//

#pragma once

// CMy3TLiveDemoDlg �Ի���
class CMy3TLiveDemoDlg : public CDialog
{
// ����
public:
	CMy3TLiveDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY3TLIVEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//  �û����ͣ�����������������//  �û����ͣ�����������������
	int m_ClientRole;
	afx_msg void OnClickedRadioM();

	afx_msg LRESULT OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnsetting();
	afx_msg void OnBnClickedBtndevicetest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedBtnNewChannelNum();
};
