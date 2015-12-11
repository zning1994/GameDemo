
// GameDemoView.cpp : CGameDemoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GameDemo.h"
#endif

#include "GameDemoDoc.h"
#include "GameDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDemoView

IMPLEMENT_DYNCREATE(CGameDemoView, CView)

BEGIN_MESSAGE_MAP(CGameDemoView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGameDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGameDemoView ����/����

CGameDemoView::CGameDemoView()
{
	// TODO: �ڴ˴���ӹ������

}

CGameDemoView::~CGameDemoView()
{
}

BOOL CGameDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGameDemoView ����

void CGameDemoView::OnDraw(CDC* /*pDC*/)
{
	CGameDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGameDemoView ��ӡ


void CGameDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGameDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGameDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGameDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGameDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameDemoView ���

#ifdef _DEBUG
void CGameDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGameDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDemoDoc* CGameDemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDemoDoc)));
	return (CGameDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameDemoView ��Ϣ�������


int CGameDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(1, 100, 0);
	CMe::LoadImage();
	return 0;
}


void CGameDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDC();

	//ÿ��ִ�У�ˢ�´��������Ӷ�ʵ��ǰ������ɵ����������¡�Ӱ�ۡ�
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);

	//����ս��ͼƬ
	//CMe::LoadImage();
	me.Draw(pDC, FALSE);

	short key = GetKeyState(VK_RIGHT);
	if ((key & 0x80) != 0)
	{
		me.SetHorMotion(1);
	}

	/*ֻ����һ�ܷɻ�
	if (listMe.GetCount() > 0)
	{
		CMe *pMe = (CMe*)listMe.GetTail();
		pMe->Draw(pDC, FALSE);
	}
	*/

	/*����COBList ����*/
	POSITION posMe = listMe.GetHeadPosition();
	for (posMe = listMe.GetHeadPosition(); posMe != NULL;)
	{
		CMe *pMe = (CMe*)listMe.GetNext(posMe);
		pMe->SetVerMotion(-1);
		pMe->Draw(pDC, FALSE);
		//��ըʾ��
		CRect intersectrect;
		pDC->Rectangle(100, 500, 150, 560);
		int intersectsection = intersectrect.IntersectRect(pMe->GetRect(), CRect(100,500,150,560));
		if (intersectsection != 0)
		{
			pDC->TextOutW(100, 100, _T("��ѽ�������ˣ�����"));//��ʾ��ըЧ��
			//��������ɾ�����ͷű�ը�˵Ķ���
		}
	}
	
	
	

	ReleaseDC(pDC);//�ͷŲ���Ҫ���ڴ�

	CView::OnTimer(nIDEvent);
}


void CGameDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_SPACE)
		listMe.AddTail(new CMe());
	if (nChar == VK_DOWN)
		me.SetVerMotion(-1);
	if (nChar == VK_UP)
		me.SetVerMotion(1);
	if (nChar == VK_LEFT)
		me.SetHorMotion(-1);
	if (nChar == VK_RIGHT)
		me.SetHorMotion(1);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}