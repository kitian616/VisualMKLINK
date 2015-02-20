#pragma once


// CListBoxWithMenu

class CListBoxX : public CListBox
{
	DECLARE_DYNAMIC(CListBoxX)

public:
	CListBoxX();
	virtual ~CListBoxX();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuDelete();
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnRbuttondown(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnNull32774();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


