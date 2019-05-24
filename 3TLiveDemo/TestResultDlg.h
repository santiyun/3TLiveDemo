#pragma once


// CTestResultDlg 对话框

class CTestResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestResultDlg)

public:
	CTestResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestResultDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_csCameraResult;
	CString m_csMicResult;
	CString m_csSpeakerResult;

	void showResult(bool camera, bool mic, bool speaker);
};
