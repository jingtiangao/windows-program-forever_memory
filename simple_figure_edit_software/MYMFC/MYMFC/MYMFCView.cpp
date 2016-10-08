
// MYMFCView.cpp : CMYMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MYMFC.h"
#endif
#include "MainFrm.h"
#include "MYMFCDoc.h"
#include "MYMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMYMFCView

IMPLEMENT_DYNCREATE(CMYMFCView, CView)

BEGIN_MESSAGE_MAP(CMYMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMYMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_ONELINE, &CMYMFCView::OnOneline)
	ON_COMMAND(ID_TXTCOLOR, &CMYMFCView::OnTxtcolor)
	ON_COMMAND(IDP_LINE, &CMYMFCView::OnIdpLine)
	ON_COMMAND(IDP_RECT, &CMYMFCView::OnIdpLine)
	ON_COMMAND(IDP_ELIPSE, &CMYMFCView::OnIdpLine)
	ON_COMMAND(IDP_TXT, &CMYMFCView::OnIdpLine)
	ON_COMMAND(ID_DEL, &CMYMFCView::OnDel)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_LC, &CMYMFCView::OnLc)
	ON_COMMAND(ID_TC, &CMYMFCView::OnTc)
	ON_COMMAND(ID_CF, &CMYMFCView::OnCf)
END_MESSAGE_MAP()

// CMYMFCView 构造/析构

CMYMFCView::CMYMFCView()
{
	// TODO: 在此处添加构造代码

}

CMYMFCView::~CMYMFCView()
{
}

BOOL CMYMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMYMFCView 绘制

void CMYMFCView::OnDraw(CDC* pDC)
{
	CMYMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/*pDC->SetTextColor(pDoc->color);
	pDC->TextOut(120,80, "Hello, it's 高楚阳的MFC");
	pDC->MoveTo(100, 100);	pDC->LineTo(300,100);*/
	for(int i=0;i<pDoc->pic.GetCount();i++)
	{
		pDoc->pic[i]->Draw(pDC);
	}


	// TODO: 在此处为本机数据添加绘制代码
}


// CMYMFCView 打印


void CMYMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMYMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMYMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMYMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMYMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	CMYMFCDoc* pDoc = GetDocument();
	for(int i =0;i<pDoc->pic.GetSize();i++)
	{
		if((point.x>pDoc->pic[i]->Begin.x&&point.y>pDoc->pic[i]->Begin.y&&point.x<pDoc->pic[i]->End.x
			&&point.y<pDoc->pic[i]->End.y)||(point.x<pDoc->pic[i]->Begin.x&&point.y>pDoc->pic[i]->Begin.y&&point.x>pDoc->pic[i]->End.x
			&&point.y<pDoc->pic[i]->End.y))
		{
			CFigChange change;
			change.x=pDoc->pic[i]->Begin.x;
			change.y=pDoc->pic[i]->Begin.y;
			change.size=1;
			change.cc=pDoc->pic[i]->bi.lopnColor;
			change.dd=pDoc->pic[i]->shua.lbColor;
			change.ff=pDoc->pic[i]->getfont();
			switch(change.DoModal())
			{
				case IDOK:
					{
						int a,b;
						POINT S;
						POINT E;
						a=pDoc->pic[i]->End.x-pDoc->pic[i]->Begin.x;
						b=pDoc->pic[i]->End.y-pDoc->pic[i]->Begin.y;
						S.x=change.x;
						S.y=change.y;			
						E.x=change.x+change.size*a;
						E.y=change.y+change.size*b;
								switch (pDoc->pic[i]->iType)
									{
									case DRAWMODE_LINE:
										
										delete pDoc->pic[i];
										pDoc->pic.SetAtGrow(i,new CMyLine(S,E,change.cc));
										break;
									case DRAWMODE_RECT:
										delete pDoc->pic[i];
										pDoc->pic.SetAtGrow(i,new CMyRect(S,E,change.cc,change.dd));
										break;
									case DRAWMODE_ELIPSE:
										delete pDoc->pic[i];
										pDoc->pic.SetAtGrow(i,new CMyElipse(S,E,change.cc,change.dd));
										break;
				
									case DRAWMODE_TEXT:
										{
											
											/*E.x=change.ff.lfWidth*pDoc->pic[i]->getstr().GetLength()
												+pDoc->pic[i]->Begin.x;
											E.y=pDoc->pic[i]->Begin.y+change.ff.lfHeight;*/
										pDoc->pic[i]->changefont(&change.ff,change.cc,S,E);
										Invalidate();
										CDC* dc;
										dc=GetDC();
										CSize si =dc->GetTextExtent(pDoc->pic[i]->getstr());
										E.x=S.x+si.cx;
										E.y=S.y+si.cy;
										pDoc->pic[i]->changefont(&change.ff,change.cc,S,E);

										break;
										}
									}//内部SWITCH

						break;
					}
			}//switc结束
			Invalidate();
		}//if结束

	}//for循环结束
	

	/*ClientToScreen(&point);
	OnContextMenu(this, point);*/
}//RBUTTON结束

void CMYMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMYMFCView 诊断

#ifdef _DEBUG
void CMYMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMYMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMYMFCDoc* CMYMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYMFCDoc)));
	return (CMYMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMYMFCView 消息处理程序


void CMYMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	   //CString string;

	   //string.AppendFormat("x坐标 %d  y坐标 %d",point.x, point.y); //将变量组装到字符串中

    //   MessageBox(string,"横纵坐标");
	CMYMFCDoc* pDoc = GetDocument();
	pDoc->m_ptSInput=point;
	pDoc->m_bDrawing=TRUE;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMYMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMYMFCDoc* pDoc = GetDocument();
	pDoc->m_ptEInput=point;
	CFigure * pFig = NULL;
	if(pDoc->m_bDrawing)
	{
		pDoc->m_bDrawing = FALSE;
		ReleaseCapture();
		
		switch(pDoc->ID)
		{
		case IDP_LINE:
			pFig=new CMyLine(pDoc->m_ptSInput,point,pDoc->LC);
	/*		pFig->Begin=pDoc->m_ptSInput;
			pFig->End=point;*/
		
			break;
		case IDP_ELIPSE:
			pFig=new CMyElipse(pDoc->m_ptSInput,point,pDoc->LC,pDoc->TC);
		/*	pFig->Begin=pDoc->m_ptSInput;
			pFig->End=point;*/
		
			break;
		case IDP_TXT:
			{
				
				CMyDialog dlg;
				if(dlg.DoModal()==IDOK)
				{
					pFig = new CMyText(pDoc->m_ptEInput ,dlg.text,pDoc->CF);
					
				}	
				break;
			}
		case IDP_RECT:
			
			
			pFig=new CMyRect(pDoc->m_ptSInput,point,pDoc->LC,pDoc->TC);
	/*		pFig->Begin=pDoc->m_ptSInput;
			pFig->End=point;*/
			break;
		}
	}

	if (pFig != NULL)
		{
			
			pDoc->pic.Add(pFig);
			pDoc->SetModifiedFlag();

			Invalidate();
		}

	CView::OnLButtonUp(nFlags, point);
}


void CMYMFCView::OnOneline()
{
	
  CDC* dc=GetDC();
  dc->MoveTo(100,100);
  dc->LineTo(300,300);
  ReleaseDC(dc);
	
	// TODO: 在此添加命令处理程序代码
}


void CMYMFCView::OnTxtcolor()
{
	CMYMFCDoc* pDoc = GetDocument();
	CColorDialog  txtcolor;
	if(txtcolor.DoModal()==IDOK)
	{
		pDoc->color=txtcolor.GetColor();
	}
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}


void CMYMFCView::OnIdpLine()

{
	CMYMFCDoc* pDoc = GetDocument();
	pDoc->ID=LOWORD(GetCurrentMessage()->wParam);
	// TODO: 在此添加命令处理程序代码
}


void CMYMFCView::OnDel()
{
	CMYMFCDoc* pDoc = GetDocument();
	int nsize=pDoc->pic.GetSize();
	for(int i=0;i<nsize;i++)
	{
		delete pDoc->pic[i];
		TRACE0("~~~~\n");
	}
	pDoc->pic.RemoveAll();
	pDoc->SetModifiedFlag();
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}


void CMYMFCView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMYMFCDoc* pDoc = GetDocument();
	for(int i =0;i<pDoc->pic.GetSize();i++)
	{
		if((point.x>pDoc->pic[i]->Begin.x&&point.y>pDoc->pic[i]->Begin.y&&point.x<pDoc->pic[i]->End.x
			&&point.y<pDoc->pic[i]->End.y)||(point.x<pDoc->pic[i]->Begin.x&&point.y>pDoc->pic[i]->Begin.y&&point.x>pDoc->pic[i]->End.x
			&&point.y<pDoc->pic[i]->End.y))
		{
			delete pDoc->pic[i];
			pDoc->pic.RemoveAt(i);
		}
	}
		Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CMYMFCView::OnLc()
{
	// TODO: 在此添加命令处理程序代码
	CMYMFCDoc* pDoc = GetDocument();
	CColorDialog ccc1;
		if(ccc1.DoModal())
		{
		pDoc->LC=ccc1.GetColor();
		}
}


void CMYMFCView::OnTc()
{
		CMYMFCDoc* pDoc = GetDocument();
		CColorDialog ccc2;
		if(ccc2.DoModal())
		{
		pDoc->TC=ccc2.GetColor();
		}
	// TODO: 在此添加命令处理程序代码
}


void CMYMFCView::OnCf()
{
	// TODO: 在此添加命令处理程序代码
	CMYMFCDoc* pDoc = GetDocument();
	CFontDialog fon1;
	if(fon1.DoModal())
	{
	pDoc->CF=*fon1.m_cf.lpLogFont;

		
	}
}
