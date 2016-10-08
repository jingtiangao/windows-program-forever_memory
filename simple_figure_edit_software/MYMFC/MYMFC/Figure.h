
#include "StdAfx.h"
#define DRAWMODE_LINE  1000
#define DRAWMODE_RECT  2000
#define DRAWMODE_ELIPSE  3000
#define DRAWMODE_TEXT  4000

class CFigure
{
public: 
	int   iType;
	CPoint Begin;
	CPoint End;
	LOGPEN bi;
	LOGBRUSH shua;
	virtual void Draw(CDC* pdc);
	virtual  void Load(CArchive&ar);
    virtual void  Save(CArchive& ar);
	virtual void  changefont(LOGFONT* a,COLORREF b,POINT c,POINT d);
	virtual   LOGFONT  getfont();
	virtual   CString getstr();

};	
class CMyLine :public CFigure
{
public:
	//LOGPEN bi;
	virtual void Draw(CDC* pdc);
	virtual void Load(CArchive& ar);
	virtual void Save(CArchive& ar);
	CMyLine(POINT a,POINT b,COLORREF c)
	{
		Begin=a;
		End=b;
		bi.lopnColor=c;
		iType=DRAWMODE_LINE;
	
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=10;
		TRACE0("CMyLine\n");
	}
	CMyLine()
	{
		iType=DRAWMODE_LINE;
		bi.lopnColor=RGB(255,0,0);
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=10;
		TRACE0("CMyLine\n");
	}
	~CMyLine()
	{
	TRACE0("~CMyLine\n");
	}
};
class CMyRect :public CFigure
{
public:
	//LOGPEN bi;
	//LOGBRUSH shua;
	virtual void Draw(CDC* pdc);
	virtual void Load(CArchive& ar);
	virtual void Save(CArchive& ar);
	CMyRect(POINT a,POINT b,COLORREF c,COLORREF d)
	{
		Begin=a;
		End=b;
		
		iType=DRAWMODE_RECT;
		bi.lopnColor=c;
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
		shua.lbColor=d;
		shua.lbHatch=HS_CROSS;
		shua.lbStyle=BS_HATCHED;
		TRACE0("CMyRect\n");
	}
	CMyRect()
	{
		iType=DRAWMODE_RECT;
		bi.lopnColor=RGB(255,0,0);
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
		shua.lbColor=RGB(0,255,0);
		shua.lbHatch=HS_CROSS;
		shua.lbStyle=BS_HATCHED;
		TRACE0("CMyRect\n");
	}
	~CMyRect()
	{
	TRACE0("~CMyRect\n");
	}
};
class CMyElipse :public CFigure
{
public:
	//LOGPEN bi;
	//LOGBRUSH shua;
	virtual void Draw(CDC* pdc);
	virtual void Load(CArchive& ar);
	virtual void Save(CArchive& ar);
	CMyElipse(POINT a,POINT b,COLORREF c,COLORREF d)
	{
		Begin=a;
		End=b;
	
		iType=DRAWMODE_ELIPSE;
		bi.lopnColor=c;
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
		shua.lbColor=d;
		shua.lbHatch=HS_CROSS;
		shua.lbStyle=BS_HATCHED;
		TRACE0("CMyElipse\n");

	}
	CMyElipse()
	{
		iType=DRAWMODE_ELIPSE;
		bi.lopnColor=RGB(255,0,0);
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
		shua.lbColor=RGB(0,255,0);
		shua.lbHatch=HS_CROSS;
		shua.lbStyle=BS_HATCHED;
		TRACE0("CMyElipse\n");

	}
	~CMyElipse()
	{
	TRACE0("~CMyElipse\n");
	}

};
class CMyText :public CFigure
{
public:
	//LOGPEN bi;
	LOGFONT ziti;
	CString wenzi;
	virtual void Draw(CDC* pdc);
	virtual void Load(CArchive& ar);
	virtual void Save(CArchive& ar);
	virtual void  changefont(LOGFONT* a,COLORREF b,POINT c,POINT d);
	virtual  LOGFONT  getfont();
	virtual  CString  getstr();

	CMyText()
	{
		iType=DRAWMODE_TEXT;
		bi.lopnColor=RGB(255,0,0);
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
		::ZeroMemory(&ziti,sizeof(ziti));
		
		ziti.lfHeight=30;
		ziti.lfWeight=FW_BOLD;
		ziti.lfItalic=FALSE;
		::lstrcpyA(ziti.lfFaceName,_T("ËÎÌו"));
		TRACE0("CMyText\n");
	}
	CMyText(POINT pt1, CString str,LOGFONT B)
	{
		
		
		iType=DRAWMODE_TEXT;
		bi.lopnColor=RGB(255,0,0);
		bi.lopnStyle=PS_SOLID;
		bi.lopnWidth.x=1;
	/*	::ZeroMemory(&ziti,sizeof(ziti));

		ziti.lfHeight=30;
		ziti.lfWidth=30;
		ziti.lfWeight=FW_BOLD;
		ziti.lfItalic=FALSE;
		::lstrcpyA(ziti.lfFaceName,_T("ËÎÌו"));*/
		ziti=B;
		TRACE0("CMyText\n");
		Begin = pt1;
		End.x=ziti.lfWidth*str.GetLength()+Begin.x;
		End.y=Begin.y+ziti.lfHeight;
		wenzi = str;
	}
	~CMyText()
	{
	TRACE0("~CMyText\n");
	}
};