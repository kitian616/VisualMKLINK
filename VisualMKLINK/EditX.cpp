// EditX.cpp : 实现文件
//

#include "stdafx.h"
#include "VisualMKLINK.h"
#include "EditX.h"


// CEditX

IMPLEMENT_DYNAMIC(CEditX, CEdit)

CEditX::CEditX()
{

}

CEditX::~CEditX()
{
}


BEGIN_MESSAGE_MAP(CEditX, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CEditX 消息处理程序




void CEditX::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	WCHAR wcStr[MAX_PATH];
	DragQueryFile(hDropInfo, 0, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
	SetWindowText(wcStr);
	UpdateData(FALSE);
	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CEdit::OnDropFiles(hDropInfo);
}
