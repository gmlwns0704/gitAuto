#include "pch.h"
#include "GitUploader.h"
#include <windows.h> //cmd��ɾ�

//***static***//
static CArray<GitUploader*> projList;
BOOL GitUploader::continueThread = TRUE;
int GitUploader::threadCoolTime = 5000;

GitUploader* GitUploader::getProj(string projName) { //�ε�� ������Ʈ ����Ʈ���� �ش� �̸��� ������Ʈ�� GitUploader���·� ����
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		if (GitUploader::projList[i]->getProjName() == projName) {
			return GitUploader::projList[i];
		}
	}
	return NULL;
}
GitUploader* GitUploader::getProj(CString projName) {
	return GitUploader::getProj((string)CT2CA(projName));
}

BOOL GitUploader::uploadAll() { //��� ������Ʈ ���ε�
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		GitUploader::projList[i]->gitUpload();
	}
	return TRUE;
}

void GitUploader::infoAll() { //�����ϴ� ��� ������Ʈ���� info()����
	if (GitUploader::projList.GetCount() <= 0) { //������Ʈ�� ����
		MessageBox(NULL, _T("Project not exist"), _T("Warning"), MB_ICONWARNING);
	}
	else { //������Ʈ ����
		TRACE("project cnt : %d", GitUploader::projList.GetCount());
		for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
			GitUploader::projList[i]->Info();
		}
	}
}

