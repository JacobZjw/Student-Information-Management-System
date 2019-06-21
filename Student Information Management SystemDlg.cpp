
// Student Information Management SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Student Information Management System.h"
#include "Student Information Management SystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInformationManagementSystemDlg 对话框



CStudentInformationManagementSystemDlg::CStudentInformationManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTINFORMATIONMANAGEMENTSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentInformationManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStudentInformationManagementSystemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CStudentInformationManagementSystemDlg 消息处理程序

BOOL CStudentInformationManagementSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//在窗口左上角设置自己的姓名和学号（课设要求)
	CString str = "学生成绩管理系统";    
	//str += theApp.m_us.sName;
	SetWindowText(str);

	//设置数据显示区
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->InsertColumn(5, "姓名", LVCFMT_CENTER, 100);
	pList->InsertColumn(1, "学号", LVCFMT_CENTER, 110);
	pList->InsertColumn(2, "高等数学", LVCFMT_CENTER, 100);
	pList->InsertColumn(3, "课程设计", LVCFMT_CENTER, 100);
	pList->InsertColumn(4, "总分", LVCFMT_CENTER, 100);

	//设置排序选择按钮
	CComboBox* pComb = (CComboBox*)GetDlgItem(IDC_SORTCOMBO);   //设置（IDC_SORTCOMBO）CComboBox控件
	pComb->AddString("学号");
	pComb->AddString("高数");
	pComb->AddString("课设");
	pComb->AddString("总分");

	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentInformationManagementSystemDlg::OnPaint()
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
HCURSOR CStudentInformationManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

