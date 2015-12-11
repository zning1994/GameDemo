
// GameDemoView.cpp : CGameDemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGameDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGameDemoView 构造/析构

CGameDemoView::CGameDemoView()
{
	// TODO: 在此处添加构造代码

}

CGameDemoView::~CGameDemoView()
{
}

BOOL CGameDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGameDemoView 绘制

void CGameDemoView::OnDraw(CDC* /*pDC*/)
{
	CGameDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGameDemoView 打印


void CGameDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGameDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGameDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGameDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CGameDemoView 诊断

#ifdef _DEBUG
void CGameDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGameDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDemoDoc* CGameDemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDemoDoc)));
	return (CGameDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameDemoView 消息处理程序


int CGameDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 100, 0);
	CMe::LoadImage();
	return 0;
}


void CGameDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();

	//每次执行，刷新窗口区，从而实现前景物体飞但并不会留下“影痕”
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);

	//插入战机图片
	//CMe::LoadImage();
	me.Draw(pDC, FALSE);

	short key = GetKeyState(VK_RIGHT);
	if ((key & 0x80) != 0)
	{
		me.SetHorMotion(1);
	}

	/*只处理一架飞机
	if (listMe.GetCount() > 0)
	{
		CMe *pMe = (CMe*)listMe.GetTail();
		pMe->Draw(pDC, FALSE);
	}
	*/

	/*遍历COBList 链表*/
	POSITION posMe = listMe.GetHeadPosition();
	for (posMe = listMe.GetHeadPosition(); posMe != NULL;)
	{
		CMe *pMe = (CMe*)listMe.GetNext(posMe);
		pMe->SetVerMotion(-1);
		pMe->Draw(pDC, FALSE);
		//爆炸示例
		CRect intersectrect;
		pDC->Rectangle(100, 500, 150, 560);
		int intersectsection = intersectrect.IntersectRect(pMe->GetRect(), CRect(100,500,150,560));
		if (intersectsection != 0)
		{
			pDC->TextOutW(100, 100, _T("哎呀，碰上了！！！"));//显示爆炸效果
			//从链表中删除并释放爆炸了的对象。
		}
	}
	
	
	

	ReleaseDC(pDC);//释放不需要的内存

	CView::OnTimer(nIDEvent);
}


void CGameDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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