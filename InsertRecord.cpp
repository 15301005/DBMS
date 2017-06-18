// InsertRecord.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "InsertRecord.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "log.h"


// CInsertRecord 对话框

IMPLEMENT_DYNAMIC(CInsertRecord, CDialogEx)

CInsertRecord::CInsertRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertRecord::IDD, pParent)
{
	ifUpdate=-1;  //是否是更新操作，更新的是哪一行数据
	recordNum=0;  //记录数目

	if (myGlobal.ifUpdate != -1) ifUpdate = myGlobal.ifUpdate;
	num = 0;
	recordRow = new CString[24];
	recordColumn = new CString[24];
	recordDataType = new CString[24];
    //读取文件中的column数目初始化到recordRow中
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".trd");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//查找表并删除记录
	//若db文件存在则打开
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//存放所有数据
	//CString szA[24];//存放表名
	//CString field[24];//存放字段信息
	BOOLEAN ifFind = 0;//标记是否找到相应表表名
	CString toE("#");               //以空格分隔
	file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
	int i = 0;                             //初始化表个数标志
	file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
	CString strGap = _T(" ");//初始化分隔符*/

	/*开始进行长字符串分割以及载入*/

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
		//recordRow[i] = recordRow[i] + toE;    //加上换行符，方便后续再次存入db文件
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

	// 获取编程语言列表视图控件的位置和大小   
	recordList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	recordList.SetExtendedStyle(recordList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// List header
	recordList.InsertColumn(0, _T("Field Name"), LVCFMT_LEFT, 100);
	recordList.InsertColumn(1, _T("Field Type"), LVCFMT_LEFT, 100);
	recordList.InsertColumn(3, _T("Value"), LVCFMT_LEFT, 150);
	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);

	//对recordRow中的数据段进行解析并且写入到列表进行创建

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


// CInsertRecord 消息处理程序


void CInsertRecord::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	// Get the value of the edit control
	CString strValue;
	m_editValue.GetWindowText(strValue);

	// Assign the value of the edit control to list item
	recordList.SetItemText(m_dwItem, m_nSubItem, strValue);

	// Hide the edit control
	m_editValue.ShowWindow(SW_HIDE);
}

/*在点击确定时对可编辑部分的内容进行读取，读取后将记录追加在列表和文件最后*/
void CInsertRecord::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	newRecord;
	CString split("#");
	CString split2(" ");
	for (int i = 0; i < num;i++)
	{
		recordRow[i]=recordList.GetItemText(i,2);
		if (recordRow[i] != "") newRecord = newRecord + recordRow[i] + split;
		else newRecord = newRecord + "null" + split;
	}

	//将获取的值写入文件对应位置
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
	//将对应文件中的记录读入到数组
	readRecord();

	//将对应改变位置的数据置换
	record[ifUpdate] = newRecord;

	//将改变后的数据重新写入文件
	writeToFile();
}

void CInsertRecord::OnInsert()
{
	CFile file;
	//char ss[20]="data.txt";
	CString dbName = myGlobal.db_name;          //获取选中的数据库名
	CString tbName = myGlobal.tableName;          //获取选中的数据库名
	CString end(".tid");          //加上后缀
	tbName = myGlobal.tableName;
	CString forder("Output\\data\\");
	CString FileName = forder + dbName + "\\" + tbName + end; //整合成为表描述文件名
	//创建或打开表描述文件追加入新表的名字
	try
	{
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
		file.Write((unsigned char *)(newRecord.GetBuffer(0)), newRecord.GetLength()*sizeof(TCHAR));
		file.Flush();
		file.Close();
		//MessageBox(_T("写入成功！"));
		myGlobal.state="操作成功！";
	    myGlobal.if_reflesh=1;
	}
	catch (CFileException *e)
	{
		CString str;
		str.Format(_T("写入失败的原因是:%d"), e->m_cause);
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
	//读取文件中的column数目初始化到recordRow中
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".tid");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//查找表并删除记录
	//若db文件存在则打开
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//存放所有数据
	BOOLEAN ifFind = 0;//标记是否找到相应表表名
	//CString toE("#");               //以空格分隔
	file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
	recordNum = 0;                             //初始化表个数标志
	file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
	CString strGap = _T(" ");//初始化分隔符*/

	/*开始进行长字符串分割以及载入*/

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

        record[recordNum] = record[recordNum] + strGap;    //加上换行符，方便后续再次存入db文件
		recordNum++;
	}
	file.Close();
	myGlobal.state="读取数据成功！";
	myGlobal.if_reflesh=1;
}

void CInsertRecord::writeToFile()
{
	//将获取的值重新写入文件
	CFile file;
	//char ss[20]="data.txt";
	CString message;
	message="";
	CString dbName = myGlobal.db_name;          //获取选中的数据库名
	CString tbName = myGlobal.tableName;          //获取选中的数据库名
	CString end(".tid");          //加上后缀
	tbName = myGlobal.tableName;
	CString forder("Output\\data\\");
	CString FileName = forder + dbName + "\\" + tbName + end; //整合成为表描述文件名
	//创建或打开表描述文件追加入新表的名字
	try
	{
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite);
		//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
		for (int i = 0; i < recordNum; i++){
			message+=record[i]+" ";
			file.SeekToEnd();
			file.Write((unsigned char *)(record[i].GetBuffer(0)), record[i].GetLength()*sizeof(TCHAR));
		}
		file.Flush();
		file.Close();
		log.InLog("Insert Record "+message+" To Table "+tbName+",Database "+dbName);
		//MessageBox(_T("写入成功！"));

		myGlobal.state="写入成功！";
	    myGlobal.if_reflesh=1;

	}
	catch (CFileException *e)
	{
		CString str;
		str.Format(_T("写入失败的原因是:%d"), e->m_cause);
		//MessageBox(str);

		myGlobal.state=str;
	    myGlobal.if_reflesh=1;

		file.Abort();
		e->Delete();
	}
}