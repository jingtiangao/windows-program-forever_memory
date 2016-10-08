
// MYMFCDoc.cpp : CMYMFCDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MYMFC.h"
#endif

#include "MYMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMYMFCDoc

IMPLEMENT_DYNCREATE(CMYMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CMYMFCDoc, CDocument)
END_MESSAGE_MAP()


// CMYMFCDoc 构造/析构

CMYMFCDoc::CMYMFCDoc()
{
	 color=RGB(255,0,0);
	 LC=RGB(255,0,0);
	 TC=RGB(0,255,0);
	 ::ZeroMemory(&CF,sizeof(CF));

		CF.lfHeight=30;
		CF.lfWidth=30;
		CF.lfWeight=FW_BOLD;
		CF.lfItalic=FALSE;
		::lstrcpyA(CF.lfFaceName,_T("宋体"));
	// TODO: 在此添加一次性构造代码

}

CMYMFCDoc::~CMYMFCDoc()
{
}

BOOL CMYMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;	
	ClearBuffer();
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

void CMYMFCDoc::ClearBuffer()
{
	int nsize=pic.GetSize();
	for(int i=0;i<nsize;i++)
	{
		delete pic[i];
		TRACE0("~~~~\n");
	}
	pic.RemoveAll();

}


// CMYMFCDoc 序列化

void CMYMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		int iCount=pic.GetSize();
		ar<<iCount;
		for(int i=0;i<iCount;i++)
		{
			ar<<pic[i]->iType;
			pic[i]->Save(ar);
		}

	}
	else
	{
		// TODO: 在此添加加载代码
		ClearBuffer();//每次打开的时候都要删除一次图元
		int iCount =0; 
		ar >> iCount;
		for(int i=0;i<iCount;i++)
		{
			CFigure* pFig=NULL;
			int mType;
			ar>>mType;
			switch(mType)
			{
			case DRAWMODE_LINE:		pFig = new CMyLine(); break;
			case DRAWMODE_RECT:		pFig = new CMyRect(); break;
			case DRAWMODE_ELIPSE:	pFig = new CMyElipse(); break;
			case DRAWMODE_TEXT:		pFig = new CMyText(); break;
			}
			if (pFig != NULL)
			{
				pFig->Load(ar);
				pic.Add(pFig);
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMYMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMYMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMYMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMYMFCDoc 诊断

#ifdef _DEBUG
void CMYMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMYMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMYMFCDoc 命令
