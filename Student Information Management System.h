
// Student Information Management System.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include "Student.h"
#include "Management.h"

// CStudentInformationManagementSystemApp:
// 有关此类的实现，请参阅 Student Information Management System.cpp
//

class CStudentInformationManagementSystemApp : public CWinApp
{
public:
	CStudentInformationManagementSystemApp();
	Student m_student;//用来实现两个窗口之间的数据传输
	Management m_Management;//用来实现增加、删除等操作
	bool Tell = false;//用来判断调用添加修改窗口时是要添加还是修改数据
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CStudentInformationManagementSystemApp theApp;
