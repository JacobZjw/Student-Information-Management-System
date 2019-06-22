// AddStudent.cpp: 实现文件
//

#include "pch.h"
#include "Student Information Management System.h"
#include "CAddStudentDlg.h"
#include "afxdialogex.h"
#include "Student.h"
#include "Management.h"


// AddStudent 对话框

IMPLEMENT_DYNAMIC(CAddStudentDlg, CDialogEx)

CAddStudentDlg::CAddStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DIALOG, pParent)
	, m_Name_Edit(_T(""))
	, m_ID_Edit(_T(""))
	, m_Program_Edit(_T(""))
	, m_Math_Edit(_T(""))
{

}

CAddStudentDlg::~CAddStudentDlg()
{
}

void CAddStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_Name_Edit);
	DDX_Text(pDX, IDC_PROGRAM_EDIT, m_Program_Edit);
	DDX_Text(pDX, IDC_ID_EDIT, m_ID_Edit);
	DDX_Text(pDX, IDC_MATH_EDIT, m_Math_Edit);
}


BEGIN_MESSAGE_MAP(CAddStudentDlg, CDialogEx)
	ON_BN_CLICKED(ID_ADD_STUDENT_SAVE, &CAddStudentDlg::OnBnClickedAddStudentSave)
END_MESSAGE_MAP()


// AddStudent 消息处理程序


void CAddStudentDlg::OnBnClickedAddStudentSave()
{
	
	
	 //TODO: 在此添加控件通知处理程序代码

	Student temp;
	GetDlgItemText(IDC_ID_EDIT, temp.ID, sizeof(temp.ID));  //将学号编辑框的内容写入u.sId
	GetDlgItemText(IDC_NAME_EDIT, temp.name, sizeof(temp.name));  //将姓名编辑框的内容写入u.sName
	if (IDC_MAN == GetCheckedRadioButton(IDC_MAN, IDC_WOMEN))
		temp.gender=true;
	else
		temp.gender=false;
	GetDlgItemText(IDC_MATH_EDIT, temp.math, sizeof(temp.math));  //将高数编辑框的内容写入u.sHigher_math
	GetDlgItemText(IDC_PROGRAM_EDIT, temp.program, sizeof(temp.program));  //将C++课设编辑框的内容写入u.sC_program

	CFile file;
	if (!file.Open("C:\\Users\\17810\\Desktop\\studentfile.dat", CFile::modeReadWrite | CFile::shareDenyNone))//文件无法打开，想办法创建新的文件类型
	{
		AfxMessageBox("添加失败,无法打开文件！");
		return;
	}

	Student temp2;
	while (file.Read(&temp2, sizeof(temp2)))   //读取学生文件信息，看学号是否重复
	{
		if ((CString)temp2.ID == (CString)temp.ID)
		{
			AfxMessageBox("该学生已存在！");
			return;
		}
	}
	file.SeekToEnd();   //将指针移到文件末尾
	file.Write(&temp, sizeof(temp));  //在文件末尾写入新的学生信息
	AfxMessageBox("保存成功！"); //提示保存成功
	OnOK();
}
