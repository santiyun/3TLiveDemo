#pragma once


// CMicphomeTesting �Ի���

class CMicphomeTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CMicphomeTesting)

public:
	CMicphomeTesting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMicphomeTesting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
