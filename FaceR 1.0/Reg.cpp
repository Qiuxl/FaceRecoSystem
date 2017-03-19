// Reg.cpp : 实现文件
//

#include "stdafx.h"
#include "Reg.h"
#include "FaceRDlg.h"


// CReg 对话框

IMPLEMENT_DYNAMIC(CReg, CDialog)

CReg::CReg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_REG, pParent)
{
}

CReg::~CReg()
{
}

void CReg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CReg::OnInitDialog()
{
	SetWindowText(TEXT("注册"));
	LPRECT rect = new tagRECT;

	GetWindowRect(rect);
	rect->left += 700;
	rect->right += 700;
	MoveWindow(rect, 1);
	return 0;
}


BEGIN_MESSAGE_MAP(CReg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CReg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CReg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CReg 消息处理程序


//采样按钮
void CReg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString id, name;
	GetDlgItem(IDC_ID)->GetWindowText(id);
	GetDlgItem(IDC_NAME)->GetWindowText(name);
	if (Number <= 0)
	{
		MessageBoxW(TEXT("采样已达5张！可完成注册！"), TEXT("WARING!"), MB_OK);
		return;
	}
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


void CReg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstr;
	if (Number > 0) {
		cstr.Format(_T("请再采样%d张以上照片！"), Number);
		MessageBoxW(cstr, TEXT("WARNING!"), MB_OK);
	}
	else {
		CString id, name;
		GetDlgItem(IDC_ID)->GetWindowText(id);
		GetDlgItem(IDC_NAME)->GetWindowText(name);
		USES_CONVERSION;
		CallRegEndCommand(std::string(T2CA(id)), std::string(T2CA(name)));
		EndDialog(0);
	}
}

void CReg::set_number(int n)
{
	Number = n;
}

void CReg::decrease_number()
{
	Number--;
}