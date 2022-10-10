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
END_MESSAGE_MAP()


// newUploaderFrame 메시지 처리기


void newUploaderFrame::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString projName, projDir, gitURL;
	GetDlgItemTextW(IDC_EDIT_PROJNAME, projName);
	GetDlgItemTextW(IDC_EDIT_PROJDIR, projDir);
	GetDlgItemTextW(IDC_EDIT_GIT_URL, gitURL);

	GitUploader(projDir, projName, _T(""), gitURL);

	CDialogEx::OnOK();

	DestroyWindow();
}
