#pragma once


// AddStudent 对话框

class AddStudent : public CDialogEx
{
	DECLARE_DYNAMIC(AddStudent)

public:
	AddStudent(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddStudent();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddStudentSave();
};
