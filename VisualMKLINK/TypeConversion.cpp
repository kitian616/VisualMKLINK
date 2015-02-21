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
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = str.GetLength();
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP, 0, str, n, pChar, len + 1, NULL, NULL);
	pChar[len] = '\0';   //多字节字符以'\0'结束

}
void TypeConversion::TChar2CString(const TCHAR* pTChar, CString& str)
{
	str.Format(_T("%s"), pTChar);
}
void TypeConversion::Char2CString(const char* pChar, CString& str)
{
	int charLen = strlen(pChar); //计算pChar所指向的字符串大小，以字节为单位，一个汉字占两个字节  
	int len = MultiByteToWideChar(CP_ACP, 0, pChar, charLen, NULL, 0); //计算多字节字符的大小，按字符计算  
	TCHAR *pTChar = new wchar_t[len + 1]; //为宽字节字符数申请空间，  
	MultiByteToWideChar(CP_ACP, 0, pChar, charLen, pTChar, len); //多字节编码转换成宽字节编码  
	pTChar[len] = '\0';

	//将wchar_t数组转换为CString
	TChar2CString(pTChar, str);
	//cstring str;
	//str.append(ptchar);
	delete(pTChar);
}
