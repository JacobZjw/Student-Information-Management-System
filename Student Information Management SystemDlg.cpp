
// Student Information Management SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Student Information Management System.h"
#include "Student Information Management SystemDlg.h"
#include "afxdialogex.h"
#include "CAddStudentDlg.h"
#include "Student.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInformationManagementSystemDlg 对话框



CStudentInformationManagementSystemDlg::CStudentInformationManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTINFORMATIONMANAGEMENTSYSTEM_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);//设置图标

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
	CString str = "学生信息管理系统";    
	SetWindowText(str);

	//设置数据显示区
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//整行选择、网格线
	m_List.InsertColumn(0, "姓名", LVCFMT_CENTER, 100);
	m_List.InsertColumn(1, "性别", LVCFMT_CENTER, 100);
	m_List.InsertColumn(2, "学号", LVCFMT_CENTER, 100);
	m_List.InsertColumn(3, "高等数学", LVCFMT_CENTER, 100);
	m_List.InsertColumn(4, "课程设计", LVCFMT_CENTER, 100);
	m_List.InsertColumn(5, "总分", LVCFMT_CENTER, 100);
	//排序函数

	//读取文件函数
	theApp.m_Management.LoadFile(&m_List);

	//设置排序选择按钮
	m_Combo.AddString(_T("总分"));
	m_Combo.AddString(_T("课设"));
	m_Combo.AddString(_T("高数"));
	m_Combo.AddString(_T("学号"));
	m_Combo.SetCurSel(2);
	

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
	theApp.m_Management.AddStudent(&m_List);
}


//删除成员按钮
void CStudentInformationManagementSystemDlg::OnBnClickedDeleteButton()
{
	theApp.m_Management.DeleteStudent(&m_List);
}

//修改数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedChangeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_List.GetFirstSelectedItemPosition();//找到当前选中行
	if (pos == NULL)
	{
		MessageBox(_T("请选择要修改的成员！"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		//将当前选中行数据写入临时变量
		Student temp;
		int nItem = m_List.GetNextSelectedItem(pos);
		char tempgender[20];
		m_List.GetItemText(nItem, 0, temp.name, sizeof(temp.name));
		m_List.GetItemText(nItem, 1, tempgender, sizeof(tempgender));
		m_List.GetItemText(nItem, 2, temp.ID, sizeof(temp.ID));
		m_List.GetItemText(nItem, 3, temp.math, sizeof(temp.math));
		m_List.GetItemText(nItem, 4, temp.program, sizeof(temp.program));
		if (strcmp(tempgender,"女"))
		{
			temp.gender = true;
		}
		else
		{
			temp.gender = false;
		}

		//将临时变量写入全局变量m_student方便CAddStudentDlg调用
		theApp.m_student=temp;
		theApp.Tell = true;//CAddStudentDlg区分添加信息还是修改信息的关键
		theApp.m_Management.ChangeStudent(&m_List);//
		theApp.Tell = false;//还原默认值（默认为添加数据）
	}

}

//数据分析按钮
void CStudentInformationManagementSystemDlg::OnBnClickedDataButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, "open", "C:\\Users\\17810\\source\\repos\\课程设计—学生信息管理系统\\DrawData\\Debug\\DrawData.exe", NULL, NULL, SW_SHOWNORMAL);

}

//导出数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedFileSaveButton()
{
	theApp.m_Management.SaveToFile(&m_List);
}

//导入数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedFileLoadButton()
{
    theApp.m_Management.GetFromFile(&m_List);
}

//查找按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSearchButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//将编辑框内容写入临时变量str
	char str[20];
	GetDlgItemText(IDC_SEARCH_EDIT, str, sizeof(str));  //获取编辑框的信息
	if ((CString)str == "")
	{
		MessageBox(_T("请输入姓名或学号"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	//查找函数
	int nCount = m_List.GetItemCount();//listCtrl中的总行数
	int i = 0, j = -1; // j是返回值，返回查找到的数据的行号

	if (IDC_ID_RADIO== GetCheckedRadioButton(IDC_ID_RADIO, IDC_NAME_RADIO))//如果输入的是学号
	{

		while (i < nCount)
		{
			if (m_List.GetItemText(i, 2) == (CString)str)
			{
				j = i;
				break;
			}
			i++;
		}

	}
	else
	{

		while (i < nCount)
		{
			if (m_List.GetItemText(i, 0) == (CString)str)
			{
				j = i;
				break;
			}
			i++;
		}

	}

	if (j!=-1)
	{
		//高亮显示选中行
		m_List.SetFocus();
		m_List.SetItemState(j, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_List.EnsureVisible(j, FALSE);
	}
	else
	{
		MessageBox(_T("没有找到该学生，请检查输入！"), _T("警告"), MB_OK | MB_ICONWARNING);
	}
}

//排序按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSortButton()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = m_Combo.GetCurSel();//取得当前选中项
	theApp.m_Management.SortStudents(&m_List,nSel);//排序函数
}