#pragma once

//#include "pch.h"
//#include "framework.h"
//#include "GitProjectManager.h"
#include <fstream>
#include <iostream>

class GitUploader
{
private:
	CStringArray filePathArr; //���ϰ�� �迭
	int filePathArrCount = 0;
	CString toolPath; //������ ���
	CString projName; //������Ʈ��
	CString dirPath; //������Ʈ�� ���丮 ���
	CString backupRepo; //������Ʈ�� ����� ����� �ּ�
public:
	static CArray<GitUploader*> projList; //��� ������Ʈ ��ü���� ���ִ� ���
	static GitUploader* getProj(CString projName); //�ش� ������Ʈ�̸��� ���� ��ü ã�Ƽ� ������ ����

	GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo); //�ϳ��� ������Ʈ, �ϳ��� ������Ʈ
	void addFile(CString filePath); //���ϸ�� �迭�� ���� �߰�
	BOOL gitUpload(); //���� ��ü�� ������ ������� filePathArr�� �ִ� ��� ������ ���ε�

	//get�Լ� ���
	CString getProjName() {
		return projName;
	}
	CString getDirPath() {
		return dirPath;
	}
	CString getBackupRepo() {
		return backupRepo;
	}
	CString getToolPath() {
		return toolPath;
	}
	CString getFilePath(int n) {
		if(n < filePathArr.GetCount())
			return filePathArr[n];
		return NULL;
	}
	int getFilePathArrCount() {
		return filePathArrCount;
	}
};