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
	bool Exists();		//�ж�·���Ƿ����
	bool IsDirectory();	//�ж��Ƿ�ΪĿ¼
	bool IsFile();
	FilePath GetParent();	//�õ���һ��Ŀ¼
	CString GetName();		//�õ��ļ����ļ��У���
	void RemoveBackslash();	//ȥ��·��ĩβ�ķ�б��

public:
	//FilePath operator+ (FilePath &filePath) const;
	bool operator== (FilePath &filePath) const;
};

