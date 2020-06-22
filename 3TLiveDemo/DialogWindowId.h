#pragma once


// CDialogWindowId 对话框
typedef struct _TASK_LIST {
    DWORD       dwProcessId;
    DWORD       dwInheritedFromProcessId;
    BOOL        flags;
    HWND      hwnd;
    CHAR        ProcessName[MAX_PATH];
    CHAR        WindowTitle[MAX_PATH];
} TASK_LIST, *PTASK_LIST;
typedef struct _TASK_LIST_ENUM {
    PTASK_LIST  tlist;
    DWORD       numtasks;
} TASK_LIST_ENUM, *PTASK_LIST_ENUM;
class CDialogWindowId : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogWindowId)

public:
	CDialogWindowId(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogWindowId();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DLG_WINDOWID};  
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    HWND m_SelectedWnd;
    CListBox	m_list;
	afx_msg void OnBnClickedOk();

};
