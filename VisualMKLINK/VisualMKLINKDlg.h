
// VisualMKLINKDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ListBoxX.h"
#include "EditX.h"
#include "BackgroundOperations.h"
#include "TypeConversion.h"
#include "FilePath.h"


// CVisualMKLINKDlg 对话框
class CVisualMKLINKDlg : public CDialogEx
{
// 构造
public:
	CVisualMKLINKDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VISUALMKLINK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
