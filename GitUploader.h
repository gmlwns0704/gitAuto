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
	CString toolPath; //������ ���
	CString projName; //������Ʈ��
	CString dirPath; //������Ʈ�� ���丮 ���
	CString backupRepo; //������Ʈ�� ����� ����� �ּ�
public:
	GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo); //�ϳ��� ������Ʈ, �ϳ��� ������Ʈ
	void addFile(CString filePath); //���ϸ�� �迭�� ���� �߰�
	BOOL gitUpload(); //���� ��ü�� ������ ������� filePathArr�� �ִ� ��� ������ ���ε�
	char* projInfo2charP(); //�� ������ ������ char*���·� ����, ������ free()�ʿ�
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
};