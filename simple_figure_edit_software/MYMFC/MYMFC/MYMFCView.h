
// MYMFCView.h : CMYMFCView ��Ľӿ�
//

#pragma once
#include "MyDialog.h"
#include "FigChange.h"

class CMYMFCView : public CView
{
protected: // �������л�����
	CMYMFCView();
	DECLARE_DYNCREATE(CMYMFCView)

// ����
public:
	CMYMFCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMYMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOneline();
	afx_msg void OnTxtcolor();
	afx_msg void OnIdpLine();
	afx_msg void OnDel();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLc();
	afx_msg void OnTc();
	afx_msg void OnCf();
};

#ifndef _DEBUG  // MYMFCView.cpp �еĵ��԰汾
inline CMYMFCDoc* CMYMFCView::GetDocument() const
   { return reinterpret_cast<CMYMFCDoc*>(m_pDocument); }
#endif

