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
	CArray<string> filePathArr; //���ϰ�� �迭
	int filePathArrCount = 0;
	string branch; //branch
	string projName; //������Ʈ��
	string dirPath; //������Ʈ�� ���丮 ���
	string backupRepo; //������Ʈ�� ����� ����� �ּ�
public:
	static CArray<GitUploader*> projList; //��� ������Ʈ ��ü���� ���ִ� ���
	static GitUploader* getProj(string  projName); //�ش� ������Ʈ�̸��� ���� ��ü ã�Ƽ� ������ ����
	static GitUploader* getProj(CString  projName);
	static BOOL uploadAll();
	static void infoAll();

	GitUploader(string  dirPath, string  projName, string  branch, string  backupRepo); //�ϳ��� ������Ʈ, �ϳ��� ������Ʈ
	GitUploader(CString  dirPath, CString  projName, CString  branch, CString  backupRepo);
	BOOL addFile(string  filePath); //���ϸ�� �迭�� ���� �߰�
	BOOL addFile(CString  filePath);
	BOOL rmFile(string filePath); //���� ��� �迭���� ���� ����
	BOOL rmFile(CString filePath);
	BOOL gitUpload(); //���� ��ü�� ������ ������� filePathArr�� �ִ� ��� ������ ���ε�
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