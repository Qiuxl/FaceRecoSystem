#pragma once

#include "dev/window/regwindow.h"
// CReg �Ի���
extern cv::Mat frame;
class CReg : public CDialog,
	public RegWindow<CReg>
{
	DECLARE_DYNAMIC(CReg)

public:
	CReg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	int Number;

	DECLARE_MESSAGE_MAP()
public:
	CDialog dlg;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void decrease_number();
	void set_number(int);
};