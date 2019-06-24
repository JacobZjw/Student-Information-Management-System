
// Student Information Management SystemDlg.h: 头文件
//

#pragma once


// CStudentInformationManagementSystemDlg 对话框
class CStudentInformationManagementSystemDlg : public CDialogEx
{
// 构造
public:
	CStudentInformationManagementSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTINFORMATIONMANAGEMENTSYSTEM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedChangeButton();
	afx_msg void OnBnClickedDataButton();
	afx_msg void OnBnClickedFileSaveButton();
	afx_msg void OnBnClickedFileLoadButton();
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedSortButton();
	CListCtrl m_List;
	// 排序选择
	CComboBox m_Combo;
	friend class Management;
};
