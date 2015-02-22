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
	void SetFilePathString(CString filePath)
	{
		m_filePath = filePath;
	}

	CString GetFilePathString()
	{
		return m_filePath;
	}

public:
	bool Exists();		//判断路径是否存在
	bool IsDirectory();	//判断是否为目录
	bool IsFile();
	FilePath GetParent();	//得到上一级目录
	CString GetName();		//得到文件（文件夹）名
	void RemoveBackslash();	//去除路径末尾的反斜线

public:
	//FilePath operator+ (FilePath &filePath) const;
	bool operator== (FilePath &filePath) const;
};

