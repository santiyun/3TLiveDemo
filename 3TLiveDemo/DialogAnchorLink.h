#pragma once


// CDialogAnchorLink �Ի���

class CDialogAnchorLink : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAnchorLink)

public:
	CDialogAnchorLink(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogAnchorLink();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DLG_ANCHORLINK};  
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	LONGLONG m_llRoomID;
	LONGLONG m_llUserID;
	afx_msg void OnBnClickedOk();
};
