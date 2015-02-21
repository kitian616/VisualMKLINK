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
	/*����WIN APIʵ��*/
	BOOL Exists();		//�ж�·���Ƿ����
	BOOL IsDirectory();	//�ж��Ƿ�ΪĿ¼��·��ΪĿ¼���Ҵ���ʱΪ��
	BOOL IsFile();
	FilePath GetParentPath();
	void RemoveBackslash();
};

