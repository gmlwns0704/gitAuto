#include "pch.h"
#include "GitUploader.h"

static CArray<GitUploader*> projList;

//업로더 클래스 생성자, 하나의 프로젝트에 하나의 오브젝트
GitUploader::GitUploader(CString dirPath, CString projName, CString toolPath, CString backupRepo) {
	GitUploader::dirPath = dirPath; //프로젝트 디렉토리의 경로
	GitUploader::projName = projName; //프로젝트명, 깃허브에서 브랜치 이름으로 사용됨
	GitUploader::toolPath = toolPath; //그 프로젝트에 맞는 개발툴의 경로
	GitUploader::backupRepo = backupRepo; //업로드될 깃허브의 링크

	GitUploader::filePathArr.SetSize(0); //파일리스트 기본크기 0

	GitUploader::projList.Add(this);
}

//해당 프로젝트에서 파일리스트의 파일을 업로드 - 일단 작동함!!!
BOOL GitUploader::gitUpload() {
	/*
* 해당 디렉터리에서 git 생성 혹은 재생성
* > cd <projPath> && git init
* 
* 새로운 브랜치 생성 or 기존의 branch 접근, 다른 프로젝트에서 같은 브랜치명을 쓰지 않도록 조심해야함
* > cd <projPath> && git checkout --orphan <branchName>
* 
* 업로드 대상이되는 파일의 경로, 상대경로도 가능하지만 혹시모르니 일단 절대경로 권장
* > cd <projPath> && git add <filePath>
* 
* add된 파일 파일 commit
* > cd <projPath> && git commit -m "message"
* 
* commit된 파일들 정해진 브랜치로 깃허브 업로드
* > cd <projPath> && git push <GitHubLink> <branchName>
*/

	//git에 대상 파일리스트 업로드
	CString2system(_T("cd ") + dirPath + _T(" && git init"));
	CString2system(_T("cd ") + dirPath + _T(" && git checkout --orphan ") + projName);
	for (int i = 0; i < filePathArr.GetCount(); i++) { //리스트내의 파일들 모두 add
		CString2system(_T("cd ") + dirPath + _T(" && git add ") + filePathArr[i]);
	}
	CString2system(_T("cd ") + dirPath + _T(" && git commit -m \"autoBackup\"")); //***autoBackup대신 당시 시간 사용하기?***
	CString2system(_T("cd ") + dirPath + _T(" && git push ") + backupRepo + _T(" ") + projName);

	return true;
}

//새로운 파일을 파일목록에 추가
void GitUploader::addFile(CString filePath) {
	filePathArr.Add(filePath);
}

GitUploader* GitUploader::getProj(CString projName) { //로드된 프로젝트 리스트에서 해당 이름의 프로젝트를 GitUploader형태로 리턴
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		if (GitUploader::projList[i]->getProjName() == projName) {
			return GitUploader::projList[i];
		}
	}
	return NULL;
}