#include "pch.h"
#include "initFileManager.h"

BOOL initFileManager::loadInit() { //GPMInit을 읽어와서 초기값 설정
	FILE* GPMInitFile;
	fopen_s(&GPMInitFile, "./GPMInit", "r");
	if (GPMInitFile == NULL) {
		MessageBox(NULL, _T("error"), _T("GPMInit not found"), MB_ICONERROR);
		return FALSE;
	}
	char strTmp[1000] = "";

	fscanf_s(GPMInitFile, "%[^\n]\n", strTmp, (unsigned int)sizeof(strTmp));
	gitURL = (LPSTR)strTmp;
	fscanf_s(GPMInitFile, "%[^\n]\n", strTmp, (unsigned int)sizeof(strTmp));
	defaultBackupURL = (LPSTR)strTmp;
	fscanf_s(GPMInitFile, "%[^\n]\n", strTmp, (unsigned int)sizeof(strTmp));
	autoBackupMessage = (LPSTR)strTmp;

	fclose(GPMInitFile);
	return TRUE;
}

BOOL initFileManager::saveInit() { //GPMInit파일을 재설정
	FILE* GPMInitFile;
	fopen_s(&GPMInitFile, "./GPMInit", "w");
	if (GPMInitFile == NULL) {
		MessageBox(NULL, _T("error"), _T("GPMInit not found"), MB_ICONERROR);
		return FALSE;
	}

	char* strTmp;

	strTmp = CString2charP(gitURL);
	fprintf_s(GPMInitFile, "%s\n", strTmp);
	free(strTmp);

	strTmp = CString2charP(defaultBackupURL);
	fprintf_s(GPMInitFile, "%s\n", strTmp);
	free(strTmp);

	strTmp = CString2charP(autoBackupMessage);
	fprintf_s(GPMInitFile, "%s\n", strTmp);
	free(strTmp);

	fclose(GPMInitFile);

	return TRUE;
}