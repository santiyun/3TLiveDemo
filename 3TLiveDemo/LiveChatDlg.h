#pragma once


// CLiveChatDlg �Ի���

class CLiveChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CLiveChatDlg)

public:
	CLiveChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLiveChatDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
