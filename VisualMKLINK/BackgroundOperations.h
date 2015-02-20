#pragma once
class BackgroundOperations
{
public:
	BackgroundOperations();
	~BackgroundOperations();

	static TCHAR* StringToChar(CString& str);
	static CString ExecuteCommandLine(CString CommandLine);
	static CString ExecuteCMD(CString CommandLine);
};

