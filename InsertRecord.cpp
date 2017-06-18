// InsertRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "InsertRecord.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "log.h"


// CInsertRecord �Ի���

IMPLEMENT_DYNAMIC(CInsertRecord, CDialogEx)

CInsertRecord::CInsertRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertRecord::IDD, pParent)
{
	ifUpdate=-1;  //�Ƿ��Ǹ��²��������µ�����һ������
	recordNum=0;  //��¼��Ŀ

	if (myGlobal.ifUpdate != -1) ifUpdate = myGlobal.ifUpdate;
	num = 0;
	recordRow = new CString[24];
	recordColumn = new CString[24];
	recordDataType = new CString[24];
    //��ȡ�ļ��е�column��Ŀ��ʼ����recordRow��
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".trd");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//���ұ�ɾ����¼
	//��db�ļ��������
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//�����������
	//CString szA[24];//��ű���
	//CString field[24];//����ֶ���Ϣ
	BOOLEAN ifFind = 0;//����Ƿ��ҵ���Ӧ�����
	CString toE("#");               //�Կո�ָ�
	file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
	int i = 0;                             //��ʼ���������־
	file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
	CString strGap = _T(" ");//��ʼ���ָ���*/

	/*��ʼ���г��ַ����ָ��Լ�����*/

	int nPos = szTemp.Find(strGap);
	int nn = 0;
	CString strLeft = _T("");
	CString str = _T("");
	while (0 <= nPos){
		strLeft = szTemp.Left(nPos);
		if (!strLeft.IsEmpty())
			recordRow[i] = strLeft;

		int j = 0;
		nn = recordRow[i].Find(toE);
		while (0<nn){
			str = recordRow[i].Left(nn);
			if (!str.IsEmpty())
				
			if (j == 0)
			{
				recordColumn[i] = str;
                //m_tableList.InsertItem(i, field[j]);
			}
				

			if (j == 1)
			{
				recordDataType[i] = str;
				//m_tableList.SetItemText(i, j, field[j]);
			}
				
			recordRow[i] = recordRow[i].Right(recordRow[i].GetLength() - nn - 1);
			nn = recordRow[i].Find(toE);
			/*
			if (!recordRow[i].IsEmpty()) {
				field[j + 1] = recordRow[i];
			}
			*/
			j++;
		}

		szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
		nPos = szTemp.Find(strGap);
		if (!szTemp.IsEmpty()) {
			recordRow[i + 1] = szTemp;
		}

		i++;
		//recordRow[i] = recordRow[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
	}
	file.Close();
	num = i;
	i = 0;
}

CInsertRecord::~CInsertRecord()
{
	delete []recordRow;
	delete[]recordColumn;
	delete[]recordDataType;
}

void CInsertRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, recordList);
	DDX_Control(pDX, IDC_EDIT1, m_editValue);
}


BOOL CInsertRecord::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the style of report
	DWORD dwStyle = ::GetWindowLong(recordList.m_hWnd, GWL_STYLE);
	dwStyle |= LVS_REPORT;// Set style
	::SetWindowLong(recordList.m_hWnd, GWL_STYLE, dwStyle);
	//recordList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	recordList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	recordList.SetExtendedStyle(recordList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// List header
	recordList.InsertColumn(0, _T("Field Name"), LVCFMT_LEFT, 100);
	recordList.InsertColumn(1, _T("Field Type"), LVCFMT_LEFT, 100);
	recordList.InsertColumn(3, _T("Value"), LVCFMT_LEFT, 150);
	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);

	//��recordRow�е����ݶν��н�������д�뵽�б���д���

	for (int i = 0; i < num; i++)
	{
		recordList.InsertItem(i, recordColumn[i]);
		recordList.SetItemText(i, 1, recordDataType[i]);
	}

	//recordList.InsertItem(0, _T("name"));
	//recordList.SetItemText(0, 1,_T("varchar"));
	//recordList.InsertItem(1, _T("name"));
	//recordList.SetItemText(1, 1, _T("varchar"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CInsertRecord, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CInsertRecord::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CInsertRecord::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDOK, &CInsertRecord::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsertRecord ��Ϣ�������


void CInsertRecord::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_dwItem = pNMListView->iItem;  // The selected row
	m_nSubItem = pNMListView->iSubItem;  // The selected column
	DWORD dwCount = recordList.GetItemCount();  // The number of the data item in the list

	// If the selected line number greater than 0, the column number greater than 1,
	// and no more than the number of data items in the list, respond to the events
	if (m_dwItem >= 0 && m_nSubItem == 2 && m_dwItem <= dwCount)
	{
		//CFieldEntity* pField = m_pTableEntity->GetFieldAt(m_dwItem);

		// Get the size of the selected cell
		CRect rtEdit, rtClient;
		recordList.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		recordList.GetSubItemRect(m_dwItem, m_nSubItem, LVIR_LABEL, rtEdit);
		rtEdit.MoveToX(rtEdit.left + rtClient.left + 2);
		rtEdit.MoveToY(rtEdit.top + rtClient.top);
		rtEdit.bottom += 4;

		// Get the content of the selected cells
		CString strItemText = recordList.GetItemText(m_dwItem, m_nSubItem);
		int nLength = strItemText.GetLength();
		// Set the content of the edit control
		m_editValue.SetWindowText(strItemText);
		m_editValue.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, rtEdit.Width(), rtEdit.Height(), SWP_SHOWWINDOW);
		m_editValue.SetSel(nLength, nLength);
		m_editValue.SetFocus();
		/**
		m_editValue.SetWindowText(recordList.GetItemText(info.iItem, info.iSubItem));
		m_editValue.MoveWindow(&rect, TRUE);
		m_editValue.ShowWindow(1);
		m_editValue.SetFocus();
		**/
	}
}


