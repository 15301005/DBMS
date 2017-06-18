
// KbDbmsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "KbDbmsDlg.h"
#include "afxdialogex.h"
#include "create_database_dialog.h"
#include "Tree_operation.h"
#include "TableCreate.h"
#include "MyGloble.h"
#include "DropTable.h"
#include "Add_field_dialog.h"
#include <CString>
#include <string>
#include "log.h"
#include "Drop_Table.h"
#include "DropField.h"
#include "Modify_Field.h"
#include "InsertRecord.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpAboutdbms();
	int ABOUT_DIALOG;
	int DIALOG_ABOUT;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
	, ABOUT_DIALOG(0)
	, DIALOG_ABOUT(0)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKbDbmsDlg �Ի���



CKbDbmsDlg::CKbDbmsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKbDbmsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKbDbmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_web_tree);
	DDX_Control(pDX,IDC_LIST1,m_tableList);
}

BEGIN_MESSAGE_MAP(CKbDbmsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_DATABASE_CREATEDATABASE, &CKbDbmsDlg::OnDatabaseCreatedatabase)
	ON_COMMAND(ID_HELP_ABOUTDBMS, &CKbDbmsDlg::OnHelpAboutdbms)
	ON_COMMAND(ID_TABLE_CREATETABLE, &CKbDbmsDlg::OnTableCreatetable)
	ON_COMMAND(ID_TABLE_DROPTABLE, &CKbDbmsDlg::OnTableDroptable)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CKbDbmsDlg::OnTvnSelchangedTree1)
	ON_COMMAND(ID_FIELD_ADDFIELD, &CKbDbmsDlg::OnFieldAddfield)
	ON_COMMAND(ID_DATABASE_OPENDATABASE, &CKbDbmsDlg::OnDatabaseOpendatabase)
	ON_COMMAND(ID_DATABASE_SHOWDATABASE, &CKbDbmsDlg::OnDatabaseShowdatabase)
	ON_COMMAND(ID_SYSTEM_EXIT, &CKbDbmsDlg::OnSystemExit)
	ON_COMMAND(ID_FIELD_DROPFIELD, &CKbDbmsDlg::OnFieldDropfield)
	ON_COMMAND(ID_TABLE_ALTERTABLE, &CKbDbmsDlg::OnTableAltertable)
	ON_COMMAND(ID_TABLE_SHOWTABLEDATA, &CKbDbmsDlg::OnTableShowtabledata)
	ON_COMMAND(ID_FIELD_MODIFYFIELD, &CKbDbmsDlg::OnFieldModifyfield)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CKbDbmsDlg::OnNMRClickList1)
	ON_COMMAND(ID_RECORD_INSERTRECORD, &CKbDbmsDlg::OnRecordInsertrecord)
	ON_COMMAND(ID_RECORD_SELECTRECORD, &CKbDbmsDlg::OnRecordSelectrecord)
	ON_COMMAND(ID_RECORD_UPDATERECORD, &CKbDbmsDlg::OnRecordUpdaterecord)
	ON_COMMAND(ID_RECORD_DELETERECORD, &CKbDbmsDlg::OnRecordDeleterecord)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CKbDbmsDlg ��Ϣ�������

