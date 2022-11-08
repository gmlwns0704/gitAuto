// initFrame.cpp: 구현 파일
//

#include "pch.h"
#include "GitProjectManager.h"
#include "afxdialogex.h"
#include "initFrame.h"

CString initFileManager::gitURL;
CString initFileManager::defaultBackupURL;
CString initFileManager::autoBackupMessage;


// initFrame 대화 상자

IMPLEMENT_DYNAMIC(initFrame, CDialogEx)

initFrame::initFrame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INIT, pParent)
{
}

initFrame::~initFrame()
{
}

void initFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//기본값 불러와서 에딧컨트롤에 넣어놓기
	SetDlgItemText(IDS_EDIT_GIT_URL, initFileManager::gitURL);
	SetDlgItemText(IDS_EDIT_REPO_URL, initFileManager::defaultBackupURL);
	SetDlgItemText(IDS_EDIT_AUTO_BACKUP_MSG, initFileManager::autoBackupMessage);
}


BEGIN_MESSAGE_MAP(initFrame, CDialogEx)
	ON_BN_CLICKED(IDS_OK, &initFrame::OnBnClickedOk)
	ON_BN_CLICKED(IDS_CANCEL, &initFrame::OnBnClickedCancel)
END_MESSAGE_MAP()


// initFrame 메시지 처리기


void initFrame::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemTextW(IDS_EDIT_GIT_URL, initFileManager::gitURL);
	GetDlgItemTextW(IDS_EDIT_REPO_URL, initFileManager::defaultBackupURL);
	GetDlgItemTextW(IDS_EDIT_AUTO_BACKUP_MSG, initFileManager::autoBackupMessage);

	initFileManager::saveInit();

	DestroyWindow();
}


void initFrame::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	DestroyWindow();
}
