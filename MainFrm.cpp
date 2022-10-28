
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GitProjectManager.h"

#include "MainFrm.h"
#include "newUploaderFrame.h"

#include "dataFileManager.h"
#include "GitUploader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_SAVE_ALL, &CMainFrame::OnSaveAll)
	ON_COMMAND(ID_INFO, &CMainFrame::OnInfo)
	ON_COMMAND(ID_LOAD_PROJECT, &CMainFrame::OnLoadProject)
	ON_COMMAND(ID_NEW_PROJECT, &CMainFrame::OnNewProject)
	ON_COMMAND(ID_SELF_BACKUP, &CMainFrame::OnSelfBackup)
	ON_COMMAND(ID_SET_INIT, &CMainFrame::OnSetInit)
	ON_COMMAND(ID_UPLOAD_ALL, &CMainFrame::OnUploadAll)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWnd::OnSysCommand(nID, lParam);
}


void CMainFrame::OnInfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GitUploader::infoAll();
}

//***여기서 GitUploader객체의 변수에 접근시 접근위반뜨고 뻗음, 원인해결방법 찾기***//
void CMainFrame::OnSaveAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!dataFileManager::saveData()) {
		MessageBox(_T("failed to save GPMDataFile"), _T("warning"));
	}
}


void CMainFrame::OnLoadProject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!dataFileManager::loadData()) {
		MessageBox(_T("failed to load GPMDataFile"), _T("warning"));
	}
}


void CMainFrame::OnNewProject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//***newUploaderFrame 불러오기***//
	CMainFrame* pFrame = this;
	newUploaderFrame* nUFrame = new newUploaderFrame;
	nUFrame->Create(IDD_NEW_UPLOADER, pFrame);
	nUFrame->ShowWindow(SW_SHOW);
	nUFrame->UpdateWindow();
}


void CMainFrame::OnSelfBackup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//***이 프로젝트 스스로를 깃허브에 업로드 및 프로젝트 정보를 로컬저장***//
	GitUploader *selfBackup = new GitUploader(
		"C:/Users/user/source/repos/GitProjectManager",
		"self",
		"C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe",
		"https://github.com/gmlwns0704/gitAuto");
	selfBackup->addAllExt(".cpp");
	selfBackup->addAllExt(".h");

	selfBackup->Info();
}


void CMainFrame::OnSetInit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//***initFrame 불러오기***//
	CMainFrame* pFrame = this;
	initFrame* iFrame = new initFrame;
	iFrame->Create(IDD_INIT, pFrame);
	iFrame->ShowWindow(SW_SHOW);
	iFrame->UpdateWindow();
}


void CMainFrame::OnUploadAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (GitUploader::uploadAll()) {
		MessageBox(_T("All project upload"), _T("All project upload"), MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(_T("warning"), _T("failed to upload project"), MB_OK | MB_ICONWARNING);
	}
}
