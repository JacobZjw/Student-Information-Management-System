
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
	CString str = "学生信息管理系统";    
	//str += theApp.Student.name;
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
	LoadFile(&m_List);

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
	CAddStudentDlg temp;
	temp.DoModal();
	LoadFile(&m_List);
}


//删除成员按钮
void CStudentInformationManagementSystemDlg::OnBnClickedDeleteButton()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();//没有删除文件
	if (pos == NULL)
	{
		MessageBox(_T("请选择要删除的成员！"), _T("警告"), MB_OK | MB_ICONWARNING);
		//AfxMessageBox(_T("请选择要删除的成员！"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (pos)
		{
			Student temp;
			int nItem = m_List.GetNextSelectedItem(pos);
			m_List.GetItemText(nItem, 2, temp.ID, sizeof(temp.ID));
			m_List.DeleteItem(nItem);

			CFile file;
			if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				//AfxMessageBox("文件无法打开！");
				MessageBox(_T("添加失败,无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);

				return;
			}
			CFile temporaryfile;
			if (!temporaryfile.Open("C:\\Users\\17810\\Desktop\\tempfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				//AfxMessageBox("文件无法打开！");
				MessageBox(_T("添加失败,无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);

				return;
			}
			Student u;
			while (file.Read(&u, sizeof(u)) == sizeof(u)) //读取学生成绩储存文件，将未删除的学生信息写入临时文件temporaryfile中
			{
				if ((CString)u.ID == (CString)temp.ID)
					continue;
				temporaryfile.Write(&u, sizeof(u));
			}
			file.Close();
			temporaryfile.Close();
			if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				AfxMessageBox("文件无法打开！");
				return;
			}
			if (!temporaryfile.Open("C:\\Users\\17810\\Desktop\\tempfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				AfxMessageBox("文件无法打开！");
				return;
			}
			while (temporaryfile.Read(&u, sizeof(u)) == sizeof(u))  //读取学生成绩储存文件，将临时文件temporarystudentfile.dat中学生信息写入真正存储学生信息的studentfile.dat中
				file.Write(&u, sizeof(u));
			LoadFile(&m_List);  //更新学生成绩管理系统界面的信息
			//OnBnClickedSortButton();
			return;

		}

	}
}

//修改数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedChangeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_List.GetFirstSelectedItemPosition();//没有删除文件
	if (pos == NULL)
	{
		MessageBox(_T("请选择要修改的成员！"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
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

		theApp.m_student=temp;
		theApp.Tell = true;
		theApp.nCOUNT = nItem;

		CAddStudentDlg tempdlg;
		tempdlg.DoModal();
		theApp.Tell = false;
		LoadFile(&m_List);
	}

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
	if (m_List.GetItemCount()<=0)
	{
		MessageBox(_T("没有需要保存的数据"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	char szFilters[] = _T("txt文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), _T("学生信息"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);
	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	strFilePath = dlg.GetPathName();
	
	DWORD dwre = GetFileAttributes(strFilePath);
	if (dwre!=(DWORD)-1)
	{
		DeleteFile(strFilePath);
	}

	//保存文件数据

	FILE* fp;
	fopen_s(&fp, strFilePath, "w");
	char str[1024];
	if (fp==NULL)
	{
		printf("Save file ERROR\n");
		return;
	}

	int nHeadNum = m_List.GetHeaderCtrl()->GetItemCount();
	LVCOLUMN lvcol;
	char str_out[256];
	int nColNum;
	nColNum = 0;
	lvcol.mask = LVCF_TEXT;
	lvcol.pszText = str_out;
	lvcol.cchTextMax = 256;
	while (m_List.GetColumn(nColNum,&lvcol))
	{
		nColNum++;
		fprintf_s(fp, "%-30s", lvcol.pszText);
	}
	fprintf_s(fp, "\n", lvcol.pszText);

	//读取数据
	int nRow = m_List.GetItemCount();
	for (int i=0;i<nRow;i++)
	{
		for (int j=0;j<nColNum;j++)
		{
			CString str_data = m_List.GetItemText(i, j);
			fprintf_s(fp, "%-30s", str_data);
		}
		fprintf_s(fp, "\n");
	}
	fclose(fp);
	MessageBox(_T("数据保存成功"), _T("成功"), MB_OK | MB_ICONASTERISK);

}

//导入数据按钮
void CStudentInformationManagementSystemDlg::OnBnClickedFileLoadButton()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[] = _T("txt文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("txt"), _T("学生信息"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);
	dlg.m_ofn.lpstrTitle = _T("导入数据");

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	strFilePath = dlg.GetPathName();

	DWORD dwre = GetFileAttributes(strFilePath);
	if (dwre != (DWORD)-1)
	{
		m_List.DeleteAllItems();
		int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			m_List.DeleteColumn(0);
		}
	}
	else
	{
		MessageBox(_T("文件不存在！"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	FILE* fp;
	fopen_s(&fp, strFilePath, "r");
	char str[1024];
	if (fp==NULL)
	{
		printf("Open file ERROR\n");
		return;
	}
	int iRow = 0;

	//m_List.InsertColumn(0, "姓名", LVCFMT_CENTER, 80);
	CFile file;
	if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
	{
		AfxMessageBox("文件无法打开！");
		return;
	}
	Student u;
	///////////////////////////////////////
	int nLength = 0;
	while (fgets(str,sizeof(str),fp))
	{
		char _index[256] = "temp";
		sprintf_s(_index, "%d", iRow);
		m_List.InsertItem(iRow, _index);

		std::string s = str;
		std::string buf;
		std::stringstream ss(s);

		std::vector<std::string> tokens;
		int i = 0;
		int j = 0;
		while (ss >> buf)
		{
			if (buf.size()>0)
			{
				tokens.push_back(buf);
				if (iRow==0)
				{
					
						m_List.InsertColumn(++j, _T(tokens.at(i).c_str()), LVCFMT_CENTER, 100);

				}
				else
				{
					m_List.SetItemText(iRow,i, tokens.at(i).c_str());
					char temp[20];
					strcpy_s(temp, tokens.at(i).c_str());
					switch (i)
					{
					case 0:
						strcpy_s(u.name, tokens.at(i).c_str());
						break;
					case 1:
						if (strcmp("女", temp))
						{
							u.gender = true;
							break;
						}
						else
						{
							u.gender = false;
							break;
						}
					case 2:
						strcpy_s(u.ID, tokens.at(i).c_str());
						break;
					case 3:
						strcpy_s(u.math, tokens.at(i).c_str());
						break;
					case 4:
						strcpy_s(u.program, tokens.at(i).c_str());
						break;
					case 5:
						strcpy_s(u.sum, tokens.at(i).c_str());
						break;
					default:
						break;
					}
				}

				i++;
			}
		}
		iRow++;
		if (iRow>1)
			file.Write(&u, sizeof(u));
	}
	fclose(fp);
	m_List.DeleteItem(0);
	file.Close();
	LoadFile(&m_List);
}

//查找按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSearchButton()
{
	// TODO: 在此添加控件通知处理程序代码
	char str[20];
	GetDlgItemText(IDC_SEARCH_EDIT, str, sizeof(str));  //获取编辑框的信息
	if ((CString)str == "")
	{
		//AfxMessageBox("请输入姓名或学号");
		MessageBox(_T("请输入姓名或学号"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	//查找函数
	int nCount = m_List.GetItemCount();
	int i = 0, j = -1;
	//////
	
	if (IDC_ID_RADIO== GetCheckedRadioButton(IDC_ID_RADIO, IDC_NAME_RADIO))
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
		AfxMessageBox(_T("没有找到该学生，请检查您的输入！"));
	}
}

//排序按钮
void CStudentInformationManagementSystemDlg::OnBnClickedSortButton()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = m_Combo.GetCurSel();//取得当前选中项
	SortStudent(nSel);//排序函数还没写
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
		//int math= atoi(u.math);//类型转换
		//int program = atoi(u.program);
		//int sum = math + program;
		//_itoa_s(sum, u.sum, 10);//写入类中

		u.Sum();
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

bool sort_id(Student a, Student b)  //学号（ID）大小比较函数
{
	return _ttoi((CString)a.ID) < _ttoi((CString)b.ID);  //将char转换成CString,在转化成int
}
bool sort_math(Student a, Student b)
{
	return _ttoi((CString)a.math) > _ttoi((CString)b.math);  //高数（Higher_math）大小比较函数
}
bool sort_sum(Student a, Student b)
{
	return (_ttoi((CString)a.program) + _ttoi((CString)a.math)) > (_ttoi((CString)b.program) + _ttoi((CString)b.math));  //总分大小比较函数
}
bool sort_program(Student a, Student b)
{
	return _ttoi((CString)a.program) > _ttoi((CString)b.program);   //c++（C_program）大小比较函数
}

void CStudentInformationManagementSystemDlg::SortStudent(int nSel)
{
	Student SomeStudent[100];
	CFile file;
	if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeRead | CFile::shareDenyNone))
	{
		AfxMessageBox("文件无法打开,无法排序！");
		return;
	}
	int i = 0;
	while (file.Read(&SomeStudent[i], sizeof(SomeStudent[i])) == sizeof(SomeStudent[i]))
	{
		i++;
	}
	file.Close();

	int b = (CString)SomeStudent[0].ID < (CString)SomeStudent[1].ID;
	if (nSel == 0)    //0是高数成绩排序
		std::sort(SomeStudent, SomeStudent + i, sort_math);  //排序是直接调用STL中的快排
	if (nSel == 1)     //1是课设成绩排序
		std::sort(SomeStudent, SomeStudent + i, sort_program);
	if (nSel == 2)    //2是学号排序
		std::sort(SomeStudent, SomeStudent + i, sort_id);
	if (nSel == 3)    //3是总成绩排序
		std::sort(SomeStudent, SomeStudent + i, sort_sum);

	if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
	{
		AfxMessageBox("文件无法打开,无法排序！");
		return;
	}
	int t = 0;
	while (t < i)  //将排好序的信息写入学生成绩存储文件
	{
		file.Write(&SomeStudent[t], sizeof(SomeStudent[t]));
		t++;
	}
	file.Close();
	CStudentInformationManagementSystemDlg::LoadFile(&m_List); //将排好序的学生信息更新到学生成绩管理系统的CListCtrl中
}