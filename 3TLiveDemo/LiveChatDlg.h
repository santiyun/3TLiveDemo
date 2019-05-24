#pragma once


// CLiveChatDlg 对话框

class CLiveChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CLiveChatDlg)

public:
	CLiveChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLiveChatDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