void GitUploader::autoUploadThread() {
	int loopCount = 0;
	while (continueThread) {
		loopCount++;
		CString loopCntMsg;
		loopCntMsg.Format(_T("loop : %d : "), loopCount);
		TRACE(loopCntMsg);
		for (int i = 0; i < projList.GetCount(); i++) {
			GitUploader* targetProj = projList.GetAt(i);
			BOOL isModified = FALSE;
			for (int j = 0; j < targetProj->getFilePathArrCount(); j++) {
				//��ó : https://2ry53.tistory.com/138
				string targetFile = targetProj->getFilePath(j);
				TRACE(loopCntMsg + (CString)targetFile.c_str() + _T("\n"));
				HANDLE h_File = CreateFile((CString)targetFile.c_str(),
					GENERIC_READ,
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
				if (h_File != INVALID_HANDLE_VALUE) {
					FILETIME
						creTime, //�Ⱦ���
						accTime, //�Ⱦ���
						wrtTime;
					GetFileTime(h_File, &creTime, &accTime, &wrtTime);
					SYSTEMTIME
						wrtSysTime,
						wrtLocalTime; //�ý��۽ð� ��ȯ
					FileTimeToSystemTime(&wrtTime, &wrtSysTime);
					SystemTimeToTzSpecificLocalTime(NULL, &wrtSysTime, &wrtLocalTime);

					CTime modifiedTIme(wrtLocalTime); //������ �����ð�
					TRACE(loopCntMsg + targetProj->lastModified.Format("%Y %m %d %H %M %S") + _T(" vs ") + modifiedTIme.Format("%Y %m %d %H %M %S\n"));
					if (targetProj->lastModified < modifiedTIme) { //�ϳ��� �����̶� �����ð��� �ٲ���ٸ�
						isModified = TRUE;
						targetProj->lastModified = modifiedTIme;
					}
				}
				//close handle
				CloseHandle(h_File);
			}
			if (isModified) { //�����ƴٸ� ������Ʈ ���ε���
				TRACE(loopCntMsg + _T(" upload\n"));
				targetProj->gitUpload();
			}
		}
		
		Sleep(threadCoolTime);
	}
}

void GitUploader::initThread() {
	thread t = thread(autoUploadThread);
	t.detach();
}

//***none static***//

//���δ� Ŭ���� ������, �ϳ��� ������Ʈ�� �ϳ��� ������Ʈ
GitUploader::GitUploader(string dirPath, string projName, string branch, string backupRepo) {
	GitUploader::dirPath = dirPath; //������Ʈ ���丮�� ���
	GitUploader::projName = projName; //������Ʈ��, ����꿡�� �귣ġ �̸����� ����
	GitUploader::branch = branch; //�� ������Ʈ�� �´� �������� ���
	GitUploader::backupRepo = backupRepo; //���ε�� ������� ��ũ

	GitUploader::filePathArr.SetSize(0); //���ϸ���Ʈ �⺻ũ�� 0
	GitUploader::filePathArrCount = 0;
	GitUploader::lastModified = CTime::GetCurrentTime();

	if (GitUploader::getProj(projName) != NULL) {
		MessageBox(NULL, _T("project name duplicated"), CString(projName.c_str()), MB_ICONWARNING);
	}
	else
		GitUploader::projList.Add(this);
}
//������ CString����
GitUploader::GitUploader(CString dirPath, CString projName, CString branch, CString backupRepo) { //CString �Է½� ������
	GitUploader::dirPath = CT2CA(dirPath); //������Ʈ ���丮�� ���
	GitUploader::projName = CT2CA(projName); //������Ʈ��, ����꿡�� �귣ġ �̸����� ����
	GitUploader::branch = CT2CA(branch); //�� ������Ʈ�� �´� �������� ���
	GitUploader::backupRepo = CT2CA(backupRepo); //���ε�� ������� ��ũ

	GitUploader::filePathArr.SetSize(0); //���ϸ���Ʈ �⺻ũ�� 0
	GitUploader::filePathArrCount = 0;
	GitUploader::lastModified = CTime::GetCurrentTime();

	if (GitUploader::getProj((string)CT2CA(projName)) != NULL) {
		MessageBox(NULL, _T("project name duplicated"), projName, MB_ICONWARNING);
	}
	else
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

	//����ð� ���ϱ�
	time_t timer = time(NULL);
	struct tm* t = (struct tm*)malloc(sizeof(struct tm));
	localtime_s(t, &timer);
	CString curTime;
	curTime.Format(_T("\"%d/%d/%d %d:%d\""), t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min);
	//git�� ��� ���ϸ���Ʈ ���ε�
	CString2system(_T("cd ") + CString(dirPath.c_str()) + _T(" && git init"));
	CString2system(_T("cd ") + CString(dirPath.c_str()) + _T(" && git checkout --orphan ") + CString(branch.c_str()));
	for (int i = 0; i < filePathArr.GetCount(); i++) { //����Ʈ���� ���ϵ� ��� add
		CString2system(_T("cd ") + CString(dirPath.c_str()) + _T(" && git add ") + CString(filePathArr[i].c_str()));
	}
	CString2system(_T("cd ") + CString(dirPath.c_str()) + _T(" && git commit -m ") + curTime); //***autoBackup��� ��� �ð� ����ϱ�?***
	CString2system(_T("cd ") + CString(dirPath.c_str()) + _T(" && git push ") + CString(backupRepo.c_str()) + _T(" ") + CString(branch.c_str()));

	return true;
}

//���ο� ������ ���ϸ�Ͽ� �߰�
BOOL GitUploader::addFile(string filePath) {
	TRACE("addFile : %s\n", filePath);
	if (GitUploader::getProj(filePath) != NULL) { //�ش� ������ �̹� �ִٸ� �߰� �ź�
		return FALSE;
	}
	filePathArr.Add(filePath);
	filePathArrCount = filePathArr.GetCount();
	return TRUE;
}
BOOL GitUploader::addFile(CString filePath) {
	return addFile((string)CT2CA(filePath));
}

BOOL GitUploader::rmFile(string filePath) {
	//MessageBox(NULL, (CString)filePath.c_str(), _T("HELLO"), NULL);

	for (int i = 0; i < filePathArrCount; i++) {
		TRACE("%s %s\n", filePath, filePathArr.GetAt(i));
		if (filePath.compare(filePathArr.GetAt(i)) == 0) {
			filePathArr.RemoveAt(i);
			filePathArrCount--;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL GitUploader::rmFile(CString filePath) {
	return rmFile((string)CT2CA(filePath));
}

BOOL GitUploader::addAllExt(string extension) { //�ش� ���丮���� ���޹��� Ȯ���ڷ� �̷���� ��� ���� �߰�
	WIN32_FIND_DATAW data;
	HANDLE hFind = FindFirstFile(CString(dirPath.c_str()) + _T("/*"), &data);
	if (hFind == INVALID_HANDLE_VALUE) { //���� ã������
		string str = "directory not found : " + dirPath;
		MessageBox(NULL, CString(str.c_str()), _T("ERROR"), MB_ICONERROR);
		return FALSE;
	}

	while (FindNextFile(hFind, &data) != 0) { //���͸� �� ��� ���ϵ鿡 ���� �˻�
		string fileName = CT2CA(data.cFileName);
		string fileExt = "";
		if (fileName.length() > extension.length()) {
			fileExt = fileName.substr(fileName.length() - extension.length(), extension.length()); //���ϸ��� Ȯ���ڸ� ����
			if (fileExt.compare(extension) == 0) { //Ȯ���� ��
				addFile(dirPath + "/" + fileName); //���� �߰�
			}
		}
	}

	FindClose(hFind);
	return TRUE;
}
BOOL GitUploader::addAllExt(CString extension) {
	return addAllExt((string)CT2CA(extension));
}

void GitUploader::Info() {//�ش� ������Ʈ ���� ���

	string info;
	info.append("dirPath : " + getDirPath());
	info.append("\nprojName : " + getProjName());
	info.append("\nbranch : " + getBranch());
	info.append("\nbackupRepo : " + getBackupRepo());
	info.append("\nfileList : " + std::to_string((getFilePathArrCount())) + "\n");

	//string info =
	//"dirPath : " + getDirPath() +
	//"\nprojName : " + getProjName() +
	//"\nbranch : " + getBranch() +
	//"\nbackupRepo : " + getBackupRepo() +
	//"\nfileList : " + std::to_string((getFilePathArrCount())) + "\n";

	for (int i = 0; i < filePathArr.GetCount(); i++) {
		info.append(getFilePath(i) + "\n");
	}

	MessageBox(NULL, CString(info.c_str()), CString(projName.c_str()), NULL);
}


//get�Լ� ���
string GitUploader::getProjName() {
	return projName;
}
string GitUploader::getDirPath() {
	return dirPath;
}
string GitUploader::getBackupRepo() {
	return backupRepo;
}
string GitUploader::getBranch() {
	return branch;
}
string GitUploader::getFilePath(int n) {
	if (n < filePathArr.GetCount())
		return filePathArr.GetAt(n);
	return NULL;
}
int GitUploader::getFilePathArrCount() {
	return filePathArrCount;
}