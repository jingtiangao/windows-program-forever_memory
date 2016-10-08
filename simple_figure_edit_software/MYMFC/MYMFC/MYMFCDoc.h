
// MYMFCDoc.h : CMYMFCDoc 类的接口
//


#pragma once
#include"figure.h"


class CMYMFCDoc : public CDocument
{

protected: // 仅从序列化创建
	CMYMFCDoc();
	DECLARE_DYNCREATE(CMYMFCDoc)

// 特性
public:
	 COLORREF color;
	 int ID;
	 CMyLine* line;
	 CMyRect* rec;
	 CMyElipse* eli;
	 CMyText* txt;
	 CArray<CFigure*,CFigure*> pic;
	 POINT m_ptSInput;
	 POINT m_ptEInput;
	 bool m_bDrawing;
	 COLORREF LC;
	 COLORREF TC;
	 LOGFONT CF;
	 
// 操作
public:
	void ClearBuffer();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMYMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
