#pragma once


// WaitDialog �Ի���

class WaitDialog : public CDialog
{
	DECLARE_DYNAMIC(WaitDialog)

public:
	WaitDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WaitDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAITDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
