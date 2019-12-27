
// 3TLiveDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "3TLiveDemoDlg.h"
#include "LiveChatDlg.h"
#include "Common.h"
#include "C3TEngineEventHandler.h"
#include "Dialog2.h"
#include "C3TLocalUserInfo.h"
#include "MySetting.h"
#include "TestDlg.h"
#include "TTTRtcEngine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IRtcEngine* g_TTTEngine = NULL;
IRtcPlayer* mPlayer;
C3TEngineEventHandler g_3TEngineEventHandler; 
C3TLocalUserInfo g_LocalUser;
typedef int(*WSInstallCrashRpt)(LPCWSTR AppName, LPCWSTR AppVersion);


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy3TLiveDemoDlg �Ի���




CMy3TLiveDemoDlg::CMy3TLiveDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3TLiveDemoDlg::IDD, pParent)
	, m_sRoomID(_T("1231"))
	, m_ClientRole(1)
	, m_b_room_mode_communication(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3TLiveDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROOMID, m_sRoomID);
	//  DDX_Radio(pDX, IDC_RADIO_M, m_radClientRole);
	//  DDV_MinMaxInt(pDX, m_radClientRole, 1, 3);
	DDX_Text(pDX, IDC_STATIC_VER, m_sVer);

	DDX_Radio(pDX, IDC_RADIO_M, m_ClientRole);
	DDV_MinMaxInt(pDX, m_ClientRole, 0, 2);
	DDX_Check(pDX, IDC_CHECK_CHANNAL_MODE, m_b_room_mode_communication);
	//DDX_Control(pDX, IDC_CHECK1, m_chkUseHighQualityAudio);
	DDX_Control(pDX, IDC_RADIO_M, m_opt_ClientRoleM);
	DDX_Control(pDX, IDC_RADIO_C , m_opt_ClientRoleC);



}

BEGIN_MESSAGE_MAP(CMy3TLiveDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ON_JOINCHANNELSUCCESS, &CMy3TLiveDemoDlg::OnJoinChannelSuccess)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMy3TLiveDemoDlg::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_ROOMID, &CMy3TLiveDemoDlg::OnEnKillfocusEditRoomid)
	ON_BN_CLICKED(IDC_RADIO_M, &CMy3TLiveDemoDlg::OnClickedRadioM)
	ON_BN_CLICKED(IDC_RADIO_B, &CMy3TLiveDemoDlg::OnClickedRadioM)
	ON_BN_CLICKED(IDC_RADIO_C, &CMy3TLiveDemoDlg::OnClickedRadioM)
	ON_BN_CLICKED(IDC_RADIO_C2, &CMy3TLiveDemoDlg::OnClickedRadioM)

	

	ON_BN_CLICKED(IDC_BTNSETTING, &CMy3TLiveDemoDlg::OnBnClickedBtnsetting)
	ON_BN_CLICKED(IDC_BTNDEVICETEST, &CMy3TLiveDemoDlg::OnBnClickedBtndevicetest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMy3TLiveDemoDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_BTNDEVICETEST2, &CMy3TLiveDemoDlg::OnBnClickedBtnNewChannelNum)
	ON_BN_CLICKED(IDC_RADIO_C2, &CMy3TLiveDemoDlg::OnBnClickedRadioC2)
	ON_BN_CLICKED(IDC_CHECK_CHANNAL_MODE, &CMy3TLiveDemoDlg::OnBnClickedCheck1)

END_MESSAGE_MAP()


// CMy3TLiveDemoDlg ��Ϣ�������

