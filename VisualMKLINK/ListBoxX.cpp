// ListBoxWithMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "VisualMKLINK.h"
#include "ListBoxX.h"


// CListBoxWithMenu

IMPLEMENT_DYNAMIC(CListBoxX, CListBox)

CListBoxX::CListBoxX()
{

}

CListBoxX::~CListBoxX()
{
}


BEGIN_MESSAGE_MAP(CListBoxX, CListBox)
	ON_COMMAND(ID_MENU0_DELETE, &CListBoxX::OnMenuDelete)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CListBoxWithMenu 消息处理程序




void CListBoxX::OnMenuDelete()
{
	// TODO:  在此添加命令处理程序代码
	int listBox_index;
	listBox_index = GetCurSel();
	if (listBox_index == CB_ERR)
	{
		MessageBox(_T("请选中一个记录"));
	}
	else
	{
		//删除listbox 中的记录
		DeleteString(listBox_index);

	}
}



BOOL CListBoxX::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (WM_RBUTTONUP == pMsg->message)
	{
		CPoint pt;
		CRect rtClient;
		GetClientRect(&rtClient);
		ClientToScreen(&rtClient);
		INT iScrollPos = GetScrollPos(SB_VERT);
		GetCursorPos(&pt);
		int iSelect = (pt.y - rtClient.top + iScrollPos * GetItemHeight(0)) / GetItemHeight(0);
		//CString st=_T("");  
		//st.Format(_T("%d"),iSelect);  
		//::AfxMessageBox(st);  
		SetCurSel(iSelect);
		RedrawWindow();
		if (rtClient.PtInRect(pt) && iSelect<GetCount())
		{
			CMenu MyMenu;
			MyMenu.LoadMenu(IDR_MENU_LISTBOX);
			MyMenu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
			MyMenu.Detach();//Detaches a Windows menu from a CMenu object and returns the handle  
		}
	}
	return CListBox::PreTranslateMessage(pMsg);
}

void CListBoxX::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	INT DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	WCHAR wcStr[MAX_PATH];
	for (int i = 0; i < DropCount; i++)
	{
		bool exit = FALSE;		//文件不存在
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
		//同名文件只显示一次
		for (int j = 0; j < GetCount(); j++)
		{
			CString listText = NULL;
			GetText(j, listText);
			if (wcStr == listText)
			{
				exit = TRUE;
			}

		}
		if (!exit)
		{
			AddString(wcStr);
		}
	}

	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CListBox::OnDropFiles(hDropInfo);
}
