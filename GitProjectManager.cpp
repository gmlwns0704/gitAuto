
// GitProjectManager.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GitProjectManager.h"
#include "MainFrm.h"
#include "resource.h"

#include "GitUploader.h"
#include "dataFileManager.h"
#include "newUploaderFrame.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGitProjectManagerApp

BEGIN_MESSAGE_MAP(CGitProjectManagerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGitProjectManagerApp::OnAppAbout)
END_MESSAGE_MAP()


// CGitProjectManagerApp 생성

CGitProjectManagerApp::CGitProjectManagerApp() noexcept
{

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GitProjectManager.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CGitProjectManagerApp 개체입니다.

CGitProjectManagerApp theApp;


// CGitProjectManagerApp 초기화

BOOL CGitProjectManagerApp::InitInstance()
{
	CWinApp::InitInstance();


	//***임시테스트***//
	//******//
	//Init불러오기***//
	initFileManager::loadInit();
	//***이 프로젝트 스스로를 깃허브에 업로드 및 프로젝트 정보를 로컬저장***//
	GitUploader selfBackup(
		_T("C:/Users/user/source/repos/GitProjectManager"),
		_T("self"),
		_T("C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe"),
		_T("https://github.com/gmlwns0704/gitAuto"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/ChildView.cpp"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/GitProjectManager.cpp"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/GitUploader.cpp"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/MainFrm.cpp"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/ChildView.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/framework.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/GitProjectManager.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/GitUploader.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/MainFrm.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/pch.h"));
	selfBackup.addFile(_T("C:/Users/user/source/repos/GitProjectManager/Resource.h"));
	selfBackup.gitUpload();

	//GitUploader sample(
	//	_T("C:/Users/user/source/repos/HelloMFC"),
	//	_T("sample"),
	//	_T("C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe"),
	//	_T("https://github.com/gmlwns0704/gitAuto"));
	//sample.addFile(_T("C:/Users/user/source/repos/HelloMFC/HelloMFC.cpp"));
	//sample.gitUpload();

	//***로컬 데이터파일에서 프로젝트 종류의 정보를 읽어오고 업로드***//
	//dataFileManager::loadData();
	//if (GitUploader* tmp = GitUploader::getProj(_T("self"))) {
	//	MessageBox(NULL, _T("self is found"), MB_OK, MB_ICONINFORMATION);
	//	tmp->gitUpload();
	//}
	//else {
	//	MessageBox(NULL, _T("self is NULL"), MB_OK, MB_ICONERROR);
	//}
	//if (GitUploader* tmp = dataFileManager::getProj(_T("sample"))) {
	//	MessageBox(NULL, _T("sample is found"), MB_OK, MB_ICONINFORMATION);
	//	tmp->gitUpload();
	//}
	//else {
	//	MessageBox(NULL, _T("sample is NULL"), MB_OK, MB_ICONERROR);
	//}
	
	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));


	// 주 창을 만들기 위해 이 코드에서는 새 프레임 창 개체를
	// 만든 다음 이를 애플리케이션의 주 창 개체로 설정합니다.
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 프레임을 만들어 리소스와 함께 로드합니다.
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	//***initFrame 불러오기(임시)***//
	//initFrame* iFrame = new initFrame;
	//iFrame->Create(IDD_INIT, pFrame);
	//iFrame->ShowWindow(SW_SHOW);
	//iFrame->UpdateWindow();

	//***newUploaderFrame 불러오기(임시)***//
	newUploaderFrame* nUFrame = new newUploaderFrame;
	nUFrame->Create(IDD_NEW_UPLOADER, pFrame);
	nUFrame->ShowWindow(SW_SHOW);
	nUFrame->UpdateWindow();

	//임시
	CString tmp;
	tmp.Format(_T("%d"), (int)GitUploader::projList.GetCount());
	MessageBox(NULL, tmp, GitUploader::getProj(_T("self"))->getProjName(), NULL);

	//***에러나는곳***//
	/*알수없는 이유로 업로더 객체의 CString값들에 접근하면 액세스위반이 뜸, public private뭐로해도 안됨*/
	dataFileManager::saveData(); //자동으로 저장

	return TRUE;
}

int CGitProjectManagerApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.

	return CWinApp::ExitInstance();
}

// CGitProjectManagerApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CGitProjectManagerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
