
// MYMFCDoc.h : CMYMFCDoc ��Ľӿ�
//


#pragma once
#include"figure.h"


class CMYMFCDoc : public CDocument
{

protected: // �������л�����
	CMYMFCDoc();
	DECLARE_DYNCREATE(CMYMFCDoc)

// ����
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
	 
// ����
public:
	void ClearBuffer();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMYMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
