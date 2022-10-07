#pragma once

//#include "pch.h"
//#include "framework.h"
//#include "GitProjectManager.h"
#include <fstream>
#include <iostream>

class GitUploader
{
private:
public:
	GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo); //하나의 프로젝트, 하나의 오브젝트
	static CArray<GitUploader*> projList; //모든 프로젝트 객체들이 모여있는 목록
	void addFile(CString filePath); //파일목록 배열에 파일 추가
	BOOL gitUpload(); //현재 객체의 정보를 기반으로 filePathArr에 있는 모든 파일을 업로드

	CStringArray filePathArr; //파일경로 배열
	CString toolPath; //개발툴 경로
	CString projName; //프로젝트명
	CString dirPath; //프로젝트의 디렉토리 경로
	CString backupRepo; //프로젝트가 저장될 깃허브 주소
};