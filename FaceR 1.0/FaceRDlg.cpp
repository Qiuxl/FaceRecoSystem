
// FaceRDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FaceR 1.0.h"
#include "FaceRDlg.h"
#include "Reg.h"
#include "Login.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg 
extern cv::Mat frame;
extern FileManager Fm;
extern BOOL m_bRun;
extern CReg reg;
extern CLogin login;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//��ͼƬ�ؼ���ʾһ֡
void CFaceRDlg::DrawcvMat(cv::Mat m_cvImg, UINT ID)
{
	cv::Mat img;
	cv::Mat temp;
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	cv::Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	cv::resize(m_cvImg, img, cv::Size(rect.Width(), rect.Height()));
	//cv::resize(m_cvImg, temp, cv::Size(200, 150));
	//cv::imshow("�������",temp);

	cvWaitKey(0);
	unsigned int m_buffer[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
	BITMAPINFO* m_bmi = (BITMAPINFO*)m_buffer;
	BITMAPINFOHEADER* m_bmih = &(m_bmi->bmiHeader);
	memset(m_bmih, 0, sizeof(*m_bmih));
	m_bmih->biSize = sizeof(BITMAPINFOHEADER);
	m_bmih->biWidth = img.cols;
	m_bmih->biHeight = -img.rows;           // �����¶��ϵ�λͼ�� �߶�Ϊ��
	m_bmih->biPlanes = 1;
	m_bmih->biCompression = BI_RGB;
	m_bmih->biBitCount = 8 * img.channels();

	CDC *pDC = GetDlgItem(ID)->GetDC();
	::StretchDIBits(
		pDC->GetSafeHdc(),
		0, 0, rect.Width(), rect.Height(),
		0, 0, rect.Width(), rect.Height(),
		img.data,
		(BITMAPINFO*)m_bmi,
		DIB_RGB_COLORS,
		SRCCOPY
		);
	ReleaseDC(pDC);
}


//�߳�
void ThreadFunc(CFaceRDlg *m_dlg)
{
	m_bRun = FALSE;
	Sleep(1000);
	cv::VideoCapture camera(0);
	camera.open(0);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	m_bRun = TRUE;
	while (m_bRun)
	{
		camera >> frame;
		m_dlg->DrawcvMat(frame, IDC_PIC);
	
	}
	/*
	CString cstr;
	m_dlg->GetDlgItem(IDC_IDEDIT)->GetWindowText(cstr);
	if (cstr.IsEmpty())
	{
		MessageBox(NULL, TEXT("������ѧ�ţ�"), TEXT("WARING!"), MB_OK);
		return;
	}
	personalInfo Info;
	USES_CONVERSION;
	m_dlg->Fm.initial();
	string str = W2CA((LPCWSTR)cstr);
	Info.sid = str;
	Info.name = "aaa";
	m_dlg->Fm.getStuinfo(Info, Info.sid);
	m_dlg->Fm.writeInfo(Info);
	m_dlg->Fm.close();
	m_dlg->Fm.writeMATtoSource(Info, m_dlg->frame);
	m_bRun = FALSE;
	*/
}


// CFaceRDlg �Ի���
CFaceRDlg::CFaceRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FACER10_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFaceRDlg::~CFaceRDlg()
{
	TerminateProcess(GetCurrentProcess(), 0);
	OnClose();
}





void CFaceRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFaceRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFaceRDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFaceRDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFaceRDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFaceRDlg ��Ϣ�������

BOOL CFaceRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFaceRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFaceRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFaceRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFaceRDlg::OnClose()
{

	TerminateProcess(GetCurrentProcess(), 0);
	
}



void CFaceRDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    m_bRun = FALSE;
	Sleep(100);
	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFunc,
		this,
		0,
		&ThreadID);
	CloseHandle(hThread);
	/*
	int CameraNumber = 0;
	Stop = false;
	cv::VideoCapture camera(CameraNumber);
	camera.open(0);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cv::Mat frame;
	int delay = 1000;

	while (!Stop)
	{
		camera >> frame;
		DrawcvMat(frame, IDC_PIC);
		//imshow("frame",frame);
		//if (cv::waitKey(delay) >= 0)
		//	Stop = true;
		
	}
	*/
	


}


void CFaceRDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	reg.set_number(5);
	MessageBoxW(TEXT("����������5������ȡ����"), TEXT("WARING!"), MB_OK);
	reg.DoModal();

	/*
	CString cstr;
	GetDlgItem(IDC_IDEDIT)->GetWindowText(cstr);
	if (cstr.IsEmpty())
	{
		MessageBoxW(TEXT("������ѧ�ţ�"), TEXT("WARNING!"));
		return;
	}
	if (!(frame.data)) {
		MessageBoxW(TEXT("��������Ƭ��"), TEXT("WARNING!"));
		return;
	}
	m_bRun = FALSE;
	//����ͼƬ
	personalInfo Info;
	USES_CONVERSION;
	Fm.initial();
	string str = W2CA((LPCWSTR)cstr);
	Info.sid = str;
	Info.name = "aaa";
	Fm.getStuinfo(Info, Info.sid);
	Fm.writeInfo(Info);
	Fm.close();
	Fm.writeMATtoSource(Info, frame);
	MessageBoxW(TEXT("�洢�ɹ���"), TEXT("INFORMATION"));
	*/

}




void CFaceRDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	login.set_Login_status(false);
	//5�β�����¼
	login.set_TryNum(5);
	login.DoModal();
}
