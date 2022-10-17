#include "pch.h"
#include "GitUploader.h"
#include <windows.h>

//***static***//
static CArray<GitUploader*> projList;

GitUploader* GitUploader::getProj(CString projName) { //�ε�� ������Ʈ ����Ʈ���� �ش� �̸��� ������Ʈ�� GitUploader���·� ����
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		if (GitUploader::projList[i]->getProjName() == projName) {
			return GitUploader::projList[i];
		}
	}
	return NULL;
}

BOOL GitUploader::uploadAll() { //��� ������Ʈ ���ε�
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		GitUploader::projList[i]->gitUpload();
	}
	return TRUE;
}

//***not static***//

//���δ� Ŭ���� ������, �ϳ��� ������Ʈ�� �ϳ��� ������Ʈ
GitUploader::GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo) {
	GitUploader::dirPath = dirPath; //������Ʈ ���丮�� ���
	GitUploader::projName = projName; //������Ʈ��, ����꿡�� �귣ġ �̸����� ����
	GitUploader::toolPath = toolPath; //�� ������Ʈ�� �´� �������� ���
	GitUploader::backupRepo = backupRepo; //���ε�� ������� ��ũ

	GitUploader::filePathArr.SetSize(0); //���ϸ���Ʈ �⺻ũ�� 0
	GitUploader::filePathArrCount = 0;

	GitUploader::projList.Add(this);
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
BOOL GitUploader::addFile(CString filePath) {
	if (GitUploader::getProj(filePath) != NULL) { //�ش� ������ �̹� �ִٸ� �߰� �ź�
		return FALSE;
	}
	filePathArr.Add(filePath);
	filePathArrCount = filePathArr.GetCount();
	return TRUE;
}

BOOL GitUploader::addAllExt(CString extension) { //�ش� ���丮���� ���޹��� Ȯ���ڷ� �̷���� ��� ���� �߰�
	WIN32_FIND_DATAW data;
	HANDLE hFind = FindFirstFile(dirPath + _T("/*"), &data);
	if (hFind == INVALID_HANDLE_VALUE) { //���� ã������
		CString str;
		str.Format(_T("directory not found : %s"), dirPath);
		MessageBox(NULL, str, _T("ERROR"), MB_ICONERROR);
		return FALSE;
	}

	while (FindNextFile(hFind, &data) != 0) { //���͸� �� ��� ���ϵ鿡 ���� �˻�
		CString fileName = data.cFileName;
		CString fileExt = fileName.Right(extension.GetLength()); //���ϸ��� Ȯ���ڸ� ����

		if (fileExt.Compare(extension) == 0) { //Ȯ���� ��
			addFile(dirPath + _T("/") + fileName); //���� �߰�
		}
	}

	FindClose(hFind);
	return TRUE;
}