
// FaceRDlg.h : ͷ�ļ�
//

#pragma once
#include "dev/window/mainwindow.h"
// CFaceRDlg �Ի���
class CFaceRDlg : public CDialogEx,
	public MainWindow<CFaceRDlg>
{
// ����
public:
	CFaceRDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CFaceRDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACER10_DIALOG };
#endif



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnClose();

	HANDLE hThread;   //�߳�
	DWORD ThreadID;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	
	BOOL Stop;
	void DrawcvMat(cv::Mat m_cvImg, UINT ID);//��ʾmat��picture�ؼ���
	cv::Mat Coppy;
	afx_msg void OnBnClickedButton3();
	
};
void ThreadFunc(CFaceRDlg *m_dlg);