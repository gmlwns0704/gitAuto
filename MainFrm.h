﻿
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:
	NOTIFYICONDATA nid;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CChildView    m_wndView;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnProject();
	afx_msg void OnInit();
	afx_msg void OnAll();
	afx_msg void OnBackup();
	afx_msg void OnInfo();
	afx_msg void OnSaveAll();
	afx_msg void OnLoadProject();
	afx_msg void OnNewProject();
	afx_msg void OnSelfBackup();
	afx_msg void OnSetInit();
	afx_msg void OnUploadAll();
	afx_msg void OnClose();
	afx_msg LRESULT OnTaryNotification(WPARAM, LPARAM);
	afx_msg void OnHide();
	afx_msg void OnSelfEdit();
};


