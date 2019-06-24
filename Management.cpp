#include "pch.h"
#include "Management.h"

bool sort_id(Student a, Student b)  //ѧ�Ŵ�С�ȽϺ���
{
	return _ttoi((CString)a.ID) < _ttoi((CString)b.ID);  //��charת����CString,��ת����int
}
bool sort_math(Student a, Student b)
{
	return _ttoi((CString)a.math) > _ttoi((CString)b.math);  //�����Ƚϳɼ�����
}
bool sort_sum(Student a, Student b)
{
	return (_ttoi((CString)a.program) + _ttoi((CString)a.math)) > (_ttoi((CString)b.program) + _ttoi((CString)b.math));  //�ܳɼ��ȽϺ���
}
bool sort_program(Student a, Student b)
{
	return _ttoi((CString)a.program) > _ttoi((CString)b.program);   //��С�ȽϺ���
}

//��ӳ�Ա
void Management::AddStudent(CListCtrl* pList)
{
	CAddStudentDlg temp;
	temp.DoModal();//����CAddStudentDlg������Ϣд��ListCtrl
	LoadFile(pList);////����ListCtrl����
}
//ɾ����Ա
void Management::DeleteStudent(CListCtrl* pList)
{
	POSITION pos = pList->GetFirstSelectedItemPosition();//�ҵ���ǰѡ����
	if (pos == NULL)
	{
		MessageBox(_T("��ѡ��Ҫɾ���ĳ�Ա��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (pos)
		{
			Student temp;
			int nItem = pList->GetNextSelectedItem(pos);//��ȡ��ǰѡ���е��к�
			pList->GetItemText(nItem, 2, temp.ID, sizeof(temp.ID));//��ѡ���е�ѧ����Ϣд����ʱ����
			pList->DeleteItem(nItem);//��ListCtrl��ɾ��ѡ����

			CFile file;
			if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
				return;
			}
			CFile temporaryfile;//��ʱ���ݴ洢�ļ�������������򴴽��µ�
			if (!temporaryfile.Open("./tempfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
				return;
			}
			//��ȡѧ���ɼ������ļ�����δɾ����ѧ����Ϣд����ʱ�ļ�temporaryfile��
			Student u;
			while (file.Read(&u, sizeof(u)) == sizeof(u)) 
			{
				if ((CString)u.ID == (CString)temp.ID)//����ѧ���ж��Ƿ��д��
					continue;
				temporaryfile.Write(&u, sizeof(u));
			}
			file.Close();
			temporaryfile.Close();
			//���������ļ��Ƿ���ڶ��������µĿ��ļ�studentfile.dat������Ϊԭ�ļ��������ݣ���Ҫ���
			if (!file.Open("./studentfile.dat", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
			{
				MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
				return;
			}
			if (!temporaryfile.Open("./tempfile.dat", CFile::modeRead | CFile::shareDenyNone))
			{
				MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
				return;
			}
			//��ȡѧ���ɼ������ļ�������ʱ�ļ�tempfile.dat��ѧ����Ϣд�������洢ѧ����Ϣ��studentfile.dat��
			while (temporaryfile.Read(&u, sizeof(u)) == sizeof(u))  
				file.Write(&u, sizeof(u));
			LoadFile(pList);  //����ѧ���ɼ�����ϵͳ�������Ϣ
			return;
		}

	}

}
//�޸ĳ�Ա
void Management::ChangeStudent(CListCtrl* pList)
{
	CAddStudentDlg tempdlg;
	tempdlg.DoModal();
	LoadFile(pList);
}
//����
void Management::SortStudents(CListCtrl* pList, int nSel)
{
	Student SomeStudent[100];
	CFile file;
	if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::shareDenyNone))//C:\\Users\\17810\\Desktop\\studentfile.dat
	{
		MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	int i = 0;
	while (file.Read(&SomeStudent[i], sizeof(SomeStudent[i])) == sizeof(SomeStudent[i]))
	{
		i++;
	}
	file.Close();

	int b = (CString)SomeStudent[0].ID < (CString)SomeStudent[1].ID;
	if (nSel == 0)     //0�Ǹ����ɼ�����
		std::sort(SomeStudent, SomeStudent + i, sort_math);
	if (nSel == 1)     //1�ǿ���ɼ�����
		std::sort(SomeStudent, SomeStudent + i, sort_program);
	if (nSel == 2)     //2��ѧ������
		std::sort(SomeStudent, SomeStudent + i, sort_id);
	if (nSel == 3)     //3���ܳɼ�����
		std::sort(SomeStudent, SomeStudent + i, sort_sum);

	if (!file.Open("./studentfile.dat", CFile::modeWrite | CFile::shareDenyNone))
	{
		MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	int t = 0;
	while (t < i)  //���ź������Ϣд��studentfile.dat
	{
		file.Write(&SomeStudent[t], sizeof(SomeStudent[t]));
		t++;
	}
	file.Close();
	LoadFile(pList); ////����ListCtrl����
}

//����ListCtrl����
void Management::LoadFile(CListCtrl* pList)
{
	CFile file;//�����ݴ洢�ļ�������������򴴽����ļ�
	if (!file.Open("./studentfile.dat", CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		MessageBox(_T("�޷����ļ�"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	pList->DeleteAllItems();//����
	//����д��ListCtrl
	Student u;
	int i = 0;
	while (file.Read(&u, sizeof(u)) == sizeof(u))
	{
		u.Sum();
		pList->InsertItem(i, u.name);
		if (u.gender)
			pList->SetItemText(i, 1, _T("��"));
		else
			pList->SetItemText(i, 1, _T("Ů"));
		pList->SetItemText(i, 2, u.ID);
		pList->SetItemText(i, 3, u.math);
		pList->SetItemText(i, 4, u.program);
		pList->SetItemText(i, 5, u.sum);
		i++;
	}
	file.Close();

}
//��������
void Management::SaveToFile(CListCtrl* pList)
{
	if (pList->GetItemCount() <= 0)
	{
		MessageBox(_T("û����Ҫ���������"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}
	//����ϵͳ���Ϊ����
	char szFilters[] = _T("txt�ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), _T("ѧ����Ϣ"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);
	if (dlg.DoModal() != IDOK)
		return;
	//��ȡ�ļ�·��
	CString strFilePath;
	strFilePath = dlg.GetPathName();
	//�ж��ļ��Ƿ��Ѵ��ڣ�������ɾ���ؽ�
	DWORD dwre = GetFileAttributes(strFilePath);
	if (dwre != (DWORD)-1)
	{
		DeleteFile(strFilePath);
	}

	//�����ļ�����
	FILE* fp;
	fopen_s(&fp, strFilePath, "w");
	//char str[1024];
	if (fp == NULL)
	{
		printf("Save file ERROR\n");
		return;
	}

	//��ȡListCtrl��ÿһ�еĵ�һ�У������ݵ����
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
	fprintf_s(fp, "\n", lvcol.pszText);//д���ļ���

	//��ȡ�е�����
	int nRow = pList->GetItemCount();
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nColNum; j++)
		{
			CString str_data = pList->GetItemText(i, j);//��ȡָ���У���Ϊ�ַ�����ʽ
			fprintf_s(fp, "%-30s", str_data);
		}
		fprintf_s(fp, "\n");
	}
	fclose(fp);
	MessageBox(_T("���ݱ���ɹ�"), _T("�ɹ�"), MB_OK | MB_ICONASTERISK);

}
//��������
void Management::GetFromFile(CListCtrl* pList)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ϵͳ����
	char szFilters[] = _T("txt�ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("txt"), _T("ѧ����Ϣ"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);
	dlg.m_ofn.lpstrTitle = _T("��������");
	if (dlg.DoModal() != IDOK)
		return;
	//��ȡ�ļ�·��
	CString strFilePath;
	strFilePath = dlg.GetPathName();
	//�ж��ļ��Ƿ����
	DWORD dwre = GetFileAttributes(strFilePath);
	if (dwre != (DWORD)-1)//���·����ȷ
	{
		//���֮ǰ��������
		pList->DeleteAllItems();
		int nColumnCount = pList->GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumnCount; i++)
		{
			pList->DeleteColumn(0);
		}
	}
	else
	{
		MessageBox(_T("�ļ������ڣ�"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}
	//��ȡ�ļ��е�����
	FILE* fp;
	fopen_s(&fp, strFilePath, "r");
	char str[1024];
	if (fp == NULL)
	{
		printf("Open file ERROR\n");
		return;
	}
	int iRow = 0;

	CFile file;
	if (!file.Open("./studentfile.dat", /*CFile::modeCreate | */CFile::modeRead|CFile::modeWrite | CFile::shareDenyNone))
	{
		MessageBox(_T("�޷����ļ���"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}

	Student u;
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
						if (strcmp("Ů", temp))
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
	LoadFile(pList);//����ListCtrl����
}