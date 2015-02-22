#pragma once


// CListBoxWithMenu

class CListBoxX : public CListBox
{
	DECLARE_DYNAMIC(CListBoxX)

private:
	bool m_clearable;	//Ϊtrueʱ����һ�����������string��Ȼ���Զ���Ϊfalse.

public:
	CListBoxX();
	virtual ~CListBoxX();

public:
	void SetClearable();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg LRESULT OnRbuttondown(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenu0Delete();
	afx_msg void OnMenu0Clearall();
};


