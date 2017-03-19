#pragma once


// WaitDialog 对话框

class WaitDialog : public CDialog
{
	DECLARE_DYNAMIC(WaitDialog)

public:
	WaitDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WaitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAITDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
