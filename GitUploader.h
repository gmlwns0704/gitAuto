#pragma once

//#include "pch.h"
//#include "framework.h"
//#include "GitProjectManager.h"
//#include <fstream>
//#include <iostream>
#include<string>
typedef std::string string;

class GitUploader
{
private:
	CArray<string> filePathArr; //파일경로 배열
	int filePathArrCount = 0;
	string branch; //branch
	string projName; //프로젝트명
	string dirPath; //프로젝트의 디렉토리 경로
	string backupRepo; //프로젝트가 저장될 깃허브 주소
public:
	static CArray<GitUploader*> projList; //모든 프로젝트 객체들이 모여있는 목록
	static GitUploader* getProj(string  projName); //해당 프로젝트이름을 가진 객체 찾아서 포인터 리턴
	static GitUploader* getProj(CString  projName);
	static BOOL uploadAll();
	static void infoAll();

	GitUploader(string  dirPath, string  projName, string  branch, string  backupRepo); //하나의 프로젝트, 하나의 오브젝트
	GitUploader(CString  dirPath, CString  projName, CString  branch, CString  backupRepo);
	BOOL addFile(string  filePath); //파일목록 배열에 파일 추가
	BOOL addFile(CString  filePath);
	BOOL rmFile(string filePath); //파일 목록 배열에서 파일 제거
	BOOL rmFile(CString filePath);
	BOOL gitUpload(); //현재 객체의 정보를 기반으로 filePathArr에 있는 모든 파일을 업로드
	BOOL addAllExt(string  extension);
	BOOL addAllExt(CString  extension);
	void Info();

	string getProjName();
	string getDirPath();
	string getBranch();
	string getBackupRepo();
	int getFilePathArrCount();
	string getFilePath(int n);
};