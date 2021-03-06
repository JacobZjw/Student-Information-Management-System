﻿#pragma once


// AddStudent 对话框

class CAddStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddStudentDlg)

public:
	CAddStudentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddStudentDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddStudentSave();
	//afx_msg void OnBnClickedFileSaveButton();
	CString m_Name_Edit;
	CString m_Program_Edit;
	CString m_ID_Edit;
	CString m_Math_Edit;
};
