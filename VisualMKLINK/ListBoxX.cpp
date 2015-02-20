// ListBoxWithMenu.cpp : ʵ���ļ�
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



// CListBoxWithMenu ��Ϣ�������




void CListBoxX::OnMenuDelete()
{
	// TODO:  �ڴ���������������
	int listBox_index;
	listBox_index = GetCurSel();
	if (listBox_index == CB_ERR)
	{
		MessageBox(_T("��ѡ��һ����¼"));
	}
	else
	{
		//ɾ��listbox �еļ�¼
		DeleteString(listBox_index);

	}
}



BOOL CListBoxX::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	INT DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	WCHAR wcStr[MAX_PATH];
	for (int i = 0; i < DropCount; i++)
	{
		bool exit = FALSE;		//�ļ�������
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
		//ͬ���ļ�ֻ��ʾһ��
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

	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CListBox::OnDropFiles(hDropInfo);
}
