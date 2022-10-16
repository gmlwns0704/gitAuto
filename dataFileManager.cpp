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

	fscanf_s(dataFile, "%[^\n]\n", str);
	if (!strcmp(str, "//PROJECT_LIST")) { // "//PROJECT_LIST"�� �ش��ϴ� ���� �ҷ���
		CString //���� ������ GitUploader ��ü�� ���� �Է°�
			projName,
			dirPath,
			toolPath,
			backupRepo;
		while (!strcmp(str, "//FILE_END")) { //������Ʈ���� ���� �ҷ�����

			fscanf_s(dataFile, "%s : %[^\n]\n", varStr, str); //���پ� �о��

			if (!strcmp(varStr, "projName")) { //������ ������ ���� �ٸ� ������ �Է�
				projName = str;
			}
			else if (!strcmp(varStr, "dirPath")) {
				dirPath = str;
			}
			else if (!strcmp(varStr, "toolPath")) {
				toolPath = str;
			}
			else if (!strcmp(varStr, "backupRepo")) {
				backupRepo = str;
			}
			else if (!strcmp(varStr, "fileList : \n")) {
				GitUploader* newProj = new GitUploader(dirPath, projName, toolPath, backupRepo);
				fscanf_s(dataFile, "%[^\n]\n", str);
				while (!strcmp(str, "//PROJECT_END")) {
					newProj->addFile((LPCTSTR)str);
					fscanf_s(dataFile, "%[^\n]\n", str);
				}
			}
			else { //�˼����� ����, ����
				MessageBox(NULL, _T("Unknow Error detected from GPMDataFile"), _T("ERROR"), MB_ICONERROR);
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

		fprintf_s(dataFile, "fileList : \n");
		for (int j = 0; j < objTmp->getFilePathArrCount(); j++) { //���ϰ�� ����Ʈ�� ��� ��ε� �Է�
			CString2charP(objTmp->getFilePath(j), str);
			fprintf_s(dataFile, "%s\n", str);
		}

		fprintf_s(dataFile, "//PROJECT_END\n");
	}

	fprintf_s(dataFile, "//FILE_END");

	return TRUE;
}