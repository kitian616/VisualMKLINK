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
	ON_COMMAND(ID_MENU0_DELETE, &CListBoxX::OnMenu0Delete)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MENU0_CLEARALL, &CListBoxX::OnMenu0Clearall)
END_MESSAGE_MAP()


void CListBoxX::SetClearable()
{
	m_clearable = true;
}

/*CListBoxWithMenu 消息处理程序*/

/*鼠标右键点击ListBox string 时，弹出菜单*/
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

	/*当m_clearFlag为true，清空数据*/
	if (m_clearable)
	{
		ResetContent();
		m_clearable = false;
	}

	INT DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	WCHAR wcStr[MAX_PATH];
	for (int i = 0; i < DropCount; i++)
	{
		bool exist = FALSE;		//文件不存在
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名

		/*除掉同名文件*/
		for (int j = 0; j < GetCount(); j++)
		{
			CString listText = NULL;
			GetText(j, listText);
			if (wcStr == listText)
			{
				exist = TRUE;
			}

		}
		if (!exist)
		{
			AddString(wcStr);
		}
	}

	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CListBox::OnDropFiles(hDropInfo);
}


void CListBoxX::OnMenu0Delete()
{
	// TODO:  在此添加命令处理程序代码
	int listBoxIndex;
	listBoxIndex = GetCurSel();
	if (listBoxIndex == CB_ERR)
	{
		MessageBox(_T("请选中一个记录"));
	}
	else
	{
		//删除listbox 中的记录
		DeleteString(listBoxIndex);
	}
}

void CListBoxX::OnMenu0Clearall()
{
	// TODO:  在此添加命令处理程序代码
	ResetContent();	//清空ListBox
}
