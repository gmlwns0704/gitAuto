#pragma once
#include "framework.h"
#include "GitUploader.h"
#include "pch.h"

class dataFileManager {
private:
public:
	static BOOL loadData(); //데이터파일 읽어오기
	static BOOL saveData(); //데이터파일 저장하기
};