void CInsertRecord::OnEnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// Get the value of the edit control
	CString strValue;
	m_editValue.GetWindowText(strValue);

	// Assign the value of the edit control to list item
	recordList.SetItemText(m_dwItem, m_nSubItem, strValue);

	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);
}

/*�ڵ��ȷ��ʱ�Կɱ༭���ֵ����ݽ��ж�ȡ����ȡ�󽫼�¼׷�����б���ļ����*/
void CInsertRecord::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	newRecord;
	CString split("#");
	CString split2(" ");
	for (int i = 0; i < num;i++)
	{
		recordRow[i]=recordList.GetItemText(i,2);
		if (recordRow[i] != "") newRecord = newRecord + recordRow[i] + split;
		else newRecord = newRecord + "null" + split;
	}

	//����ȡ��ֵд���ļ���Ӧλ��
	newRecord = newRecord + split2;

	if (ifUpdate == -1)
	{
		OnInsert();
	}else 
	{
		OnUpdate();
	}

	CDialogEx::OnOK();
}

void CInsertRecord::OnUpdate()
{
	//����Ӧ�ļ��еļ�¼���뵽����
	readRecord();

	//����Ӧ�ı�λ�õ������û�
	record[ifUpdate] = newRecord;

	//���ı�����������д���ļ�
	writeToFile();
}

void CInsertRecord::OnInsert()
{
	CFile file;
	//char ss[20]="data.txt";
	CString dbName = myGlobal.db_name;          //��ȡѡ�е����ݿ���
	CString tbName = myGlobal.tableName;          //��ȡѡ�е����ݿ���
	CString end(".tid");          //���Ϻ�׺
	tbName = myGlobal.tableName;
	CString forder("Output\\data\\");
	CString FileName = forder + dbName + "\\" + tbName + end; //���ϳ�Ϊ�������ļ���
	//������򿪱������ļ�׷�����±������
	try
	{
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		//���±����д�� ע��*sizeof(TCHAR)����д�벻����
		file.Write((unsigned char *)(newRecord.GetBuffer(0)), newRecord.GetLength()*sizeof(TCHAR));
		file.Flush();
		file.Close();
		//MessageBox(_T("д��ɹ���"));
		myGlobal.state="�����ɹ���";
	    myGlobal.if_reflesh=1;
	}
	catch (CFileException *e)
	{
		CString str;
		str.Format(_T("д��ʧ�ܵ�ԭ����:%d"), e->m_cause);
		//MessageBox(str);
		myGlobal.state=str;
	    myGlobal.if_reflesh=1;
		file.Abort();
		e->Delete();
	}

}

void CInsertRecord::readRecord()
{
	record = new CString[24];
	//CString* recordData = new CString[24];
	//��ȡ�ļ��е�column��Ŀ��ʼ����recordRow��
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".tid");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//���ұ�ɾ����¼
	//��db�ļ��������
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//�����������
	BOOLEAN ifFind = 0;//����Ƿ��ҵ���Ӧ�����
	//CString toE("#");               //�Կո�ָ�
	file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
	recordNum = 0;                             //��ʼ���������־
	file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
	CString strGap = _T(" ");//��ʼ���ָ���*/

	/*��ʼ���г��ַ����ָ��Լ�����*/

	int nPos = szTemp.Find(strGap);
	int nn = 0;
	CString strLeft = _T("");
	CString str = _T("");
	while (0 <= nPos){
		strLeft = szTemp.Left(nPos);
		if (!strLeft.IsEmpty())
			record[recordNum] = strLeft;

		szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
		nPos = szTemp.Find(strGap);
		if (!szTemp.IsEmpty()) {
			recordRow[recordNum + 1] = szTemp;
		}

        record[recordNum] = record[recordNum] + strGap;    //���ϻ��з�����������ٴδ���db�ļ�
		recordNum++;
	}
	file.Close();
	myGlobal.state="��ȡ���ݳɹ���";
	myGlobal.if_reflesh=1;
}

void CInsertRecord::writeToFile()
{
	//����ȡ��ֵ����д���ļ�
	CFile file;
	//char ss[20]="data.txt";
	CString message;
	message="";
	CString dbName = myGlobal.db_name;          //��ȡѡ�е����ݿ���
	CString tbName = myGlobal.tableName;          //��ȡѡ�е����ݿ���
	CString end(".tid");          //���Ϻ�׺
	tbName = myGlobal.tableName;
	CString forder("Output\\data\\");
	CString FileName = forder + dbName + "\\" + tbName + end; //���ϳ�Ϊ�������ļ���
	//������򿪱������ļ�׷�����±������
	try
	{
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite);
		//���±����д�� ע��*sizeof(TCHAR)����д�벻����
		for (int i = 0; i < recordNum; i++){
			message+=record[i]+" ";
			file.SeekToEnd();
			file.Write((unsigned char *)(record[i].GetBuffer(0)), record[i].GetLength()*sizeof(TCHAR));
		}
		file.Flush();
		file.Close();
		log.InLog("Insert Record "+message+" To Table "+tbName+",Database "+dbName);
		//MessageBox(_T("д��ɹ���"));

		myGlobal.state="д��ɹ���";
	    myGlobal.if_reflesh=1;

	}
	catch (CFileException *e)
	{
		CString str;
		str.Format(_T("д��ʧ�ܵ�ԭ����:%d"), e->m_cause);
		//MessageBox(str);

		myGlobal.state=str;
	    myGlobal.if_reflesh=1;

		file.Abort();
		e->Delete();
	}
}