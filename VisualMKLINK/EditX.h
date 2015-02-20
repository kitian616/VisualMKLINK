#pragma once


// CEditX

class CEditX : public CEdit
{
	DECLARE_DYNAMIC(CEditX)

public:
	CEditX();
	virtual ~CEditX();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


