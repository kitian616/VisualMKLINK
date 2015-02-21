#pragma once
class TypeConversion
{
public:
	TypeConversion();
	~TypeConversion();

	static void CString2TChar(const CString& str, TCHAR* pTchar);
	static void CString2Char(const CString& str, char* pChar);
	static void TChar2CString(const TCHAR* pTchar, CString& str);
	static void Char2CString(const char* pChar, CString& str);
};

