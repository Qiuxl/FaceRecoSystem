
// FaceRDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 
extern cv::Mat frame;
extern FileManager Fm;
extern BOOL m_bRun;
extern CReg reg;
extern CLogin login;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

//在图片控件显示一帧
void CFaceRDlg::DrawcvMat(cv::Mat m_cvImg, UINT ID)
{
	cv::Mat img;
	cv::Mat temp;
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	cv::Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	cv::resize(m_cvImg, img, cv::Size(rect.Width(), rect.Height()));
	//cv::resize(m_cvImg, temp, cv::Size(200, 150));
	//cv::imshow("采样结果",temp);

	cvWaitKey(0);
	unsigned int m_buffer[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
	BITMAPINFO* m_bmi = (BITMAPINFO*)m_buffer;
	BITMAPINFOHEADER* m_bmih = &(m_bmi->bmiHeader);
	memset(m_bmih, 0, sizeof(*m_bmih));
	m_bmih->biSize = sizeof(BITMAPINFOHEADER);
	m_bmih->biWidth = img.cols;
	m_bmih->biHeight = -img.rows;           // 在自下而上的位图中 高度为负
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


//线程
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
		MessageBox(NULL, TEXT("请输入学号！"), TEXT("WARING!"), MB_OK);
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


// CFaceRDlg 对话框
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


// CFaceRDlg 消息处理程序

BOOL CFaceRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	reg.set_number(5);
	MessageBoxW(TEXT("接下来会有5次拍照取样！"), TEXT("WARING!"), MB_OK);
	reg.DoModal();

	/*
	CString cstr;
	GetDlgItem(IDC_IDEDIT)->GetWindowText(cstr);
	if (cstr.IsEmpty())
	{
		MessageBoxW(TEXT("请输入学号！"), TEXT("WARNING!"));
		return;
	}
	if (!(frame.data)) {
		MessageBoxW(TEXT("请拍摄照片！"), TEXT("WARNING!"));
		return;
	}
	m_bRun = FALSE;
	//保存图片
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
	MessageBoxW(TEXT("存储成功！"), TEXT("INFORMATION"));
	*/

}




void CFaceRDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	login.set_Login_status(false);
	//5次采样登录
	login.set_TryNum(5);
	login.DoModal();
}
