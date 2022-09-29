#include "pch.h"
#include "GitUploader.h"

void CString2charP(CString cstr, char* str) { //CString�� char*�� ��ȯ
	for (int i = 0; i < cstr.GetLength(); i++) {
		str[i] = cstr.GetAt(i);
		//printf("%c", cstr.GetAt(i));
	}
	str[cstr.GetLength()] = '\0';
}

void CString2system(CString cstr) { //CString�� system�Լ��� �Է���
	char* str = (char*)malloc(cstr.GetLength() + 1);
	CString2charP(cstr, str);
	system(str);
	free(str);
}

//���δ� Ŭ���� ������, �ϳ��� ������Ʈ�� �ϳ��� ������Ʈ
GitUploader::GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo) {
	GitUploader::dirPath = dirPath; //������Ʈ ���丮�� ���
	GitUploader::projName = projName; //������Ʈ��, ����꿡�� �귣ġ �̸����� ����
	GitUploader::toolPath = toolPath; //�� ������Ʈ�� �´� �������� ���
	GitUploader::backupRepo = backupRepo; //���ε�� ������� ��ũ

	GitUploader::filePathArr.SetSize(0); //���ϸ���Ʈ �⺻ũ�� 0
}

//�ش� ������Ʈ���� ���ϸ���Ʈ�� ������ ���ε� - �ϴ� �۵���!!!
BOOL GitUploader::gitUpload() {
	/*
* �ش� ���͸����� git ���� Ȥ�� �����
* > cd <projPath> && git init
* 
* ���ο� �귣ġ ���� or ������ branch ����, �ٸ� ������Ʈ���� ���� �귣ġ���� ���� �ʵ��� �����ؾ���
* > cd <projPath> && git checkout --orphan <branchName>
* 
* ���ε� ����̵Ǵ� ������ ���, ����ε� ���������� Ȥ�ø𸣴� �ϴ� ������ ����
* > cd <projPath> && git add <filePath>
* 
* add�� ���� ���� commit
* > cd <projPath> && git commit -m "message"
* 
* commit�� ���ϵ� ������ �귣ġ�� ����� ���ε�
* > cd <projPath> && git push <GitHubLink> <branchName>
*/

	//git�� ��� ���ϸ���Ʈ ���ε�
	CString2system(_T("cd ") + dirPath + _T(" && git init"));
	CString2system(_T("cd ") + dirPath + _T(" && git checkout --orphan ") + projName);
	for (int i = 0; i < filePathArr.GetCount(); i++) { //����Ʈ���� ���ϵ� ��� add
		CString2system(_T("cd ") + dirPath + _T(" && git add ") + filePathArr[i]);
	}
	CString2system(_T("cd ") + dirPath + _T(" && git commit -m \"autoBackup\"")); //***autoBackup��� ��� �ð� ����ϱ�?***
	CString2system(_T("cd ") + dirPath + _T(" && git push ") + backupRepo + _T(" ") + projName);

	return true;
}

//���ο� ������ ���ϸ�Ͽ� �߰�
void GitUploader::addFile(CString filePath) {
	filePathArr.Add(filePath);
}

char* GitUploader::projInfo2charP() { //�ش� ������Ʈ ���δ� Ŭ������ ������ char*�� ��ȯ�Ͽ� ����, ������ free�ʿ�
	char* result;
	CString infoStr =
		projName + _T("\n") +
		dirPath + _T("\n") +
		toolPath + _T("\n") +
		backupRepo + _T("\n");
	for (int i = 0; i < filePathArr.GetCount(); i++) {
		infoStr += filePathArr[i] + _T("\n");
	}

	result = (char*)malloc(infoStr.GetLength() + 1);
	CString2charP(infoStr, result);

	return result;
}