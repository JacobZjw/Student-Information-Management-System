#include "pch.h"
#include "Management.h"

bool sort_id(Student a, Student b)  //学号大小比较函数
{
	return _ttoi((CString)a.ID) < _ttoi((CString)b.ID);  //将char转换成CString,在转化成int
}
bool sort_math(Student a, Student b)
{
	return _ttoi((CString)a.math) > _ttoi((CString)b.math);  //高数比较成绩函数
}
bool sort_sum(Student a, Student b)
{
	return (_ttoi((CString)a.program) + _ttoi((CString)a.math)) > (_ttoi((CString)b.program) + _ttoi((CString)b.math));  //总成绩比较函数
}
bool sort_program(Student a, Student b)
{
	return _ttoi((CString)a.program) > _ttoi((CString)b.program);   //大小比较函数
}

//添加成员
void Management::AddStudent(CListCtrl* pList)
{
	CAddStudentDlg temp;
	temp.DoModal();
	LoadFile(pList);
}
//删除成员
void Management::DeleteStudent(CListCtrl* pList)
{
	POSITION pos = pList->GetFirstSelectedItemPosition();//没有删除文件
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
			int nItem = pList->GetNextSelectedItem(pos);
			pList->GetItemText(nItem, 2, temp.ID, sizeof(temp.ID));
			pList->DeleteItem(nItem);

			CFile file;
			if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				//AfxMessageBox("文件无法打开！");
				MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);

				return;
			}
			CFile temporaryfile;
			if (!temporaryfile.Open("./tempfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				//AfxMessageBox("文件无法打开！");
				MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
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
			if (!file.Open("./studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
				return;
			}
			if (!temporaryfile.Open("./tempfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
				return;
			}
			while (temporaryfile.Read(&u, sizeof(u)) == sizeof(u))  //读取学生成绩储存文件，将临时文件temporarystudentfile.dat中学生信息写入真正存储学生信息的studentfile.dat中
				file.Write(&u, sizeof(u));
			LoadFile(pList);  //更新学生成绩管理系统界面的信息
			//OnBnClickedSortButton();
			return;

		}

	}

}
//修改成员
void Management::ChangeStudent(CListCtrl* pList)
{
	CAddStudentDlg tempdlg;
	tempdlg.DoModal();
	LoadFile(pList);
}
//排序
void Management::SortStudents(CListCtrl* pList,int nSel)
{
	Student SomeStudent[100];
	CFile file;
	if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::shareDenyNone))//C:\\Users\\17810\\Desktop\\studentfile.dat
	{
		MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
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

	if (!file.Open("./studentfile.dat",  CFile::modeWrite | CFile::shareDenyNone))
	{
		MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	int t = 0;
	while (t < i)  //将排好序的信息写入学生成绩存储文件
	{
		file.Write(&SomeStudent[t], sizeof(SomeStudent[t]));
		t++;
	}
	file.Close();
	LoadFile(pList); //将排好序的学生信息更新到学生成绩管理系统的CListCtrl中
}
//加载文件，数据存储在此文件
void Management::LoadFile(CListCtrl* pList)
{
	CFile file;
	if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		//AfxMessageBox("添加失败，文件打不开！");
		MessageBox(_T("无法打开文件"), _T("错误"), MB_OK | MB_ICONERROR);
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
//导出数据
void Management::SaveToFile(CListCtrl* pList)
{
	if (pList->GetItemCount() <= 0)
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
	if (dwre != (DWORD)-1)
	{
		DeleteFile(strFilePath);
	}

	//保存文件数据

	FILE* fp;
	fopen_s(&fp, strFilePath, "w");
	char str[1024];
	if (fp == NULL)
	{
		printf("Save file ERROR\n");
		return;
	}

	int nHeadNum = pList->GetHeaderCtrl()->GetItemCount();
	LVCOLUMN lvcol;
	char str_out[256];
	int nColNum;
	nColNum = 0;
	lvcol.mask = LVCF_TEXT;
	lvcol.pszText = str_out;
	lvcol.cchTextMax = 256;
	while (pList->GetColumn(nColNum, &lvcol))
	{
		nColNum++;
		fprintf_s(fp, "%-30s", lvcol.pszText);
	}
	fprintf_s(fp, "\n", lvcol.pszText);

	//读取数据
	int nRow = pList->GetItemCount();
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nColNum; j++)
		{
			CString str_data = pList->GetItemText(i, j);
			fprintf_s(fp, "%-30s", str_data);
		}
		fprintf_s(fp, "\n");
	}
	fclose(fp);
	MessageBox(_T("数据保存成功"), _T("成功"), MB_OK | MB_ICONASTERISK);

}
//导入数据
void Management::GetFromFile(CListCtrl* pList)
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
		pList->DeleteAllItems();
		int nColumnCount = pList->GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			pList->DeleteColumn(0);
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
	if (fp == NULL)
	{
		printf("Open file ERROR\n");
		return;
	}
	int iRow = 0;

	//m_List.InsertColumn(0, "姓名", LVCFMT_CENTER, 80);
	CFile file;
	if (!file.Open("./studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
	{
		MessageBox(_T("无法打开文件！"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	Student u;
	///////////////////////////////////////
	int nLength = 0;
	while (fgets(str, sizeof(str), fp))
	{
		char _index[256] = "temp";
		sprintf_s(_index, "%d", iRow);
		pList->InsertItem(iRow, _index);

		std::string s = str;
		std::string buf;
		std::stringstream ss(s);

		std::vector<std::string> tokens;
		int i = 0;
		int j = 0;
		while (ss >> buf)
		{
			if (buf.size() > 0)
			{
				tokens.push_back(buf);
				if (iRow == 0)
				{

					pList->InsertColumn(++j, _T(tokens.at(i).c_str()), LVCFMT_CENTER, 100);

				}
				else
				{
					pList->SetItemText(iRow, i, tokens.at(i).c_str());
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
		if (iRow > 1)
			file.Write(&u, sizeof(u));
	}
	fclose(fp);
	pList->DeleteItem(0);
	file.Close();
	LoadFile(pList);

}