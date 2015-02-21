#pragma once

#include "TypeConversion.h"

class BackgroundOperations
{
public:
	BackgroundOperations();
	~BackgroundOperations();

	CString ExecuteCommandLine(CString commandLine);
	CString ExecuteCMD(CString cmdCommand);
	
};