BOOL CMy3TLiveDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	CEdit *p_Edit;
	p_Edit = (CEdit*)GetDlgItem(IDC_EDIT_ROOMID);
	p_Edit->SetLimitText(18); 

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	RtcEngineContext context;
	g_TTTEngine = IRtcEngine::createInstance();
	//return TRUE;


	HINSTANCE m_phDLLHdl = NULL;
	m_phDLLHdl = LoadLibrary("WS_CrashRpt1403.dll");  //���� DLL�ļ�  
	if (m_phDLLHdl) {
		WSInstallCrashRpt myCrashRpt = (WSInstallCrashRpt)GetProcAddress(m_phDLLHdl, "WSInstallCrashRpt");
		std::wstring version = L"Ver: "; 
		std::wstring sdk_ver = ws_techapi::utf82ws(g_TTTEngine->getVersion());
		version.append(sdk_ver.c_str());
		m_sVer = version.c_str();
		UpdateData(false);
		myCrashRpt(L"3TLiveDemo", sdk_ver.c_str());
	}


	if (g_TTTEngine != NULL)
	{
		g_3TEngineEventHandler.SetMsgReceiver(GetSafeHwnd());
		context.eventHandler = &g_3TEngineEventHandler;

		int res = g_TTTEngine->initialize(context);
		if (res == 0)
		{
			//��ʼ���ɹ���
			g_TTTEngine->setAppID(g_LocalUser.m_sAppID.c_str());
			//g_TTTEngine->setVideoMixerBackgroundImgUrl("http://3ttech.cn/res/tpl/default/images/bk.png");

			int count = IVideoDevice::getCount();
			g_LocalUser.m_vDeviceCount = count;
			for (int i = 0; i < count; i++)
			{
				IVideoDevice::getInfo(i, &g_LocalUser.m_vDeviceArray[i]);
			}

		}

	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy3TLiveDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy3TLiveDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy3TLiveDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy3TLiveDemoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	//OnEnKillfocusEditRoomid();
	std::string strvalue = this->m_sRoomID.GetBuffer(0);
	rid_ttt roomId = 0;
	try {
		roomId = _atoi64(strvalue.c_str());
	}
	catch (...) {
		roomId = 0;
	}
	if (0 == roomId) {
		MessageBox( "����ű����Ǵ���0��������");
		return;
	}

	g_LocalUser.m_roomID = roomId;

	CDialog2 dlg;
	dlg.m_bJoinChannel = true;
	g_LocalUser.m_cbMsgHandler = dlg.GetSafeHwnd();
	//dlg.ShowWindow(SW_SHOW);
	//dlg.joinChannel();
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		
	}

	if (g_TTTEngine != NULL)
	{
		//g_TTTEngine->setChannelProfile(g_LocalUser.m_channelProfile);

		//if (g_LocalUser.m_enableVideo)
		//	g_TTTEngine->enableVideo();
		//if (g_LocalUser.m_enableAudio)
		//	g_TTTEngine->enableAudio();
		//g_TTTEngine->setClientRole(g_LocalUser.m_clientRole, NULL);
		//std::string roomid = this->m_sRoomID.GetBuffer(0);

		//VideoCanvas_TTT vc;

		//vc.uid = 0;
		//CStatic   *pStatic = (CStatic*)GetDlgItem(IDC_STATIC3);
		//vc.view = pStatic->GetSafeHwnd();
		//vc.renderMode = RENDER_MODE_TYPE_TTT::RENDER_MODE_FIT_TTT;


		//g_TTTEngine->setupLocalVideo(vc);
		//g_TTTEngine->startPreview();

		//nReponse = g_TTTEngine->joinChannel("Omygode!", this->m_sRoomID.GetBuffer(0), 0);
	}

	_CrtDumpMemoryLeaks();
	return;
}


void CMy3TLiveDemoDlg::OnEnKillfocusEditRoomid()
{
	// TODO: У�����id������������
	this->UpdateData(TRUE);
}



void CMy3TLiveDemoDlg::OnClickedRadioM()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	g_LocalUser.m_clientRole = (CLIENT_ROLE_TYPE)(this->m_ClientRole + 1);
}

LRESULT CMy3TLiveDemoDlg::OnJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	//if (g_TTTEngine != NULL)
	//	g_TTTEngine->startPreview();
	return 0;
}


void CMy3TLiveDemoDlg::OnBnClickedBtnsetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMySetting dlg;
	dlg.DoModal();
}


void CMy3TLiveDemoDlg::OnBnClickedBtndevicetest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDlg dlg;
	dlg.DoModal();
}


void CMy3TLiveDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	static bool started = false;
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 125)
	{
		CDialog2 dlg;
		dlg.SDKTestTimer();
		dlg.m_bJoinChannel = true;
		g_LocalUser.m_cbMsgHandler = dlg.GetSafeHwnd();
		//dlg.SDKTestTimer
		this->KillTimer(125);
		dlg.DoModal();
		this->SetTimer(125, 3000, NULL);
		//dlg.KillSDKTimer();
	}

	CDialog::OnTimer(nIDEvent);
}


void CMy3TLiveDemoDlg::OnBnClickedMfcbutton1()
{
	static bool bJoin = true;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (bJoin)
		this->SetTimer(125, 3000, NULL);
	else
		this->KillTimer(125);
}


void CMy3TLiveDemoDlg::OnBnClickedBtnNewChannelNum()
{
	srand(time(0));
	int num = rand() ;
	srand(rand());
	num = num + rand();
	std::string uid = ws_techapi::llToString(num);

	this->m_sRoomID = uid.c_str();
	UpdateData(false);
}


void CMy3TLiveDemoDlg::OnBnClickedRadioC2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMy3TLiveDemoDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_b_room_mode_communication == 1) {
		UpdateData(FALSE);
		g_LocalUser.m_channelProfile = CHANNEL_PROFILE_COMMUNICATION;
		g_LocalUser.m_clientRole = (CLIENT_ROLE_TYPE)(this->m_ClientRole + 1);
	}
	else
	{
		g_LocalUser.m_channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
		g_LocalUser.m_clientRole = (CLIENT_ROLE_TYPE)(this->m_ClientRole + 1);
	}
}