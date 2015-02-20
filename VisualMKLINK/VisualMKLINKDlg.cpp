
// VisualMKLINKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisualMKLINK.h"
#include "VisualMKLINKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisualMKLINKDlg �Ի���



CVisualMKLINKDlg::CVisualMKLINKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisualMKLINKDlg::IDD, pParent)
	, m_szResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_APP);
	InitUIPIFilter();
}

void CVisualMKLINKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TARGET, m_IDC_Target);
	DDX_Control(pDX, IDC_EDIT_LINK, m_IDC_Link);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_szResult);
}

BEGIN_MESSAGE_MAP(CVisualMKLINKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MKLINK, &CVisualMKLINKDlg::OnBnClickedButtonMklink)
END_MESSAGE_MAP()


// CVisualMKLINKDlg ��Ϣ�������&

BOOL CVisualMKLINKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVisualMKLINKDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVisualMKLINKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVisualMKLINKDlg::OnBnClickedButtonMklink()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < m_IDC_Target.GetCount(); i++)
	{
		CString targetPath;
		m_IDC_Target.GetText(i, targetPath);
		if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(targetPath))
		{
			MessageBox(_T("·�������ڣ�"));
			break;
		}
		else if (FILE_ATTRIBUTE_DIRECTORY == GetFileAttributes(targetPath))
		{
			targetPath += "";
		}
		CString linkPath;
		m_IDC_Link.GetWindowTextW(linkPath);
		CString cmd = _T("mklink /D \"") + linkPath + _T("\"  \"") + targetPath + _T("\"");
		m_szResult = BackgroundOperations::ExecuteCMD(cmd);
		UpdateData(FALSE);

	}
	
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
