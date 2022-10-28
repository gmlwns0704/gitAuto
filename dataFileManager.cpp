#include "dataFileManager.h"
#include "GitUploader.h"
#include "pch.h"

CArray<GitUploader*> GitUploader::projList;

BOOL dataFileManager::loadData() {
	FILE* dataFile;
	fopen_s(&dataFile, "./GPMDataFile", "r");
	if (!dataFile) { //파일 발견되지 않음
		MessageBox(NULL, _T("GPMDataFile not found"), _T("ERROR"), MB_ICONERROR);
		return FALSE;
	}

	char varStr[64]; //파일을 읽어올 때 변수를 구분
	char str[1024]; //변수의 내용을 읽어옴

	fscanf_s(dataFile, "%[^\n]\n", str, 1023);
	if (strcmp(str, "//PROJECT_LIST") == 0) { // "//PROJECT_LIST"에 해당하는 정보 불러옴
		string //이후 생성할 GitUploader 객체를 위한 입력값
			projName,
			dirPath,
			toolPath,
			backupRepo;
		int line = 1;
		while (strcmp(str, "//FILE_END") != 0) { //프로젝트들의 정보 불러오기
			line++;
			//fscanf_s(dataFile, "%s : %[^\n]\n", varStr, 63, str, 1023); //한줄씩 읽어옴
			fscanf_s(dataFile, "%s : ", varStr, sizeof(varStr));
			TRACE("line %d varStr : %s\n", line, varStr);
			if (strcmp(varStr, "//FILE_END") == 0)
				break;
			fscanf_s(dataFile, "%[^\n]\n", str, sizeof(str));
			TRACE("line %d str : %s\n", line, str);

			if (strcmp(varStr, "projName") == 0) { //변수의 종류에 따라 다른 값으로 입력
				projName = str;
			}
			else if (strcmp(varStr, "dirPath") == 0) {
				dirPath = str;
			}
			else if (strcmp(varStr, "toolPath") == 0) {
				toolPath = str;
			}
			else if (strcmp(varStr, "backupRepo") == 0) {
				backupRepo = str;
			}
			else if (!strcmp(varStr, "fileList")) {
				GitUploader* newProj = new GitUploader(dirPath, projName, toolPath, backupRepo);
				fscanf_s(dataFile, "%[^\n]\n", str, 1023);
				while (strcmp(str, "//PROJECT_END") != 0) {
					line++;
					string cstrTmp = str;
					//cstrTmp.append("\n");
					newProj->addFile(cstrTmp);
					fscanf_s(dataFile, "%[^\n]\n", str, 1023);

					TRACE("line %d str : %s\n", line, str);
				}
			}
			else { //알수없는 정보, 에러
				CString errorMsg;
				errorMsg.Format(_T("Unknow text detected from GPMDataFile line : %d\n%s"), line, (LPCTSTR)varStr);
				MessageBox(NULL, errorMsg, _T("ERROR"), MB_ICONERROR);
				fclose(dataFile);
				return FALSE;
			}


		}
	}
	

	fclose(dataFile);
	return TRUE;
}

BOOL dataFileManager::saveData() {
	FILE* dataFile;
	fopen_s(&dataFile, "./GPMDataFile", "w");
	if (!dataFile) {
		MessageBox(NULL, _T("GPMDataFile not found"), _T("ERROR"), MB_ICONERROR);
		return FALSE;
	}

	fprintf_s(dataFile, "//PROJECT_LIST\n");
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) { //프로젝트의 갯수들 만큼 반복
		char str[1024];
		GitUploader* objTmp = GitUploader::projList[i];

		CString2charP(objTmp->getProjName(), str);
		fprintf_s(dataFile, "projName : %s\n", str);

		CString2charP(objTmp->getDirPath(), str);
		fprintf_s(dataFile, "dirPath : %s\n", str);

		CString2charP(objTmp->getToolPath(), str);
		fprintf_s(dataFile, "toolPath : %s\n", str);

		CString2charP(objTmp->getBackupRepo(), str);
		fprintf_s(dataFile, "backupRepo : %s\n", str);

		fprintf_s(dataFile, "fileList : fileList\n");
		for (int j = 0; j < objTmp->getFilePathArrCount(); j++) { //파일경로 리스트의 모든 경로들 입력
			CString2charP(objTmp->getFilePath(j), str);
			fprintf_s(dataFile, "%s\n", str);
		}

		fprintf_s(dataFile, "//PROJECT_END\n");
	}

	fprintf_s(dataFile, "//FILE_END");
	
	fclose(dataFile);
	return TRUE;
}