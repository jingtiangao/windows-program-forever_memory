// FigChange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MYMFC.h"
#include "FigChange.h"
#include "afxdialogex.h"


// CFigChange �Ի���

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


// CFigChange ��Ϣ�������


void CFigChange::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFigChange::OnBnClickedCor()
{
	CColorDialog cor;
	if(cor.DoModal())
	{
	cc=cor.GetColor();
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFigChange::OnBnClickedCor2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
