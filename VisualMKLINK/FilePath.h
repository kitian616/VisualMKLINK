#pragma once

#include "TypeConversion.h"
class FilePath
{
public:
	FilePath();
	FilePath(CString filePath);
	~FilePath();

private:
	CString m_filePath;

public:
	void SetFilePath(CString filePath)
	{
		m_filePath = filePath;
	}

	CString GetFilePath()
	{
		return m_filePath;
	}

public:
	/*调用WIN API实现*/
	BOOL Exists();		//判断路径是否存在
	BOOL IsDirectory();	//判断是否为目录，路径为目录，且存在时为真
	BOOL IsFile();
	FilePath GetParentPath();
	void RemoveBackslash();
};

