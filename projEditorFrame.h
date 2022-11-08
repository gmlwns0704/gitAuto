#pragma once
#include "afxdialogex.h"


// projEditorFrame 대화 상자
// 참고 출처 : https://learn.microsoft.com/ko-kr/cpp/mfc/reference/clistbox-class?view=msvc-170#findstringexact

class projEditorFrame : public CDialogEx
{
	DECLARE_DYNAMIC(projEditorFrame)

public:
	projEditorFrame(GitUploader* targetProj, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~projEditorFrame();
	GitUploader* proj; //이 다이얼로그의 대상이되는 객체

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_UPLOADER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddExt();
	afx_msg void OnBnClickedButtonAddFile();
	afx_msg void OnBnClickedButtonRmFile();
	virtual BOOL OnInitDialog();
	CListBox fileList;
//	virtual BOOL Create(LPCTSTR lpszTemplateName, GitUploader* insertProj, CWnd* pParentWnd = NULL);
private:
	void listBoxUpdate(); //리스트박스를 현재 객체의 상태에 맞게 업데이트함
};
