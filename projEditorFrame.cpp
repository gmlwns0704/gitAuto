// projEditorFrame.cpp: 구현 파일
//

#include "pch.h"
#include "GitProjectManager.h"
#include "afxdialogex.h"
#include "projEditorFrame.h"


// projEditorFrame 대화 상자

IMPLEMENT_DYNAMIC(projEditorFrame, CDialogEx)

projEditorFrame::projEditorFrame(GitUploader* targetProj, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_UPLOADER, pParent)
{
	projEditorFrame::proj = targetProj;
}

projEditorFrame::~projEditorFrame()
{
}

void projEditorFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILES, fileList);
}


BEGIN_MESSAGE_MAP(projEditorFrame, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_EXT, &projEditorFrame::OnBnClickedButtonAddExt)
	ON_BN_CLICKED(IDC_BUTTON_ADD_FILE, &projEditorFrame::OnBnClickedButtonAddFile)
	ON_BN_CLICKED(IDC_BUTTON_RM_FILE, &projEditorFrame::OnBnClickedButtonRmFile)
END_MESSAGE_MAP()


// projEditorFrame 메시지 처리기


void projEditorFrame::OnBnClickedButtonAddExt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstr;
	GetDlgItemText(IDC_EDIT_EXT, cstr);
	proj->addAllExt(cstr);
	listBoxUpdate();
}


void projEditorFrame::OnBnClickedButtonAddFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//출처 : https://psmkr0225.tistory.com/192
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 파일 추가
		proj->addFile(strPathName);
		//리스트에 해당 파일 경로 추가
		fileList.InsertString(-1, strPathName);
	}
}


void projEditorFrame::OnBnClickedButtonRmFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int n = fileList.GetCurSel(); //n = 리스트박스에서 선택한 인덱스
	CString cstr;
	//LB_ERR: 아무것도 선택하지 않음
	if (n != LB_ERR) { //리스트박스의 무언가 선택함
		fileList.GetText(n, cstr);
		//MessageBox(cstr);
		proj->rmFile(cstr); //리스트박스 해당 인덱스의 아이템을 포인터로 얻어서 전달
		fileList.DeleteString(fileList.GetCurSel());
	}
	else { //아무것도 선택하지 않았다면
		fileList.GetText(0, cstr);
		proj->rmFile(cstr);
		fileList.DeleteString(0);
	}
}


BOOL projEditorFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//프로젝트이름 출력
	GetDlgItem(IDC_EDIT_PROJNAME)->SetWindowTextW((CString)(proj->getProjName()).c_str());
	GetDlgItem(IDC_EDIT_EXT)->SetWindowTextW(_T("예:[.cpp][.h]"));
	for (int i = 0; i < proj->getFilePathArrCount(); i++) {
		fileList.InsertString(i, (CString)proj->getFilePath(i).c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//리스트박스를 업데이트
void projEditorFrame::listBoxUpdate()
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < proj->getFilePathArrCount(); i++) { //리스트박스에 없는파일 찾아서 추가
		if (fileList.FindStringExact(0, (CString)proj->getFilePath(i).c_str()) == LB_ERR) { //검색에 실패했다면 (리스트박스에 해당 파일경로가 없다면)
			fileList.AddString((CString)proj->getFilePath(i).c_str()); //해당 파일 리스트박스에 추가
		}
	}
}
