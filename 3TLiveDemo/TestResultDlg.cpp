// TestResultDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "TestResultDlg.h"
#include "afxdialogex.h"


// CTestResultDlg �Ի���

IMPLEMENT_DYNAMIC(CTestResultDlg, CDialogEx)

CTestResultDlg::CTestResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_RESULT, pParent)
	, m_csCameraResult(_T("ʧ��"))
	, m_csMicResult(_T("ʧ��"))
	, m_csSpeakerResult(_T("ʧ��"))
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


// CTestResultDlg ��Ϣ�������


void CTestResultDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CTestResultDlg::showResult(bool camera, bool mic, bool speaker)
{
	m_csCameraResult = camera ? "�ɹ�" : "ʧ��";
	m_csMicResult = mic ? "�ɹ�" : "ʧ��";
	m_csSpeakerResult = speaker ? "�ɹ�" : "ʧ��";
	UpdateData(false);
	return;
}
