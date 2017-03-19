// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Login.h"
#include "WaitDialog.h"

// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CLogin::OnInitDialog()
{
	SetWindowText(TEXT("��¼"));
	LPRECT rect = new tagRECT;

	GetWindowRect(rect);
	rect->left += 700;
	rect->right += 700;
	MoveWindow(rect, 1);
	return 0;
}

BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnLoginClicked)
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


void CLogin::OnBnLoginClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LoginSuccess = false;
	TryNum = 5;
	
//	WaitDialog *dlg = new WaitDialog;
//	dlg->Create(AFX_IDD_EMPTYDIALOG);
//	dlg->CenterWindow(this);
//	dlg->ShowWindow(SW_SHOW);
	
	while (!LoginSuccess && TryNum > 0)
	{
		CallLogin();
	}
//	dlg->EndDialog(0);
	if (LoginSuccess)
	{
		MessageBoxW(TEXT("��¼�ɹ�"), TEXT("INFORMATION!"), MB_OK);
	}
	else
	{
		MessageBoxW(TEXT("��¼ʧ��"), TEXT("INFORMATION!"), MB_OK);
	}
}

void CLogin::CallLogin()
{
	CString id, name;
	GetDlgItem(IDC_ID)->GetWindowText(id);   
	GetDlgItem(IDC_NAME)->GetWindowText(name);
	if (id.IsEmpty())
	{
		MessageBoxW(TEXT("������ѧ�ţ�"), TEXT("WARING!"), MB_OK);
		return;
	}
	if (name.IsEmpty())
	{
		MessageBoxW(TEXT("������������"), TEXT("WARING!"), MB_OK);
		return;
	}
	if (!frame.data) {
		MessageBoxW(TEXT("�������ͷ��"), TEXT("WARING!"), MB_OK);
		return;
	}
	USES_CONVERSION;
	CallSampleCommand(std::string(T2CA(id)), frame);
}


void CLogin::set_TryNum(int n)
{
	TryNum = n;
}

void CLogin::decrease_TryNum()
{
	TryNum--;
}

void CLogin::set_Login_status(bool status)
{
	LoginSuccess = status;
}
