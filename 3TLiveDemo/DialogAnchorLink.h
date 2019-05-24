#pragma once


// CDialogAnchorLink 对话框

class CDialogAnchorLink : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAnchorLink)

public:
	CDialogAnchorLink(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogAnchorLink();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DLG_ANCHORLINK};  
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	LONGLONG m_llRoomID;
	LONGLONG m_llUserID;
	afx_msg void OnBnClickedOk();
};
