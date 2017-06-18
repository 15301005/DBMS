
// KbDbmsDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CKbDbmsDlg 对话框



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


// CKbDbmsDlg 消息处理程序

BOOL CKbDbmsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	// TODO:  在此添加额外的初始化代码

	type=-1;

	SetTimer(1,100,NULL);

	m_StatBar = new CStatusBarCtrl;
	RECT m_Rect;
	GetClientRect(&m_Rect); //获取对话框的矩形区域
	m_Rect.top = m_Rect.bottom - 20; //设置状态栏的矩形区域
	m_StatBar->Create(WS_BORDER | WS_VISIBLE | CBRS_BOTTOM, m_Rect, this, 3);
	int nParts[4] = { 100, 200, 300, -1 }; //分割尺寸
	m_StatBar->SetParts(4, nParts); //分割状态栏
	m_StatBar->SetText(_T("\t就绪.."),0,0);


	//创建工具栏
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("未能创建工具栏\n");
		return -1; // 未能创建
	}
	//m_ToolBar.LoadBitmap(IDB_BITMAP1);//载入图片失败
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

	//加载三个图标
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//创建图像序列
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//将三个图标添加到图像序列
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
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKbDbmsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKbDbmsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKbDbmsDlg::OnDatabaseCreatedatabase()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
}


void CKbDbmsDlg::OnTableCreatetable()
{
	type=1;
	// TODO:  在此添加命令处理程序代码

	//当选中了一个数据库时可创建表 否则不予反应
	TableCreate Dlg;
	Dlg.DoModal();
	//将表名写入数据库文件 并创建表描述文件
	if (myGlobal.tableName != ""){
		CRect rect;

		// 获取编程语言列表视图控件的位置和大小   
		m_tableList.GetClientRect(&rect);
		
		// 为列表视图控件添加全行选中和栅格风格   
		m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_tableList.DeleteAllItems();
		// 为列表视图控件添加三列   
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
	// TODO:  在此添加命令处理程序代码
	//DropTable Dlg2;
	//Dlg2.DoModal();
	int if_succeed;
	if_succeed=drop_table.drop_table();
	if(if_succeed==0){
		AfxMessageBox("删除表格失败！");
	}else{
		OnDatabaseOpendatabase();
	}
}


//获取所点击ctree的节点
void CKbDbmsDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	 CString strText; // 树节点的标签文本字符串   

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
	// 为列表视图控件添加全行选中和栅格风格   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// 为列表视图控件添加三列   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	
	// TODO: 在此添加命令处理程序代码
	Add_field_dialog add;
	INT_PTR nRes;
	nRes = add.DoModal();
	if (IDCANCEL == nRes)
		return ; 
	
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//查找表并删除记录
		//若db文件存在则打开
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		CString field[24];//存放字段信息
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE("#");               //以空格分隔
		file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符*/

		/*开始进行长字符串分割以及载入*/
	
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
			szA[i] = szA[i] + toE;    //加上换行符，方便后续再次存入db文件
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

	//加载三个图标
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//创建图像序列
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//将三个图标添加到图像序列
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

	//加载三个图标
	png[0].Load(IDB_PNG6);
	png[1].Load(IDB_PNG1);
	png[2].Load(IDB_PNG4);
	png[3].Load(IDB_PNG5);

	pngBmp[0].Attach(png[0].Detach());
	pngBmp[1].Attach(png[1].Detach());
	pngBmp[2].Attach(png[2].Detach());
	pngBmp[3].Attach(png[3].Detach());
	//创建图像序列
	imageList.Create(16,16,ILC_COLOR32|ILC_MASK,4,4);
	//imageList.Create(25,25,ILC_COLOR32,4,4);
	//将三个图标添加到图像序列
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
	// TODO: 在此添加命令处理程序代码
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
	// 为列表视图控件添加全行选中和栅格风格   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// 为列表视图控件添加三列   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	
	// TODO: 在此添加命令处理程序代码
	Add_field_dialog add;
	INT_PTR nRes;
	nRes = add.DoModal();
	if (IDCANCEL == nRes)
		return ; 
	
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//查找表并删除记录
		//若db文件存在则打开
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		CString field[24];//存放字段信息
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE("#");               //以空格分隔
		file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符*/

		/*开始进行长字符串分割以及载入*/
	
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
			szA[i] = szA[i] + toE;    //加上换行符，方便后续再次存入db文件
		}
		file.Close();
		if(nRes==IDOK){
		OnDatabaseOpendatabase();
		OnTableShowtabledata();
		myGlobal.state="操作成功！";
		myGlobal.if_reflesh=1;
	}
		
}


