#pragma once

#include "Resource.h"
// CFigChange �Ի���

class CFigChange : public CDialogEx
{
	DECLARE_DYNAMIC(CFigChange)

public:
	CFigChange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFigChange();


// �Ի�������
	enum { IDD = IDD_DIACHA };
	int x;
	int y;
	float size;
	COLORREF cc;
	COLORREF dd;
	LOGFONT ff;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCor();
	afx_msg void OnBnClickedCor2();
	afx_msg void OnBnClickedFon();
};
