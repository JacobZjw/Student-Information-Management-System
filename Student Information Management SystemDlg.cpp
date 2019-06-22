
// Student Information Management SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Student Information Management System.h"
#include "Student Information Management SystemDlg.h"
#include "afxdialogex.h"
#include "CAddStudentDlg.h"
#include "Student.h"

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
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_SORT_COMBO, m_Combo);
}

BEGIN_MESSAGE_MAP(CStudentInformationManagementSystemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_CHANGE_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedChangeButton)
	ON_BN_CLICKED(IDC_DATA_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedDataButton)
	ON_BN_CLICKED(IDC_FILE_SAVE_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedFileSaveButton)
	ON_BN_CLICKED(IDC_FILE_LOAD_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedFileLoadButton)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedSearchButton)
	ON_BN_CLICKED(IDC_SORT_BUTTON, &CStudentInformationManagementSystemDlg::OnBnClickedSortButton)
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
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//整行选择、网格线
	m_List.InsertColumn(1, "姓名", LVCFMT_CENTER, 80);
	m_List.InsertColumn(2, "性别", LVCFMT_CENTER, 50);
	m_List.InsertColumn(3, "学号", LVCFMT_CENTER, 100);
	m_List.InsertColumn(4, "高等数学", LVCFMT_CENTER, 100);
	m_List.InsertColumn(5, "课程设计", LVCFMT_CENTER, 100);
	m_List.InsertColumn(6, "总分", LVCFMT_CENTER, 80);
	//排序函数

	//读取文件函数
	LoadFile(&m_List);

	//设置排序选择按钮
	m_Combo.AddString(_T("总分"));
	m_Combo.AddString(_T("课设"));
	m_Combo.AddString(_T("高数"));
	m_Combo.AddString(_T("学号"));
	int nsel = m_Combo.SetCurSel(2);
	
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


//添加成员按钮
void CStudentInformationManagementSystemDlg::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddStudentDlg temp;
	if (IDCANCEL == temp.DoModal())
	{
		CListCtrl* pList = (CListCtrl*)GetDlgItem(IDD_STUDENTINFORMATIONMANAGEMENTSYSTEM_DIALOG);  //关闭IDD_StudentSpecificAddDlg添加窗口，读取储存学生成绩的文件刷新学生成绩管理系统窗口
		CStudentInformationManagementSystemDlg::LoadFile(pList);
		OnBnClickedSortButton();//排序函数
	}
}


//删除成员按钮
void CStudentInformationManagementSystemDlg::OnBnClickedDeleteButton()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();//没有删除文件
	if (pos == NULL)
	{
		AfxMessageBox(_T("请选择要删除的成员！"));
		return;
	}
	else
	{
		while (pos)
		{
			int nItem = m_List.GetNextSelectedItem(pos);
			m_List.DeleteItem(nItem);
		}
	}
}

//修改数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedChangeButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//数据分析按钮
void CStudentInformationManagementSystemDlg::OnBnClickedDataButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//导出数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedFileSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//导入数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedFileLoadButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//查找按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSearchButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//排序按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSortButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox* pComb = (CComboBox*)GetDlgItem(IDD_STUDENTINFORMATIONMANAGEMENTSYSTEM_DIALOG);
	int nSel = pComb->GetCurSel();
	//SortStudent(nSel);//排序函数还没写

}

void CStudentInformationManagementSystemDlg::LoadFile(CListCtrl* pList)
{
	CFile file;
	if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeRead | CFile::shareDenyNone))
	{
		AfxMessageBox("添加失败，文件打不开！");
		return;
	}
	pList->DeleteAllItems();
	Student u;
	int i = 0;
	while (file.Read(&u, sizeof(u)) == sizeof(u))
	{
		pList->InsertItem(i, u.name);
		if (u.gender)
			pList->SetItemText(i, 1, _T("男"));
		else
			pList->SetItemText(i, 1, _T("女"));
		pList->SetItemText(i, 2, u.ID);
		pList->SetItemText(i, 3, u.math);
		pList->SetItemText(i, 4, u.program);
		pList->SetItemText(i, 5, u.sum);
		i++;
	}
	file.Close();
}
