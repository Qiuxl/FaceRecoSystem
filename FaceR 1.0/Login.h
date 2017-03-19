#pragma once
#include "dev/window/LoginWindow.h"

// CLogin �Ի���
extern cv::Mat frame;
class CLogin : public CDialog,
	public LoginWindow<CLogin>
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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

	//void DrawcvMat(cv::Mat m_cvImg, UINT ID);//��ʾmat��picture�ؼ���
	cv::Mat Coppy;
};