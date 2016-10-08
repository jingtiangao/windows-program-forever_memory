
// MYMFCDoc.cpp : CMYMFCDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CMYMFCDoc ����/����

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
		::lstrcpyA(CF.lfFaceName,_T("����"));
	// TODO: �ڴ����һ���Թ������

}

CMYMFCDoc::~CMYMFCDoc()
{
}

BOOL CMYMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;	
	ClearBuffer();
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

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


// CMYMFCDoc ���л�

void CMYMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
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
		// TODO: �ڴ���Ӽ��ش���
		ClearBuffer();//ÿ�δ򿪵�ʱ��Ҫɾ��һ��ͼԪ
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

// ����ͼ��֧��
void CMYMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CMYMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CMYMFCDoc ���

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


// CMYMFCDoc ����
