
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
	m_lstTarget.AddString(_T("Drop the TARGRT Files HEAR! Right Mouse-click for More Functions."));
	m_edtLink.SetWindowTextW(_T("Drop the LINK File HEAR!"));
	m_lstTarget.SetClearable();

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
	BackgroundOperations bgo;
	UpdateData(TRUE);
	//��ղ���
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
			cmd += _T('\"') + targetPath.GetFilePathString() + _T('\"');		//�ļ���Ӳ����
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


