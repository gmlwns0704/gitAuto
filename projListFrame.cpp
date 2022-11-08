// projListFrame.cpp: 구현 파일
//

#include "pch.h"
#include "GitProjectManager.h"
#include "afxdialogex.h"
#include "projListFrame.h"
#include "projEditorFrame.h"


// projListFrame 대화 상자

IMPLEMENT_DYNAMIC(projListFrame, CDialogEx)

projListFrame::projListFrame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPLOADER_LIST, pParent)
{

}

projListFrame::~projListFrame()
{
}

void projListFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROJ, m_projList);
}


BEGIN_MESSAGE_MAP(projListFrame, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST_PROJ, &projListFrame::OnLbnDblclkListProj)
END_MESSAGE_MAP()


// projListFrame 메시지 처리기


BOOL projListFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	for (int i = 0; i < GitUploader::projList.GetCount(); i++) {
		m_projList.AddString((CString)GitUploader::projList.GetAt(i)->getProjName().c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//리스트박스 더블클릭
void projListFrame::OnLbnDblclkListProj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int n = m_projList.GetCurSel(); //선택한 항목 인덱스
	if (n == LB_ERR) { //선택된 프로젝트가 없음
		return;
	}

	//해당 프로젝트 편집 다이얼로그 생성
	CString cstr;
	m_projList.GetText(n, cstr);
	projEditorFrame* nUFrame = new projEditorFrame(GitUploader::getProj(cstr)); //해당 프로젝트 이름 생성자 매개변수로 전달
	nUFrame->Create(IDD_EDIT_UPLOADER);
	nUFrame->ShowWindow(SW_SHOW);
	nUFrame->UpdateWindow();
	
	//이 다이얼로그 삭제
	DestroyWindow();
}
