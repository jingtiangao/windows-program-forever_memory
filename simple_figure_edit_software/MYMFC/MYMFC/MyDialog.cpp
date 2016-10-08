// MyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MYMFC.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include "resource.h"


// CMyDialog 对话框

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX,IDC_EDIT1,text);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
END_MESSAGE_MAP()


// CMyDialog 消息处理程序
