// WaitDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FaceR 1.0.h"
#include "WaitDialog.h"
#include "afxdialogex.h"


// WaitDialog �Ի���

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


// WaitDialog ��Ϣ�������
