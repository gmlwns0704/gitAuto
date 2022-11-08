#pragma once
#include "afxdialogex.h"


// projListFrame 대화 상자

class projListFrame : public CDialogEx
{
	DECLARE_DYNAMIC(projListFrame)

public:
	projListFrame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~projListFrame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPLOADER_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_projList;
	afx_msg void OnLbnDblclkListProj();
};
