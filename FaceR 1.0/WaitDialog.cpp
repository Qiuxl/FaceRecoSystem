// WaitDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FaceR 1.0.h"
#include "WaitDialog.h"
#include "afxdialogex.h"


// WaitDialog 对话框

IMPLEMENT_DYNAMIC(WaitDialog, CDialog)

WaitDialog::WaitDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WAITDIALOG, pParent)
{

}

WaitDialog::~WaitDialog()
{
}

void WaitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WaitDialog, CDialog)
END_MESSAGE_MAP()


// WaitDialog 消息处理程序
