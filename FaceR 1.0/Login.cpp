// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Login.h"
#include "WaitDialog.h"

// CLogin 对话框

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
	SetWindowText(TEXT("登录"));
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


// CLogin 消息处理程序


void CLogin::OnBnLoginClicked()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBoxW(TEXT("登录成功"), TEXT("INFORMATION!"), MB_OK);
	}
	else
	{
		MessageBoxW(TEXT("登录失败"), TEXT("INFORMATION!"), MB_OK);
	}
}

void CLogin::CallLogin()
{
	CString id, name;
	GetDlgItem(IDC_ID)->GetWindowText(id);   
	GetDlgItem(IDC_NAME)->GetWindowText(name);
	if (id.IsEmpty())
	{
		MessageBoxW(TEXT("请输入学号！"), TEXT("WARING!"), MB_OK);
		return;
	}
	if (name.IsEmpty())
	{
		MessageBoxW(TEXT("请输入姓名！"), TEXT("WARING!"), MB_OK);
		return;
	}
	if (!frame.data) {
		MessageBoxW(TEXT("请打开摄像头！"), TEXT("WARING!"), MB_OK);
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
