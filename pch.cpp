// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

char* CString2charP(CString cstr) { //CString을 char*로 변환하여 char*리턴, 사용이후 알아서 할당해제 해야함
	char* str = (char*)malloc(cstr.GetLength() + 1);
	for (int i = 0; i < cstr.GetLength(); i++) {
		str[i] = cstr.GetAt(i);
		//printf("%c", cstr.GetAt(i));
	}
	str[cstr.GetLength()] = '\0';
	return str;
}

char* CString2charP(string cstr) {
	return CString2charP(CString(cstr.c_str()));
}

void CString2charP(CString cstr, char* str) { //사전에 메모리가 할당된 char*에 사용
	for (int i = 0; i < cstr.GetLength(); i++) {
		str[i] = cstr.GetAt(i);
		//printf("%c", cstr.GetAt(i));
	}
	str[cstr.GetLength()] = '\0';
}

void CString2charP(string cstr, char* str) {
	CString2charP(CString(cstr.c_str()), str);
}

void CString2system(CString cstr) { //CString을 system함수에 입력함
	char* str = CString2charP(cstr);
	system(str);
	free(str);
}