BOOL CKbDbmsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	type=-1;

	SetTimer(1,100,NULL);

	m_StatBar = new CStatusBarCtrl;
	RECT m_Rect;
	GetClientRect(&m_Rect); //��ȡ�Ի���ľ�������
	m_Rect.top = m_Rect.bottom - 20; //����״̬���ľ�������
	m_StatBar->Create(WS_BORDER | WS_VISIBLE | CBRS_BOTTOM, m_Rect, this, 3);
	int nParts[4] = { 100, 200, 300, -1 }; //�ָ�ߴ�
	m_StatBar->SetParts(4, nParts); //�ָ�״̬��
	m_StatBar->SetText(_T("\t����.."),0,0);


	//����������
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("δ�ܴ���������\n");
		return -1; // δ�ܴ���
	}
	//m_ToolBar.LoadBitmap(IDB_BITMAP1);//����ͼƬʧ��
	//m_ToolBar.LoadBitmap(IDB_BITMAP2);
	m_ToolBar.ShowWindow(SW_SHOW);
	m_ToolBar.SetBarStyle(CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);



	CImageList imageList;
	CPngImage png[4];
	HTREEITEM hRoot;
	HTREEITEM hDatabaseItem;
	//HICON hicon[4];
	CBitmap pngBmp[4];

	//��������ͼ��
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//����ͼ������
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//������ͼ����ӵ�ͼ������
	for(int i=0;i<4;i++)
	{
	//	imageList.Add(hicon[i]);
		imageList.Add(&pngBmp[i],RGB(0,0,0));
	}
	
	CString* database_name=tree_operation.get_database_from_db();
	//int h=sizeof(tree_operation.get_database_from_db());
	tree_operation.get_database_from_db();
	int h=tree_operation.database_num;
	for(int i=0;i<h;i++){
		hRoot=m_web_tree.InsertItem(database_name[i],0,0);
	}
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKbDbmsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKbDbmsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKbDbmsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKbDbmsDlg::OnDatabaseCreatedatabase()
{
	// TODO: �ڴ���������������
	create_database_dialog cdd;
	INT_PTR nRes;
	nRes = cdd.DoModal();
	if (IDCANCEL == nRes)
		return ; 
}



void CKbDbmsDlg::OnHelpAboutdbms()
{
	about_dialog about;
	//CAboutDlg about;
	INT_PTR nRes;
	nRes=about.DoModal();
	// TODO: �ڴ���������������
}


void CKbDbmsDlg::OnTableCreatetable()
{
	type=1;
	// TODO:  �ڴ���������������

	//��ѡ����һ�����ݿ�ʱ�ɴ����� �����跴Ӧ
	TableCreate Dlg;
	Dlg.DoModal();
	//������д�����ݿ��ļ� �������������ļ�
	if (myGlobal.tableName != ""){
		CRect rect;

		// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
		m_tableList.GetClientRect(&rect);
		
		// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
		m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_tableList.DeleteAllItems();
		// Ϊ�б���ͼ�ؼ��������   
		m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);

	}
	OnDatabaseOpendatabase();
	//OnTableShowtabledata();
}


void CKbDbmsDlg::OnTableDroptable()
{
	type=1;
	// TODO:  �ڴ���������������
	//DropTable Dlg2;
	//Dlg2.DoModal();
	int if_succeed;
	if_succeed=drop_table.drop_table();
	if(if_succeed==0){
		AfxMessageBox("ɾ�����ʧ�ܣ�");
	}else{
		OnDatabaseOpendatabase();
	}
}


//��ȡ�����ctree�Ľڵ�
void CKbDbmsDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CString strText; // ���ڵ�ı�ǩ�ı��ַ���   

	CPoint pt;
    GetCursorPos(&pt);
    m_web_tree.ScreenToClient(&pt);
	HTREEITEM HH=m_web_tree.GetSelectedItem();
    HTREEITEM hItem = m_web_tree.HitTest(pt);
    if(hItem)
    {
        int nIndex = 1;
        while(NULL != (hItem = m_web_tree.GetParentItem(hItem)))
        {
            nIndex++;
        }
        //CString strText(_T(""));
        //strText.Format(_T("Index: %d"), nIndex);
        //AfxMessageBox(strText);
		CString strText(_T(""));
		switch(nIndex){
		case 1:
			myGlobal.db_name=m_web_tree.GetItemText(HH);
			//AfxMessageBox(_T(myGlobal.db_name));
			break;
		case 2:
			HTREEITEM database;
			database = m_web_tree.GetParentItem(HH);
			myGlobal.db_name=m_web_tree.GetItemText(database);
			myGlobal.tableName=m_web_tree.GetItemText(HH);
			//AfxMessageBox(_T(myGlobal.db_name+myGlobal.tableName));
			break;
		case 3:
			HTREEITEM table1;
			table1 = m_web_tree.GetParentItem(HH);
			HTREEITEM database1;
			database1 = m_web_tree.GetParentItem(table1);
			myGlobal.db_name=m_web_tree.GetItemText(database1);
			myGlobal.tableName=m_web_tree.GetItemText(table1);
			myGlobal.field=m_web_tree.GetItemText(HH);
			//AfxMessageBox(AfxMessageBox(_T(myGlobal.db_name+myGlobal.tableName+myGlobal.field)));
			break;
		default:
			break;
		}
    }

	*pResult = 0;
}


