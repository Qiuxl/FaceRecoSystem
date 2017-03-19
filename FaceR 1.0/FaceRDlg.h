
// FaceRDlg.h : 头文件
//

#pragma once
#include "dev/window/mainwindow.h"
// CFaceRDlg 对话框
class CFaceRDlg : public CDialogEx,
	public MainWindow<CFaceRDlg>
{
// 构造
public:
	CFaceRDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CFaceRDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACER10_DIALOG };
#endif



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnClose();

	HANDLE hThread;   //线程
	DWORD ThreadID;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	
	BOOL Stop;
	void DrawcvMat(cv::Mat m_cvImg, UINT ID);//显示mat在picture控件中
	cv::Mat Coppy;
	afx_msg void OnBnClickedButton3();
	
};
void ThreadFunc(CFaceRDlg *m_dlg);