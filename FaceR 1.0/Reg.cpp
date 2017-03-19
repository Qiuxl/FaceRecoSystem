// Reg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Reg.h"
#include "FaceRDlg.h"


// CReg �Ի���

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
	SetWindowText(TEXT("ע��"));
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


// CReg ��Ϣ�������


//������ť
void CReg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString id, name;
	GetDlgItem(IDC_ID)->GetWindowText(id);
	GetDlgItem(IDC_NAME)->GetWindowText(name);
	if (Number <= 0)
	{
		MessageBoxW(TEXT("�����Ѵ�5�ţ������ע�ᣡ"), TEXT("WARING!"), MB_OK);
		return;
	}
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


void CReg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cstr;
	if (Number > 0) {
		cstr.Format(_T("���ٲ���%d��������Ƭ��"), Number);
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