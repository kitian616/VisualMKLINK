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
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
	int n = str.GetLength();
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
	//���ֽڱ���ת���ɶ��ֽڱ���
	WideCharToMultiByte(CP_ACP, 0, str, n, pChar, len + 1, NULL, NULL);
	pChar[len] = '\0';   //���ֽ��ַ���'\0'����

}
void BackgroundOperations::TChar2CString(TCHAR* pTChar, CString& str)
{
	str.Format(_T("%s"), pTChar);
}
void BackgroundOperations::Char2CString(char* pChar, CString& str)
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

CString BackgroundOperations::ExecuteCommandLine(CString commandLine)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(NULL, _T("Error on CreatePipe()!"), _T("��ʾ"), MB_OK);  //TODO
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
		MessageBox(NULL, _T("Error on CreateProcess()!"), _T("��ʾ"), MB_OK);		//TODO
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
