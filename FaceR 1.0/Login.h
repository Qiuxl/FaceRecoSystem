#pragma once
#include "dev/window/LoginWindow.h"

// CLogin 对话框
extern cv::Mat frame;
class CLogin : public CDialog,
	public LoginWindow<CLogin>
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	bool LoginSuccess;
	int TryNum;
	DECLARE_MESSAGE_MAP()
public:
	void CallLogin();
	afx_msg void OnBnLoginClicked();
	void set_TryNum(int);
	void decrease_TryNum();
	void set_Login_status(bool);

	//void DrawcvMat(cv::Mat m_cvImg, UINT ID);//显示mat在picture控件中
	cv::Mat Coppy;
};