#pragma once
#include <afxdialogex.h>
#include <afxdialogex.h>

#include "Student Information Management SystemDlg.h"
#include <iostream>
#include "CAddStudentDlg.h"
#include "Student.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


class Management :
	public CDialogEx
{
public:
	Management() {};
	~Management() {};
	void AddStudent(CListCtrl* pList);
	void DeleteStudent(CListCtrl* pList);
	void ChangeStudent(CListCtrl* pList);
	void SortStudents(CListCtrl* pList,int nSel);
	void LoadFile(CListCtrl* pList);//º”‘ÿ ˝æ›
	void SaveToFile(CListCtrl* pList);
	void GetFromFile(CListCtrl* pList);
};


