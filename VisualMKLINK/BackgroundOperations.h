#pragma once
class BackgroundOperations
{
public:
	BackgroundOperations();
	~BackgroundOperations();

	void CString2TChar(CString& str, TCHAR* pTchar);
	void CString2Char(CString& str, char* pChar);
	void TChar2CString(TCHAR* pTchar, CString& str);
	void Char2CString(char* pChar, CString& str);

	CString ExecuteCommandLine(CString commandLine);
	CString ExecuteCMD(CString cmdCommand);
	
};

