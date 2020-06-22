// TestResultDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "TestResultDlg.h"
#include "afxdialogex.h"


// CTestResultDlg 对话框

IMPLEMENT_DYNAMIC(CTestResultDlg, CDialogEx)

CTestResultDlg::CTestResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_RESULT, pParent)
	, m_csCameraResult(_T("失败"))
	, m_csMicResult(_T("失败"))
	, m_csSpeakerResult(_T("失败"))
{

}

CTestResultDlg::~CTestResultDlg()
{
}

void CTestResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_CAM_RESULT, m_csCameraResult);
	DDX_Text(pDX, IDC_STATIC_MIC_RESULT, m_csMicResult);
	DDX_Text(pDX, IDC_STATIC_SPEAKER_RESULT, m_csSpeakerResult);
}


BEGIN_MESSAGE_MAP(CTestResultDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CTestResultDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTestResultDlg 消息处理程序


void CTestResultDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CTestResultDlg::showResult(bool camera, bool mic, bool speaker)
{
	m_csCameraResult = camera ? "成功" : "失败";
	m_csMicResult = mic ? "成功" : "失败";
	m_csSpeakerResult = speaker ? "成功" : "失败";
	UpdateData(false);
	return;
}
