// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include <iostream>
#include "gPrjDlg.h"

using namespace std;

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Origin Image"));
	InitImage();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
	
	drawData(&dc);
}

void CDlgImage::InitImage() 
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;
	
	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CDlgImage::drawData(CDC* pDC)
{
	// Edit Control에 있는 값 가져오기.
	int nRadius = ((CgPrjDlg*)GetParent())->m_nRadius;

	// 선 색칠하기 
	// 좀 더 자세한 내용.
	// https://m.blog.naver.com/idjoopal/100185800818 
	CPen yellowPen;
	yellowPen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	CPen* pYellowPen = pDC->SelectObject(&yellowPen);

	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();

	int nDrawCircleX = rand() % (nWidth - nRadius);
	int nDrawCircleY = rand() % (nHeight - nRadius);

	// 원 그리기.
	CRect rect(nDrawCircleX, nDrawCircleY, nDrawCircleX + nRadius, nDrawCircleY + nRadius);
	pDC->Ellipse(rect);
	pDC->SelectObject(pYellowPen);

	// 원의 중심 좌표 구하기.
	CPoint centerPos = rect.CenterPoint();

	CBrush redBrush;
	redBrush.CreateSolidBrush(COLOR_RED);
	CBrush* pRedBrush =(CBrush*) pDC->SelectObject(&redBrush);
	
	// 가로 한 줄 그리기 
	CRect rawSquare(centerPos.x - 10, centerPos.y - 20, centerPos.x + 10, centerPos.y + 20);
	pDC->Rectangle(rawSquare);

	// 세로 한 줄 그리기 
	CRect colSquare(centerPos.x - 20, centerPos.y - 10, centerPos.x + 20, centerPos.y + 10);
	pDC->Rectangle(colSquare);

	pDC->SelectObject(pRedBrush);
}