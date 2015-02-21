#include "stdafx.h"
#include "BackgroundOperations.h"


BackgroundOperations::BackgroundOperations()
{
}


BackgroundOperations::~BackgroundOperations()
{
}


void BackgroundOperations::CString2TChar(CString& str, TCHAR* pTchar)
{
	int strLen = str.GetLength();
	lstrcpy(pTchar, str.GetBuffer(strLen));
	str.ReleaseBuffer();
}
void BackgroundOperations::CString2Char(CString& str, char* pChar)
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
void BackgroundOperations::TChar2CString(TCHAR* pTChar, CString& str)
{
	str.Format(_T("%s"), pTChar);
}
void BackgroundOperations::Char2CString(char* pChar, CString& str)
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

CString BackgroundOperations::ExecuteCommandLine(CString commandLine)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(NULL, _T("Error on CreatePipe()!"), _T("提示"), MB_OK);  //TODO
		return NULL;
	}
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	//si.wShowWindow = SW_NORMAL;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	TCHAR pCommandLine[IF_MAX_STRING_SIZE];
	CString2TChar(commandLine, pCommandLine);
	if (!CreateProcess(NULL, pCommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		MessageBox(NULL, _T("Error on CreateProcess()!"), _T("提示"), MB_OK);		//TODO
		return NULL;
	}
	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer, 0, 4096);
	CString output;
	DWORD byteRead;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &byteRead, NULL) == NULL)
		{
			break;
		}
		output += buffer;
	}
	return output;
}

CString BackgroundOperations::ExecuteCMD(CString cmdCommand)
{
	CString commandLine = _T("cmd.exe /C ") + cmdCommand;
	return BackgroundOperations::ExecuteCommandLine(commandLine);
}
