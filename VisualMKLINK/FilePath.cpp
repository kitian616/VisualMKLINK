#include "stdafx.h"
#include "FilePath.h"


FilePath::FilePath()
{
}

FilePath::FilePath(CString filePath)
{
	m_filePath = filePath;
}
FilePath::~FilePath()
{
}

BOOL FilePath::Exists()
{
	//winapi
	/*TCHAR szFilePath[_MAX_PATH];
	TypeConversion::CString2TChar(m_filePath, szFilePath);*/
	return PathFileExists(m_filePath);
}

BOOL FilePath::IsDirectory()
{
	return PathIsDirectory(m_filePath);
}

BOOL FilePath::IsFile()
{
	return PathIsFileSpec(m_filePath);
}

FilePath FilePath::GetParentPath()
{
	FilePath parentPath;
	RemoveBackslash();
	int pos = m_filePath.ReverseFind('\\');
	parentPath = m_filePath.Left(pos);
	return parentPath;
}

void FilePath::RemoveBackslash()
{
	int filePathLen = m_filePath.GetLength();
	if (m_filePath.GetAt(filePathLen - 1) == '\\')
	{
		m_filePath.Delete(filePathLen - 1);
	}
}

