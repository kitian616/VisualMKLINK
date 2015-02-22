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
	ON_COMMAND(ID_MENU0_DELETE, &CListBoxX::OnMenu0Delete)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MENU0_CLEARALL, &CListBoxX::OnMenu0Clearall)
END_MESSAGE_MAP()


void CListBoxX::SetClearable()
{
	m_clearable = true;
}

/*CListBoxWithMenu ��Ϣ�������*/

/*����Ҽ����ListBox string ʱ�������˵�*/
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

	/*��m_clearFlagΪtrue���������*/
	if (m_clearable)
	{
		ResetContent();
		m_clearable = false;
	}

	INT DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	WCHAR wcStr[MAX_PATH];
	for (int i = 0; i < DropCount; i++)
	{
		bool exist = FALSE;		//�ļ�������
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���

		/*����ͬ���ļ�*/
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

	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CListBox::OnDropFiles(hDropInfo);
}


void CListBoxX::OnMenu0Delete()
{
	// TODO:  �ڴ���������������
	int listBoxIndex;
	listBoxIndex = GetCurSel();
	if (listBoxIndex == CB_ERR)
	{
		MessageBox(_T("��ѡ��һ����¼"));
	}
	else
	{
		//ɾ��listbox �еļ�¼
		DeleteString(listBoxIndex);
	}
}

void CListBoxX::OnMenu0Clearall()
{
	// TODO:  �ڴ���������������
	ResetContent();	//���ListBox
}