void CKbDbmsDlg::OnFieldAddfield()
{
	CRect rect;
	m_tableList.GetClientRect(&rect);
	type=1;
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// Ϊ�б���ͼ�ؼ��������   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	
	// TODO: �ڴ���������������
	Add_field_dialog add;
	INT_PTR nRes;
	nRes = add.DoModal();
	if (IDCANCEL == nRes)
		return ; 
	
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//���ұ�ɾ����¼
		//��db�ļ��������
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		CString field[24];//����ֶ���Ϣ
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE("#");               //�Կո�ָ�
		file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���*/

		/*��ʼ���г��ַ����ָ��Լ�����*/
	
		int nPos = szTemp.Find(strGap);
		int nn=0;
		CString strLeft = _T("");
		CString str=_T("");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			szA[i]=strLeft;

			int j=0;
			nn=szA[i].Find(toE);
			while(0<nn){
				str = szA[i].Left(nn); 
			if (!str.IsEmpty())
			   field[j]=str;

			if(j==0)
			   m_tableList.InsertItem(i,field[j]);
			else
				m_tableList.SetItemText(i,j,field[j]);

			szA[i]=szA[i].Right(szA[i].GetLength() - nn - 1);
			nn = szA[i].Find(toE);
			if (!szA[i].IsEmpty()) {
				field[j+1]=szA[i];
			}
			j++;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}
			
			i++;
			szA[i] = szA[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
		file.Close();
		if(nRes==IDOK){
		OnDatabaseOpendatabase();
		OnTableShowtabledata();
	}
}


void CKbDbmsDlg::OnDatabaseOpendatabase()
{
	m_web_tree.SetRedraw(FALSE);  
    m_web_tree.DeleteAllItems();  
   
	CImageList imageList;
	CPngImage png[4];
	HTREEITEM database_item;
	HTREEITEM table_item;
	HTREEITEM field_item;
	//HTREEITEM hFieldItem;
	//HICON hicon[4];
	CBitmap pngBmp[4];

	//��������ͼ��
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//����ͼ������
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//������ͼ����ӵ�ͼ������
	for(int i=0;i<4;i++)
	{
	//	imageList.Add(hicon[i]);
		imageList.Add(&pngBmp[i],RGB(0,0,0));
	}
	database_item=m_web_tree.InsertItem(myGlobal.db_name,0,0);
	CString* table_name=tree_operation.get_table_from_tb(myGlobal.db_name);
	for(int i=0;i<tree_operation.table_num;i++){
		table_item=m_web_tree.InsertItem(table_name[i],1,1,database_item,TVI_LAST);
		CString* field=tree_operation.get_fieldfrom_tdf(myGlobal.db_name,table_name[i]);
		for(int j=0;j<tree_operation.field_num;j++){
			field_item=m_web_tree.InsertItem(field[j],2,2,table_item,TVI_LAST);
		}
	}

	log.InLog("Open Database "+myGlobal.db_name);
	m_web_tree.SetRedraw(TRUE);  
    m_web_tree.RedrawWindow(); 
	
}


void CKbDbmsDlg::OnDatabaseShowdatabase()
{
	m_web_tree.SetRedraw(FALSE);  
    m_web_tree.DeleteAllItems();  
   
	CImageList imageList;
	CPngImage png[4];
	HTREEITEM hRoot;
	HTREEITEM hDatabaseItem;
	//HICON hicon[4];
	CBitmap pngBmp[4];

	//��������ͼ��
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//����ͼ������
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//������ͼ����ӵ�ͼ������
	for(int i=0;i<4;i++)
	{
	//	imageList.Add(hicon[i]);
		imageList.Add(&pngBmp[i],RGB(0,0,0));
	}
	
	CString* database_name=tree_operation.get_database_from_db();
	//int h=sizeof(tree_operation.get_database_from_db());
	tree_operation.get_database_from_db();
	int h=tree_operation.database_num;
	for(int i=0;i<h;i++){
		hRoot=m_web_tree.InsertItem(database_name[i],0,0);
	}

	m_web_tree.SetRedraw(TRUE);  
    m_web_tree.RedrawWindow(); 
}


void CKbDbmsDlg::OnSystemExit()
{
	log.InLog("Exit");
	exit(0);
	// TODO: �ڴ���������������
}


void CKbDbmsDlg::OnFieldDropfield()
{
	type=1;
	int field_id[24],i=0;
	while(m_tableList.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
    {
       int nItem = m_tableList.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
       m_tableList.DeleteItem(nItem);
	   field_id[i]=nItem;
	   i++;
    }
	drop_field.drop_field(field_id,i);
	OnDatabaseOpendatabase();
	OnTableShowtabledata();
}


void CKbDbmsDlg::OnTableAltertable()
{
	CRect rect;
	m_tableList.GetClientRect(&rect);
	type=1;
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// Ϊ�б���ͼ�ؼ��������   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	
	// TODO: �ڴ���������������
	Add_field_dialog add;
	INT_PTR nRes;
	nRes = add.DoModal();
	if (IDCANCEL == nRes)
		return ; 
	
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//���ұ�ɾ����¼
		//��db�ļ��������
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		CString field[24];//����ֶ���Ϣ
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE("#");               //�Կո�ָ�
		file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���*/

		/*��ʼ���г��ַ����ָ��Լ�����*/
	
		int nPos = szTemp.Find(strGap);
		int nn=0;
		CString strLeft = _T("");
		CString str=_T("");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			szA[i]=strLeft;

			int j=0;
			nn=szA[i].Find(toE);
			while(0<nn){
				str = szA[i].Left(nn); 
			if (!str.IsEmpty())
			   field[j]=str;

			if(j==0)
			   m_tableList.InsertItem(i,field[j]);
			else
				m_tableList.SetItemText(i,j,field[j]);

			szA[i]=szA[i].Right(szA[i].GetLength() - nn - 1);
			nn = szA[i].Find(toE);
			if (!szA[i].IsEmpty()) {
				field[j+1]=szA[i];
			}
			j++;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}
			
			i++;
			szA[i] = szA[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
		file.Close();
		if(nRes==IDOK){
		OnDatabaseOpendatabase();
		OnTableShowtabledata();
		myGlobal.state="�����ɹ���";
		myGlobal.if_reflesh=1;
	}
		
}


void CKbDbmsDlg::OnTableShowtabledata()
{
	CRect rect;
	m_tableList.GetClientRect(&rect);
	type=1;
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// Ϊ�б���ͼ�ؼ��������   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	log.InLog("Show Table "+myGlobal.tableName+" From Database "+myGlobal.db_name);

	// TODO: �ڴ���������������
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//���ұ�ɾ����¼
		//��db�ļ��������
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		CString field[24];//����ֶ���Ϣ
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE("#");               //�Կո�ָ�
		file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���*/

		/*��ʼ���г��ַ����ָ��Լ�����*/
	
		int nPos = szTemp.Find(strGap);
		int nn=0;
		CString strLeft = _T("");
		CString str=_T("");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			szA[i]=strLeft;

			int j=0;
			nn=szA[i].Find(toE);
			while(0<nn){
				str = szA[i].Left(nn); 
			if (!str.IsEmpty())
			   field[j]=str;

			if(j==0)
			   m_tableList.InsertItem(i,field[j]);
			else
				m_tableList.SetItemText(i,j,field[j]);

			szA[i]=szA[i].Right(szA[i].GetLength() - nn - 1);
			nn = szA[i].Find(toE);
			if (!szA[i].IsEmpty()) {
				field[j+1]=szA[i];
			}
			j++;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}
			
			i++;
			szA[i] = szA[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
		file.Close();
}

void CKbDbmsDlg::OnFieldModifyfield()
{
	type=1;
	int  nSelectIndex=m_tableList.GetSelectionMark();//��ȡѡ����к�
	CString  str0=m_tableList.GetItemText(nSelectIndex,0);//nColumn������Ҫ ��ȡ�������ڵ�����
    CString  str1=m_tableList.GetItemText(nSelectIndex,1);//nColumn������Ҫ ��ȡ�������ڵ�����
	CString  str2=m_tableList.GetItemText(nSelectIndex,2);//nColumn������Ҫ ��ȡ�������ڵ�����
	CString  str3=m_tableList.GetItemText(nSelectIndex,3);//nColumn������Ҫ ��ȡ�������ڵ�����
	CString  str4=m_tableList.GetItemText(nSelectIndex,4);//nColumn������Ҫ ��ȡ�������ڵ�����
	myGlobal.field_name=str0;
	myGlobal.data_type=str1;
	myGlobal.default_value=str2;
	myGlobal.if_primary_key=atoi(str3);
	myGlobal.if_null=atoi(str4);

	myGlobal.row_index=m_tableList.GetNextItem(-1,LVIS_SELECTED); 
	//modify_field.set_text();
	INT_PTR nRes;
	nRes = modify_field.DoModal();
	if(nRes==IDOK){
		OnDatabaseOpendatabase();
		OnTableShowtabledata();
	}
}


void CKbDbmsDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CPoint pt;
	::GetCursorPos(&pt);	//��ȡ�������
	CMenu	menu;
	//���ز˵�
	if (type==0){//typeΪ0ʱ����record�б��һ��˵�
		if (!menu.LoadMenuA(IDR_POPUP_LIST))//LoadMenuW(IDR_POPUP_LIST))
		{
			return;
		}
		//����Ӳ˵�
	CMenu *pPopupMenu = menu.GetSubMenu(0);		//���Ϊ0���Ӳ˵�
	//�����˵�
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
}

MyGlobal CKbDbmsDlg::return_myGlobal(){
	return myGlobal;
}

void CKbDbmsDlg::OnRecordInsertrecord()
{
	// TODO: �ڴ���������������
	CInsertRecord Dlg3;
	Dlg3.DoModal();
	selectRecord();
}


void CKbDbmsDlg::OnRecordSelectrecord()
{
	selectRecord();
}


void CKbDbmsDlg::OnRecordUpdaterecord()
{
	// TODO:  �ڴ���������������
	POSITION p = m_tableList.GetFirstSelectedItemPosition();    //��ȡ��ѡ����λ��
	myGlobal.ifUpdate = m_tableList.GetNextSelectedItem(p); //��ȡѡ���е�����;
	if (myGlobal.ifUpdate==-1){//δѡ�����򲻽����κβ���
		//myGlobal.ifUpdate = NULL;
	}
	else
	{
        CInsertRecord Dlg4;
		Dlg4.DoModal();
		myGlobal.ifUpdate = NULL;
		selectRecord();
	}
}


void CKbDbmsDlg::OnRecordDeleterecord()
{
	// TODO:  �ڴ���������������
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_tableList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	POSITION p = m_tableList.GetFirstSelectedItemPosition();    //��ȡ��ѡ����λ��
	while (p)
	{
		int  nSelected = m_tableList.GetNextSelectedItem(p); //��ȡѡ���е�����
		m_tableList.DeleteItem(nSelected); //��������ɾ��
		p = m_tableList.GetFirstSelectedItemPosition();  //������㲻һ���������������д�Ļ�����ɾ��λ�ģ�������ѡ��1��2���У���ɾ��һ�к���������������һ�����ڶ���ɾ��ɾ��ԭ�ȵĵ�����ȥ, ���������¼���ѡ������ɾ��һ�����listctl��λ��
	}

	writeRecordToFile();
}



void CKbDbmsDlg::selectRecord()
{
	type=0;
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_tableList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	
	//���ڿ����ظ��鿴����ˣ����´���ʾ֮ǰ�����������
	int nCols = m_tableList.GetHeaderCtrl()->GetItemCount();
	for (int j = 0; j < nCols; j++)
	{
		m_tableList.DeleteColumn(0);
	}
	m_tableList.DeleteAllItems();

	readTableConlumn();
	for (int i = 0; i < ConNum;i++)
	{
		m_tableList.InsertColumn(i, recordColumn[i], LVCFMT_CENTER, rect.Width() / ConNum, i);
	}
    
	CString*recordRow = new CString[24];
	CString* recordData = new CString[24];
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

				recordData[j] = str;
			if (j==0)
				m_tableList.InsertItem(i, recordData[j]);
			else m_tableList.SetItemText(i, j, recordData[j]);

			recordRow[i] = recordRow[i].Right(recordRow[i].GetLength() - nn - 1);
			nn = recordRow[i].Find(toE);
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
}



void CKbDbmsDlg::readTableConlumn()
{
    CString*recordRow = new CString[24];
	recordColumn = new CString[24];
	ConNum = 0;
	//��ȡ�ļ��е�column��Ŀ��ʼ����recordRow��
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".trd");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//���ұ�ɾ����¼
	//��db�ļ��������
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//�����������
	BOOLEAN ifFind = 0;//����Ƿ��ҵ���Ӧ�����
	CString toE("#");               //�Կո�ָ�
	file.Open(dbPath, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
	//int i = 0;                             //��ʼ���������־
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
			recordRow[ConNum] = strLeft;

		int j = 0;
		nn = recordRow[ConNum].Find(toE);
		while (0<nn){
			str = recordRow[ConNum].Left(nn);
			if (!str.IsEmpty())

			if (j == 0)
			{
				recordColumn[ConNum] = str;
				//m_tableList.InsertItem(i, recordColumn[i]);
			}

			recordRow[ConNum] = recordRow[ConNum].Right(recordRow[ConNum].GetLength() - nn - 1);
			nn = recordRow[ConNum].Find(toE);
			j++;
		}

		szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
		nPos = szTemp.Find(strGap);
		if (!szTemp.IsEmpty()) {
			recordRow[ConNum + 1] = szTemp;
		}

		ConNum++;
		//recordRow[i] = recordRow[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
	}
	file.Close();
}

void CKbDbmsDlg::writeRecordToFile()
{
    CString *record=new CString[24];
	CString split("#");
	CString split2(" ");
	CString temp;
	int row = m_tableList.GetItemCount();
	int column= m_tableList.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp = m_tableList.GetItemText(i, j);
			if (temp != "") record[i] = record[i] + temp + split;
			else record[i] = record[i] + "null" + split;
		}
		record[i] = record[i] + split2;
	}

	//����ȡ��ֵ����д���ļ�
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
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite);
		//���±����д�� ע��*sizeof(TCHAR)����д�벻����
		for (int i = 0; i < row; i++){
			file.SeekToEnd();
			file.Write((unsigned char *)(record[i].GetBuffer(0)), record[i].GetLength()*sizeof(TCHAR));
		}
		file.Flush();
		file.Close();
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

void CKbDbmsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(myGlobal.if_reflesh==1){
		m_StatBar->SetText(myGlobal.state,0,0);
		myGlobal.if_reflesh=0;
	}
	CDialogEx::OnTimer(nIDEvent);
}
