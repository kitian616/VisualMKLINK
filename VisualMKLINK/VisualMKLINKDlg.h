
// VisualMKLINKDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ListBoxX.h"
#include "EditX.h"
#include "BackgroundOperations.h"
#include "TypeConversion.h"
#include "FilePath.h"


// CVisualMKLINKDlg �Ի���
class CVisualMKLINKDlg : public CDialogEx
{
// ����
public:
	CVisualMKLINKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VISUALMKLINK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMklink();
	//afx_msg void OnDropFiles(HDROP hDropInfo);
private:
	CListBoxX m_IDC_Target;
	CEditX m_IDC_Link;
	CString m_strResult;
	void InitUIPIFilter();	
};
