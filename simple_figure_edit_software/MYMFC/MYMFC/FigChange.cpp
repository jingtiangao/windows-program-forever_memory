// FigChange.cpp : 实现文件
//

#include "stdafx.h"
#include "MYMFC.h"
#include "FigChange.h"
#include "afxdialogex.h"


// CFigChange 对话框

IMPLEMENT_DYNAMIC(CFigChange, CDialogEx)

CFigChange::CFigChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFigChange::IDD, pParent)
{

}

CFigChange::~CFigChange()
{
}

void CFigChange::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX,IDC_X,x);
	DDX_Text(pDX,IDC_Y,y);
	DDX_Text(pDX,IDC_SIZE,size);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFigChange, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFigChange::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_COR, &CFigChange::OnBnClickedCor)
	ON_BN_CLICKED(IDC_COR2, &CFigChange::OnBnClickedCor2)
	ON_BN_CLICKED(IDC_FON, &CFigChange::OnBnClickedFon)
END_MESSAGE_MAP()


// CFigChange 消息处理程序


void CFigChange::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFigChange::OnBnClickedCor()
{
	CColorDialog cor;
	if(cor.DoModal())
	{
	cc=cor.GetColor();
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CFigChange::OnBnClickedCor2()
{
	// TODO: 在此添加控件通知处理程序代码
		CColorDialog cor2;
		if(cor2.DoModal())
		{
		dd=cor2.GetColor();
		}
		
}


void CFigChange::OnBnClickedFon()
{
	CFontDialog fon;
	if(fon.DoModal())
	{
		ff=*fon.m_cf.lpLogFont;

		
	}
	// TODO: 在此添加控件通知处理程序代码
}
