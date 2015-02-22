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

bool FilePath::Exists()
{
	//winapi
	/*TCHAR szFilePath[_MAX_PATH];
	TypeConversion::CString2TChar(m_filePath, szFilePath);*/
	return PathFileExists(m_filePath);
}

bool FilePath::IsDirectory()
{
	//return PathIsDirectory(m_filePath);
	CString fileName = GetName();
	return (-1 == fileName.Find('.'));

}

bool FilePath::IsFile()
{
	//return PathIsFileSpec(m_filePath);
	return !IsDirectory();
}

FilePath FilePath::GetParent()
{
	FilePath parentPath;
	RemoveBackslash();
	int pos = m_filePath.ReverseFind('\\');
	parentPath.SetFilePathString(m_filePath.Left(pos));
	return parentPath;
}

CString FilePath::GetName()
{
	CString fileName;
	RemoveBackslash();
	int pos = m_filePath.ReverseFind('\\');
	fileName = m_filePath.Right(m_filePath.GetLength() - pos -1);
	return fileName;
}

void FilePath::RemoveBackslash()
{
	int filePathLen = m_filePath.GetLength();
	if (m_filePath.GetAt(filePathLen - 1) == '\\')
	{
		m_filePath.Delete(filePathLen - 1);
	}
}

//FilePath FilePath::operator + (FilePath &filePath) const
//{
//	CString lastFilePath = m_filePath + filePath.GetFilePathString();
//	return FilePath(lastFilePath);
//}
bool FilePath::operator == (FilePath &filePath) const
{
	return (m_filePath == filePath.GetFilePathString());
}

