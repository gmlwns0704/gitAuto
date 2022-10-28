#include "dataFileManager.h"
#include "GitUploader.h"
#include "pch.h"

CArray<GitUploader*> GitUploader::projList;

BOOL dataFileManager::loadData() {
	FILE* dataFile;
	fopen_s(&dataFile, "./GPMDataFile", "r");
	if (!dataFile) { //���� �߰ߵ��� ����
		MessageBox(NULL, _T("GPMDataFile not found"), _T("ERROR"), MB_ICONERROR);
		return FALSE;
	}

	char varStr[64]; //������ �о�� �� ������ ����
	char str[1024]; //������ ������ �о��

	fscanf_s(dataFile, "%[^\n]\n", str, 1023);
	if (strcmp(str, "//PROJECT_LIST") == 0) { // "//PROJECT_LIST"�� �ش��ϴ� ���� �ҷ���
		string //���� ������ GitUploader ��ü�� ���� �Է°�
			projName,
			dirPath,
			toolPath,
			backupRepo;
		int line = 1;
		while (strcmp(str, "//FILE_END") != 0) { //������Ʈ���� ���� �ҷ�����
			line++;
			//fscanf_s(dataFile, "%s : %[^\n]\n", varStr, 63, str, 1023); //���پ� �о��
			fscanf_s(dataFile, "%s : ", varStr, sizeof(varStr));
			TRACE("line %d varStr : %s\n", line, varStr);
			if (strcmp(varStr, "//FILE_END") == 0)
				break;
			fscanf_s(dataFile, "%[^\n]\n", str, sizeof(str));
			TRACE("line %d str : %s\n", line, str);

			if (strcmp(varStr, "projName") == 0) { //������ ������ ���� �ٸ� ������ �Է�
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
			else { //�˼����� ����, ����
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
	for (int i = 0; i < GitUploader::projList.GetCount(); i++) { //������Ʈ�� ������ ��ŭ �ݺ�
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
		for (int j = 0; j < objTmp->getFilePathArrCount(); j++) { //���ϰ�� ����Ʈ�� ��� ��ε� �Է�
			CString2charP(objTmp->getFilePath(j), str);
			fprintf_s(dataFile, "%s\n", str);
		}

		fprintf_s(dataFile, "//PROJECT_END\n");
	}

	fprintf_s(dataFile, "//FILE_END");
	
	fclose(dataFile);
	return TRUE;
}