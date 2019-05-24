#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Common.h"


// CSpeakerTesting �Ի���

class CSpeakerTesting : public CDialogEx
{
	DECLARE_DYNAMIC(CSpeakerTesting)

public:
	CSpeakerTesting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpeakerTesting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderVolumeSetting;
	CComboBox m_comboSpeakerEnum;
	CString m_csSpeakerName;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSpeaker();
	afx_msg void OnBnClickedPlayMusic();
	afx_msg void OnThemechangedSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnThumbposchangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DEVICEIDMAP m_mapDeviceIDs;

	afx_msg void OnBnClickedMfcbutton1();
};