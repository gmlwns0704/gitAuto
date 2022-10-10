#pragma once
#include "afxdialogex.h"


// newUploaderFrame 대화 상자

class newUploaderFrame : public CDialogEx
{
	DECLARE_DYNAMIC(newUploaderFrame)

public:
	newUploaderFrame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~newUploaderFrame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_UPLOADER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
