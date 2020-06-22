// DialogWindowId.cpp : 实现文件
//

#include "stdafx.h"
#include "3TLiveDemo.h"
#include "DialogWindowId.h"
#include "afxdialogex.h"


// CDialogWindowId 对话框

IMPLEMENT_DYNAMIC(CDialogWindowId, CDialogEx)

CDialogWindowId::CDialogWindowId(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_WINDOWID, pParent)
{

}

CDialogWindowId::~CDialogWindowId()
{
}

void CDialogWindowId::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialogWindowId, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogWindowId::OnBnClickedOk)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD           i;
    RECT			r;
    CHAR            buf[MAX_PATH];
    PTASK_LIST_ENUM te = (PTASK_LIST_ENUM)lParam;
    PTASK_LIST      tlist = te->tlist;
    DWORD           numTasks = te->numtasks;

    i = 1 + tlist[0].dwProcessId;
    // max 255 windows (I think it's enough)
    if (i < 255) {

        // Skip windows that are invisible, minimized, have no title, or are owned,
        // unless they have the app window style set.
        int len = GetWindowTextLength(hwnd);
        HWND owner = GetWindow(hwnd, GW_OWNER);
        LONG exstyle = GetWindowLong(hwnd, GWL_EXSTYLE);
        if (len == 0 || IsIconic(hwnd) || !IsWindowVisible(hwnd) ||
            (owner && !(exstyle & WS_EX_APPWINDOW))) {
            return TRUE;
        }
        // Skip unresponsive windows. Set timout with 50ms, in case system is under
        // heavy load, the check can wait longer but wont' be too long to delay the
        // the enumeration.
        const UINT uTimeout = 50;  // ms
        if (!SendMessageTimeout(hwnd, WM_NULL, 0, 0, SMTO_ABORTIFHUNG, uTimeout,
            nullptr)) {
            return TRUE;
        }

        // Skip the Program Manager window and the Start button.
        const size_t kClassLength = 256;
        WCHAR class_name[kClassLength];
        const int class_name_length = GetClassNameW(hwnd, class_name, kClassLength);

        // Skip Program Manager window and the Start button. This is the same logic
        // that's used in Win32WindowPicker in libjingle. Consider filtering other
        // windows as well (e.g. toolbars).
        if (wcscmp(class_name, L"Progman") == 0 || wcscmp(class_name, L"Button") == 0)
            return TRUE;

        if ((wcscmp(class_name, L"ApplicationFrameWindow") == 0 ||
                wcscmp(class_name, L"Windows.UI.Core.CoreWindow") == 0)) {
            return TRUE;
        }
        {
            GetClientRect(hwnd, &r);
            // discard strange windows
            if (r.right > 4 && r.bottom > 4) {
                // get the window caption
                if (GetWindowText(hwnd, buf, sizeof(buf))) {
                    tlist[i].hwnd = hwnd;				 // store hwnd
                    strcpy(tlist[i].WindowTitle, buf); // store caption
                    tlist[0].dwProcessId++;
                }
            }
        }
    }
    return TRUE;
}
// CDialogWindowId 消息处理程序
BOOL CDialogWindowId::OnInitDialog()
{
    CDialog::OnInitDialog();
    TASK_LIST   tlist[256];
    tlist[0].dwProcessId = 0;
    TASK_LIST_ENUM    te;
    // task list
    te.tlist = tlist;
    // get the windows
    EnumWindows(EnumWindowsProc, (LPARAM)(&te));
    int idx;
    // always add the desktop

    int numtasks = tlist[0].dwProcessId;
    // fill the list with the other windows
    for (int i = 1; i < numtasks; i++) {
        idx = m_list.InsertString(-1, tlist[i].WindowTitle);
        m_list.SetItemData(idx, (DWORD)tlist[i].hwnd);
    }
    // default selection
    m_list.SetCurSel(0);
    return TRUE;

}

void CDialogWindowId::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);
    int idx = m_list.GetCurSel();
    m_SelectedWnd = (HWND)m_list.GetItemData(idx);
	CDialogEx::OnOK();
}
