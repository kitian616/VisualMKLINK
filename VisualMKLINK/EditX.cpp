// EditX.cpp : ʵ���ļ�
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



// CEditX ��Ϣ�������




void CEditX::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WCHAR wcStr[MAX_PATH];
	DragQueryFile(hDropInfo, 0, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
	SetWindowText(wcStr);
	UpdateData(FALSE);
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CEdit::OnDropFiles(hDropInfo);
}
