#include "stdafx.h"
#include "BackgroundOperations.h"


BackgroundOperations::BackgroundOperations()
{
}


BackgroundOperations::~BackgroundOperations()
{
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
	TCHAR szCommandLine[IF_MAX_STRING_SIZE];
	TypeConversion::CString2TChar(commandLine, szCommandLine);
	if (!CreateProcess(NULL, szCommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
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
