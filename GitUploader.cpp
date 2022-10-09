#include "pch.h"
#include "GitUploader.h"

static CArray<GitUploader*> projList;

//���δ� Ŭ���� ������, �ϳ��� ������Ʈ�� �ϳ��� ������Ʈ
GitUploader::GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo) {
	this->dirPath = dirPath; //������Ʈ ���丮�� ���
	this->projName = projName; //������Ʈ��, ����꿡�� �귣ġ �̸����� ����
	this->toolPath = toolPath; //�� ������Ʈ�� �´� �������� ���
	this->backupRepo = backupRepo; //���ε�� ������� ��ũ

	this->filePathArr.SetSize(0); //���ϸ���Ʈ �⺻ũ�� 0

	this->projList.Add(this);
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