
// VisualMKLINKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisualMKLINK.h"
#include "VisualMKLINKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisualMKLINKDlg 对话框



CVisualMKLINKDlg::CVisualMKLINKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisualMKLINKDlg::IDD, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_APP);
	InitUIPIFilter();
}

void CVisualMKLINKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TARGET, m_lstTarget);
	DDX_Control(pDX, IDC_EDIT_LINK, m_edtLink);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CVisualMKLINKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MKLINK, &CVisualMKLINKDlg::OnBnClickedButtonMklink)
END_MESSAGE_MAP()


// CVisualMKLINKDlg 消息处理程序&

BOOL CVisualMKLINKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_lstTarget.AddString(_T("Drop the TARGRT Files HEAR! Right Mouse-click for More Functions."));
	m_edtLink.SetWindowTextW(_T("Drop the LINK File HEAR!"));
	m_lstTarget.SetClearable();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVisualMKLINKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVisualMKLINKDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVisualMKLINKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVisualMKLINKDlg::OnBnClickedButtonMklink()
{
	// TODO:  在此添加控件通知处理程序代码
	BackgroundOperations bgo;
	UpdateData(TRUE);
	//清空操作
	m_strResult = _T("");

	if (0 == m_lstTarget.GetCount())
	{
		m_strResult += _T("0. ERROR: Target path not exist!\r\n");
		UpdateData(FALSE);
		return;
	}

	for (int i = 0; i < m_lstTarget.GetCount(); i++)
	{
		CString cmd;
		CString curNum;  //int i to CString
		curNum.Format(_T("%d. "), i + 1);

		CString targetPathString;
		m_lstTarget.GetText(i, targetPathString);
		FilePath targetPath(targetPathString);

		CString linkPathString;
		m_edtLink.GetWindowTextW(linkPathString);
		FilePath linkPath(linkPathString);

		if (!targetPath.Exists())
		{
			m_strResult += curNum + _T("ERROR: Target path not exist!\r\n");
			UpdateData(FALSE);
			break;
		}
		if (targetPath == linkPath)
		{
			m_strResult += curNum + _T("ERROR: Path repetitions!\r\n");
			UpdateData(FALSE);
			continue;
		}

		if (targetPath.IsFile())
		{
			if (linkPath.IsFile())
			{
				if (!linkPath.GetParent().Exists())
				{
					m_strResult += curNum + _T("ERROR: Link path not exist!\r\n");
					UpdateData(FALSE);
					continue;
				}
			}
			else
			{
				if (!linkPath.Exists())
				{
					m_strResult += curNum + _T("ERROR: Link path not exist!\r\n");
					UpdateData(FALSE);
					continue;
				}
				else
				{
					linkPath.SetFilePathString(linkPath.GetFilePathString() + _T('\\') + targetPath.GetName());
					if (linkPath == targetPath)
					{
						m_strResult += curNum + _T("ERROR: Path repetitions!\r\n");
						UpdateData(FALSE);
						continue;
					}
				}
			}
			cmd = _T("mklink /H \"") + linkPath.GetFilePathString() + _T('\"');
			cmd += _T(' ');
			cmd += _T('\"') + targetPath.GetFilePathString() + _T('\"');		//文件的硬链接
		}
		else
		{
			if (linkPath.IsFile())
			{
				m_strResult += curNum + _T("ERROR: Can not link a direction to a file!\r\n");
				UpdateData(FALSE);
				continue;
			}
			else
			{
				if (linkPath.Exists())
				{
					linkPath.SetFilePathString(linkPath.GetFilePathString() + _T('\\') + targetPath.GetName());
					if (linkPath == targetPath)
					{
						m_strResult += curNum + _T("ERROR: Path repetitions!\r\n");
						UpdateData(FALSE);
						continue;
					}
				}
				else
				{
					if (!linkPath.GetParent().Exists())
					{
						m_strResult += curNum + _T("ERROR: Link path not exist!\r\n");
						UpdateData(FALSE);
						continue;
					}
				}
			}
			cmd = _T("mklink /D \"") + linkPath.GetFilePathString() + _T('\"');
			cmd += _T(' ');
			cmd += _T('\"') + targetPath.GetFilePathString() + _T('\"');
		}
		
		m_strResult += curNum + bgo.ExecuteCMD(cmd) + _T("\r\n");
		UpdateData(FALSE);
	}//END FOR
	
}


void CVisualMKLINKDlg::InitUIPIFilter()
{
	typedef BOOL(WINAPI *ChangeWindowMessageFilterProc)(UINT, DWORD);
	HMODULE hUser = LoadLibraryA("user32.dll");
	if (hUser)
	{
		ChangeWindowMessageFilterProc proc = (ChangeWindowMessageFilterProc)GetProcAddress(hUser, "ChangeWindowMessageFilter");
		if (proc)
		{
			proc(WM_COPYDATA, MSGFLT_ADD);
			proc(WM_DROPFILES, MSGFLT_ADD);
			proc(0x0049, MSGFLT_ADD);
		}
	}
}


