#include "stdafx.h"
#include"figure.h"

void CFigure::Draw(CDC*pdc)
{
}
void CFigure::Load(CArchive& ar)
{
	ar>>Begin;
	ar>>End;

}
void CFigure::Save(CArchive& ar)
{
	ar<<Begin;
	ar<<End;

}
void CMyLine::Load(CArchive& ar)
{
	CFigure::Load(ar);
	ar.Read(&bi, sizeof(LOGPEN));
}
void CMyLine::Save(CArchive& ar)
{
	CFigure::Save(ar);
	ar.Write(&bi, sizeof(LOGPEN));	
}
void CMyElipse::Load(CArchive& ar)
{
	CFigure::Load(ar);
	ar.Read(&bi, sizeof(LOGPEN));
	ar.Read(&shua, sizeof(LOGBRUSH));
}
void CMyElipse::Save(CArchive& ar)
{
	CFigure::Save(ar);
	ar.Write(&bi, sizeof(LOGPEN));
	ar.Write(&shua, sizeof(LOGBRUSH));	
}
void CMyRect::Load(CArchive& ar)
{
	CFigure::Load(ar);
	ar.Read(&bi, sizeof(LOGPEN));
	ar.Read(&shua, sizeof(LOGBRUSH));
}
void CMyRect::Save(CArchive& ar)
{
	CFigure::Save(ar);
	ar.Write(&bi, sizeof(LOGPEN));
	ar.Write(&shua, sizeof(LOGBRUSH));	
}
void CMyText::Load(CArchive& ar)
{
	CFigure::Load(ar);
	ar.Read(&bi, sizeof(LOGPEN));
	ar.Read(&ziti, sizeof(LOGFONT));
	ar>>wenzi;
}
void CMyText::Save(CArchive& ar)
{
	CFigure::Save(ar);
	ar.Write(&bi, sizeof(LOGPEN));
	ar.Write(&ziti, sizeof(LOGFONT));
	ar<<wenzi;	
}
void CMyLine::Draw(CDC*pdc)
{
	 CPen pen;
	pen.CreatePenIndirect(&bi);
	CPen *pold;
	pold = pdc->SelectObject(&pen);
	pdc->MoveTo(Begin);//»­Ïß
	pdc->LineTo(End);
	pdc->SelectObject(pold);
	//delete &pen;
}
void CMyRect::Draw(CDC*pdc)
{
	CPen pen;
	pen.CreatePenIndirect(&bi);
	CPen *pold;
	pold = pdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateBrushIndirect(&shua);
	CBrush *poldbrush;
	poldbrush = pdc->SelectObject(&brush);
	pdc->Rectangle(Begin.x,Begin.y,End.x,End.y);//»­¾ØÐÎ
	pdc->SelectObject(pold);
	pdc->SelectObject(poldbrush);
	/*delete &pen;
	delete &brush;*/
}
void CMyElipse::Draw(CDC*pdc)
{
	CPen pen;
	pen.CreatePenIndirect(&bi);
	CPen *pold;
	pold = pdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateBrushIndirect(&shua);
	CBrush *poldbrush;
	poldbrush = pdc->SelectObject(&brush);
	pdc->Ellipse(Begin.x,Begin.y,End.x,End.y);//»­ÍÖÔ²
	pdc->SelectObject(pold);
	pdc->SelectObject(poldbrush);
	/*delete &pen;
	delete &brush;*/
}
void CMyText::Draw(CDC*pdc)
{
	CPen pen;
	pen.CreatePenIndirect(&bi);
	CPen *pold;
	pold = pdc->SelectObject(&pen);
	CFont font;
	font.CreateFontIndirect(&ziti);
	CFont *poldfont;
	poldfont = pdc->SelectObject(&font);
	CRect rect(Begin.x,Begin.y,End.x,End.y);//»­ÎÄ×Ö
	pdc->TextOutA(Begin.x,Begin.y,wenzi);
	pdc->SelectObject(pold);
	pdc->SelectObject(poldfont);
	/*delete &pen;
	delete &font;*/
}
 void  CMyText:: changefont(LOGFONT* a,COLORREF b,POINT c,POINT d)
 {
	 ziti = *a;
	 bi.lopnColor=b;
	 Begin=c;
	 End=d;
 }
 void  CFigure::changefont(LOGFONT* a,COLORREF b,POINT c,POINT d){ };
LOGFONT  CFigure:: getfont(){

LOGFONT A;
	::ZeroMemory(&A,sizeof(A));
		A.lfHeight=30;
		A.lfWeight=FW_BOLD;
		A.lfItalic=FALSE;
		A.lfWidth=30;
		::lstrcpyA(A.lfFaceName,_T("ËÎÌå"));
return A;
};
  LOGFONT  CMyText:: getfont()
	  {

		  return ziti;
  };
   CString CFigure:: getstr(){CString a="";return a;};
  CString  CMyText:: getstr(){return wenzi;};