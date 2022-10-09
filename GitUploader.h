#pragma once

//#include "pch.h"
//#include "framework.h"
//#include "GitProjectManager.h"
#include <fstream>
#include <iostream>

class GitUploader
{
private:
	CStringArray filePathArr; //파일경로 배열
	CString toolPath; //개발툴 경로
	CString projName; //프로젝트명
	CString dirPath; //프로젝트의 디렉토리 경로
	CString backupRepo; //프로젝트가 저장될 깃허브 주소
public:
	static CArray<GitUploader*> projList; //모든 프로젝트 객체들이 모여있는 목록
	static GitUploader* getProj(CString projName); //해당 프로젝트이름을 가진 객체 찾아서 포인터 리턴

	GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo); //하나의 프로젝트, 하나의 오브젝트
	void addFile(CString filePath); //파일목록 배열에 파일 추가
	BOOL gitUpload(); //현재 객체의 정보를 기반으로 filePathArr에 있는 모든 파일을 업로드

	//get함수 목록
	CString getProjName() {
		return this->projName;
	}
	CString getDirPath() {
		return this->dirPath;
	}
	CString getBackupRepo() {
		return this->backupRepo;
	}
	CString getToolPath() {
		return this->toolPath;
	}
};