#pragma once

#include "Resource.h"
// CFigChange 对话框

class CFigChange : public CDialogEx
{
	DECLARE_DYNAMIC(CFigChange)

public:
	CFigChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFigChange();


// 对话框数据
	enum { IDD = IDD_DIACHA };
	int x;
	int y;
	float size;
	COLORREF cc;
	COLORREF dd;
	LOGFONT ff;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCor();
	afx_msg void OnBnClickedCor2();
	afx_msg void OnBnClickedFon();
};
