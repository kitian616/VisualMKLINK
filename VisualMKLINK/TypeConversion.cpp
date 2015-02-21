#include "stdafx.h"
#include "TypeConversion.h"


TypeConversion::TypeConversion()
{
}


TypeConversion::~TypeConversion()
{
}

void TypeConversion::CString2TChar(const CString& str, TCHAR* pTchar)
{
	CString temStr = str;
	int strLen = temStr.GetLength();
	lstrcpy(pTchar, temStr.GetBuffer(strLen));
	temStr.ReleaseBuffer();
}
void TypeConversion::CString2Char(const CString& str, char* pChar)
{
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
	int n = str.GetLength();
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
	//���ֽڱ���ת���ɶ��ֽڱ���
	WideCharToMultiByte(CP_ACP, 0, str, n, pChar, len + 1, NULL, NULL);
	pChar[len] = '\0';   //���ֽ��ַ���'\0'����

}
void TypeConversion::TChar2CString(const TCHAR* pTChar, CString& str)
{
	str.Format(_T("%s"), pTChar);
}
void TypeConversion::Char2CString(const char* pChar, CString& str)
{
	int charLen = strlen(pChar); //����pChar��ָ����ַ�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�  
	int len = MultiByteToWideChar(CP_ACP, 0, pChar, charLen, NULL, 0); //������ֽ��ַ��Ĵ�С�����ַ�����  
	TCHAR *pTChar = new wchar_t[len + 1]; //Ϊ���ֽ��ַ�������ռ䣬  
	MultiByteToWideChar(CP_ACP, 0, pChar, charLen, pTChar, len); //���ֽڱ���ת���ɿ��ֽڱ���  
	pTChar[len] = '\0';

	//��wchar_t����ת��ΪCString
	TChar2CString(pTChar, str);
	//cstring str;
	//str.append(ptchar);
	delete(pTChar);
}
