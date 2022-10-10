#pragma once
#include "framework.h"
#include "GitUploader.h"
#include "InitFrame.h"


class initFileManager {
private:
public:
	static CString gitURL;
	static CString defaultBackupURL;
	static CString autoBackupMessage;

	static BOOL loadInit();
	static BOOL saveInit();
};