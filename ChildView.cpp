
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "CClientDC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	/*CMetaFileDC dc;
	dc.CreateEnhanced(NULL, NULL, NULL, NULL);

	dc.Rectangle(0, 0, 50, 50);
	dc.Ellipse(1, 1, 9, 9);

	m_hmf = dc.CloseEnhanced();*/
}

CChildView::~CChildView()
{
	//::DeleteEnhMetaFile(m_hmf);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), (HBRUSH)GetStockObject(GRAY_BRUSH), nullptr);
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			dc.SetPixelV(i, j, RGB(i, j, 0));
		}
	}

	CRect rect;
	GetClientRect(&rect);

	dc.MoveTo(0, rect.bottom / 2);
	dc.LineTo(rect.right, rect.bottom / 2);
	dc.MoveTo(rect.right / 2, 0);
	dc.LineTo(rect.right / 2, rect.bottom);

	dc.SetBkMode(OPAQUE);
	dc.TextOut(100, 50, CString(" OPAQUE 모드 [1] "));

	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(100, 100, CString(" TRANSPARENT 모드 "));

	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(RGB(0, 255, 0));
	dc.TextOut(100, 150, CString(" OPAQUE 모드 [2] "));

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);
	CBrush brush(&bitmap);
	dc.SelectObject(&brush);
	dc.RoundRect(450, 50, 600, 200, 50, 50);

	//GetClientRect(&rect);
	//CBrush brush2(HS_CROSS, RGB(0, 255, 0));
	//dc.SelectObject(&brush2);
	//dc.Rectangle(&rect);

	dc.SelectStockObject(BLACK_PEN);
	dc.SelectStockObject(NULL_BRUSH);
	dc.Ellipse(100, 50, 200, 200);

	dc.SelectStockObject(NULL_PEN);
	dc.SelectStockObject(LTGRAY_BRUSH);
	POINT points[] = { {250.50}, {450,150}, {300,200}, {250,150} };
	dc.Polygon(points, 4);

	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(300, 300, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	dc.StretchBlt(500, 500, bmpinfo.bmWidth * 4, bmpinfo.bmHeight / 2, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



//void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CClientDC dc(this);
//	dc.Rectangle(point.x, point.y, point.x + 10, point.y + 10);
//
//	CWnd::OnLButtonDown(nFlags, point);
//}
//
//
//void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CClientDC dc(this);
//	dc.Ellipse(point.x, point.y, point.x + 10, point.y + 10);
//
//	CWnd::OnRButtonDown(nFlags, point);
//}
