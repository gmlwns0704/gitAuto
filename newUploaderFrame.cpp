// newUploaderFrame.cpp: 구현 파일
//

#include "pch.h"
#include "GitProjectManager.h"
#include "afxdialogex.h"
#include "newUploaderFrame.h"


// newUploaderFrame 대화 상자

IMPLEMENT_DYNAMIC(newUploaderFrame, CDialogEx)

newUploaderFrame::newUploaderFrame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_UPLOADER, pParent)
{

}

newUploaderFrame::~newUploaderFrame()
{
}

void newUploaderFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(newUploaderFrame, CDialogEx)
	ON_BN_CLICKED(IDOK, &newUploaderFrame::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PROJ_DIR_FIND, &newUploaderFrame::OnBnClickedButtonProjDirFind)
END_MESSAGE_MAP()


// newUploaderFrame 메시지 처리기


void newUploaderFrame::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString projName, projDir, gitURL;
	GetDlgItemTextW(IDC_EDIT_PROJNAME, projName);
	GetDlgItemTextW(IDC_EDIT_PROJDIR, projDir);
	GetDlgItemTextW(IDC_EDIT_GIT_URL, gitURL);
	if (projName == "") {
		MessageBox(_T("프로젝트 이름을 입력하시오"), _T("warning"), MB_ICONWARNING);
		return;
	}
	if (projDir== "") {
		MessageBox(_T("프로젝트 경로를 입력하시오"), _T("warning"), MB_ICONWARNING);
		return;
	}
	if (GitUploader::getProj((string)CT2CA(projName))) {
		MessageBox(_T("해당 이름의 프로젝트가 이미 존재합니다"), _T("warning"), MB_ICONWARNING);
		return;
	}
	GitUploader(projDir, projName, _T(""), gitURL);

	CDialogEx::OnOK();

	DestroyWindow();
}


BOOL newUploaderFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_EDIT_GIT_URL)->SetWindowTextW(initFileManager::defaultBackupURL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void newUploaderFrame::OnBnClickedButtonProjDirFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//출처 : https://psmkr0225.tistory.com/192
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("파일이 저장될 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);               // 파일경로 읽어오기

	// 경로를 가져와 사용할 경우, Edit Control 에 값 저장
	CString str;
	str.Format(_T("%s"), szBuffer);
	SetDlgItemText(IDC_EDIT_PROJDIR, str);
}
