
// 3TLiveDemoDlg.cpp : 实现文件
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
C3TEngineEventHandler g_3TEngineEventHandler; 
C3TLocalUserInfo g_LocalUser;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy3TLiveDemoDlg 对话框




CMy3TLiveDemoDlg::CMy3TLiveDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3TLiveDemoDlg::IDD, pParent)
	, m_sRoomID(_T("1231"))
	, m_ClientRole(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3TLiveDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROOMID, m_sRoomID);
	//  DDX_Radio(pDX, IDC_RADIO_M, m_radClientRole);
	//  DDV_MinMaxInt(pDX, m_radClientRole, 1, 3);
	DDX_Radio(pDX, IDC_RADIO_M, m_ClientRole);
	DDV_MinMaxInt(pDX, m_ClientRole, 0, 2);
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
	ON_BN_CLICKED(IDC_BTNSETTING, &CMy3TLiveDemoDlg::OnBnClickedBtnsetting)
	ON_BN_CLICKED(IDC_BTNDEVICETEST, &CMy3TLiveDemoDlg::OnBnClickedBtndevicetest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMy3TLiveDemoDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_BTNDEVICETEST2, &CMy3TLiveDemoDlg::OnBnClickedBtnNewChannelNum)
END_MESSAGE_MAP()


// CMy3TLiveDemoDlg 消息处理程序

BOOL CMy3TLiveDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	RtcEngineContext context;
	g_TTTEngine = IRtcEngine::createInstance();
	//return TRUE;


	if (g_TTTEngine != NULL)
	{
		g_3TEngineEventHandler.SetMsgReceiver(GetSafeHwnd());
		context.eventHandler = &g_3TEngineEventHandler;

		int res = g_TTTEngine->initialize(context);
		if (res == 0)
		{
			//初始化成功？
			g_TTTEngine->setAppID(g_LocalUser.m_sAppID.c_str());
			g_TTTEngine->setVideoMixerBackgroundImgUrl("http://3ttech.cn/res/tpl/default/images/bk.png");

			int count = IVideoDevice::getCount();
			g_LocalUser.m_vDeviceCount = count;
			for (int i = 0; i < count; i++)
			{
				IVideoDevice::getInfo(i, &g_LocalUser.m_vDeviceArray[i]);
			}

		}

	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy3TLiveDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy3TLiveDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy3TLiveDemoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	OnEnKillfocusEditRoomid();

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
	// TODO: 校验会议id，必须是数字
	this->UpdateData(TRUE);
	std::string strvalue = this->m_sRoomID.GetBuffer(0);
	if (!isdigit(strvalue))
		MessageBox(strvalue.data(), "请输入正确的数字！");
	else
		g_LocalUser.m_roomID = strvalue;
}



void CMy3TLiveDemoDlg::OnClickedRadioM()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CMySetting dlg;
	dlg.DoModal();
}


void CMy3TLiveDemoDlg::OnBnClickedBtndevicetest()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDlg dlg;
	dlg.DoModal();
}


void CMy3TLiveDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	static bool started = false;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
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