void CKbDbmsDlg::OnTableShowtabledata()
{
	CRect rect;
	m_tableList.GetClientRect(&rect);
	type=1;
	// 为列表视图控件添加全行选中和栅格风格   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_tableList.DeleteAllItems();
	// 为列表视图控件添加三列   
	m_tableList.InsertColumn(0, _T("Column"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_tableList.InsertColumn(1, _T("Data Type"), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_tableList.InsertColumn(2, _T("Not NULL"), LVCFMT_CENTER, rect.Width() / 5, 5);
	m_tableList.InsertColumn(2, _T("Primary Key"), LVCFMT_CENTER, rect.Width() / 5, 4);
	//m_tableList.InsertColumn(2, _T("Foreign Key"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_tableList.InsertColumn(2, _T("Default Value"), LVCFMT_CENTER, rect.Width() / 5, 3);
	log.InLog("Show Table "+myGlobal.tableName+" From Database "+myGlobal.db_name);

	// TODO: 在此添加命令处理程序代码
	    CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string,dbFileName,m_externDB(".trd");
		dbFileName = myGlobal.db_name+"\\"+myGlobal.tableName + m_externDB;
		//查找表并删除记录
		//若db文件存在则打开
		CString dbPath=forder +dbFileName;
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		CString field[24];//存放字段信息
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE("#");               //以空格分隔
		file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符*/

		/*开始进行长字符串分割以及载入*/
	
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
			szA[i] = szA[i] + toE;    //加上换行符，方便后续再次存入db文件
		}
		file.Close();
}

void CKbDbmsDlg::OnFieldModifyfield()
{
	type=1;
	int  nSelectIndex=m_tableList.GetSelectionMark();//获取选择的行号
	CString  str0=m_tableList.GetItemText(nSelectIndex,0);//nColumn代表你要 获取的列所在的索引
    CString  str1=m_tableList.GetItemText(nSelectIndex,1);//nColumn代表你要 获取的列所在的索引
	CString  str2=m_tableList.GetItemText(nSelectIndex,2);//nColumn代表你要 获取的列所在的索引
	CString  str3=m_tableList.GetItemText(nSelectIndex,3);//nColumn代表你要 获取的列所在的索引
	CString  str4=m_tableList.GetItemText(nSelectIndex,4);//nColumn代表你要 获取的列所在的索引
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
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	CPoint pt;
	::GetCursorPos(&pt);	//获取鼠标坐标
	CMenu	menu;
	//加载菜单
	if (type==0){//type为0时加载record列表右击菜单
		if (!menu.LoadMenuA(IDR_POPUP_LIST))//LoadMenuW(IDR_POPUP_LIST))
		{
			return;
		}
		//获得子菜单
	CMenu *pPopupMenu = menu.GetSubMenu(0);		//编号为0的子菜单
	//弹出菜单
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
}

MyGlobal CKbDbmsDlg::return_myGlobal(){
	return myGlobal;
}

void CKbDbmsDlg::OnRecordInsertrecord()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO:  在此添加命令处理程序代码
	POSITION p = m_tableList.GetFirstSelectedItemPosition();    //获取首选中行位置
	myGlobal.ifUpdate = m_tableList.GetNextSelectedItem(p); //获取选中行的索引;
	if (myGlobal.ifUpdate==-1){//未选中行则不进行任何操作
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
	// TODO:  在此添加命令处理程序代码
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_tableList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	POSITION p = m_tableList.GetFirstSelectedItemPosition();    //获取首选中行位置
	while (p)
	{
		int  nSelected = m_tableList.GetNextSelectedItem(p); //获取选中行的索引
		m_tableList.DeleteItem(nSelected); //根据索引删除
		p = m_tableList.GetFirstSelectedItemPosition();  //这里跟你不一样，如果不是这样写的话，会删错位的，比如你选了1，2两行，当删第一行后，如果跟你上面代码一样，第二次删会删到原先的第三行去, 这个语句重新计算选中行在删掉一条后的listctl中位置
	}

	writeRecordToFile();
}



void CKbDbmsDlg::selectRecord()
{
	type=0;
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_tableList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_tableList.SetExtendedStyle(m_tableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	
	//由于可以重复查看，因此，在下次显示之前清空所有数据
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
		//recordRow[i] = recordRow[i] + toE;    //加上换行符，方便后续再次存入db文件
	}
	file.Close();
}



void CKbDbmsDlg::readTableConlumn()
{
    CString*recordRow = new CString[24];
	recordColumn = new CString[24];
	ConNum = 0;
	//读取文件中的column数目初始化到recordRow中
	CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
	CString string, dbFileName, m_externDB(".trd");
	dbFileName = myGlobal.db_name + "\\" + myGlobal.tableName + m_externDB;
	//查找表并删除记录
	//若db文件存在则打开
	CString dbPath = forder + dbFileName;
	CFile file;
	CString szTemp;//存放所有数据
	BOOLEAN ifFind = 0;//标记是否找到相应表表名
	CString toE("#");               //以空格分隔
	file.Open(dbPath, CFile::modeRead);//以读的方式打开文件
	//int i = 0;                             //初始化表个数标志
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
		//recordRow[i] = recordRow[i] + toE;    //加上换行符，方便后续再次存入db文件
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

	//将获取的值重新写入文件
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
		file.Open(FileName, CFile::modeCreate | CFile::modeWrite);
		//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
		for (int i = 0; i < row; i++){
			file.SeekToEnd();
			file.Write((unsigned char *)(record[i].GetBuffer(0)), record[i].GetLength()*sizeof(TCHAR));
		}
		file.Flush();
		file.Close();
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

void CKbDbmsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(myGlobal.if_reflesh==1){
		m_StatBar->SetText(myGlobal.state,0,0);
		myGlobal.if_reflesh=0;
	}
	CDialogEx::OnTimer(nIDEvent);
}
