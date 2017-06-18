// Add_field_dialog.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "Add_field_dialog.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "log.h"


// Add_field_dialog 对话框

IMPLEMENT_DYNAMIC(Add_field_dialog, CDialogEx)

Add_field_dialog::Add_field_dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(Add_field_dialog::IDD, pParent)
	, ADD_FIELD_DIALOG(0)
{

}

Add_field_dialog::~Add_field_dialog()
{
}

void Add_field_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, if_primary_key);
	DDX_Control(pDX, IDC_CHECK2, if_null);
	DDX_Control(pDX, IDC_COMBOX_FIELDTYPE, get_field_type);
}


BEGIN_MESSAGE_MAP(Add_field_dialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &Add_field_dialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBOX_FIELDTYPE, &Add_field_dialog::OnCbnSelchangeComboxFieldtype)
END_MESSAGE_MAP()


// Add_field_dialog 消息处理程序


void Add_field_dialog::OnBnClickedOk()
{
	CString field_id,default_value,field_type;
	int if_primary=0,if_null=0;
	field_id="",default_value="",field_type="INT";

	GetDlgItemText( IDC_EDIT_FIELD_NAME,field_id);  //获取字段id
	GetDlgItemText(IDC_COMBOX_FIELDTYPE,field_type);
	GetDlgItemText( IDC_EDIT_DEFAULT,default_value);  //获取默认值
	CButton *pButton = (CButton*)GetDlgItem(IDC_CHECK1);
	if_primary=pButton->GetCheck();//获取点击状态，点击后为非零值
	CButton *dButton = (CButton*)GetDlgItem(IDC_CHECK2);
	if_null=dButton->GetCheck();//获取点击状态，点击后为非零值

	if(field_id==""||field_type==""){
		AfxMessageBox(_T("字段名称或字段类型不能为空!"));
	}else{
		CString primary,ii;
		primary.Format("%d",if_primary);
		ii.Format("%d",if_null);
		CString field_value=field_id+"#"+field_type+"#"+default_value+"#"+primary+"#"+ii+"#";
		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //获取选中的数据库名
		CString tbName=myGlobal.tableName;          //获取选中的数据库名
		CString end(".trd");          //加上后缀
		tbName=myGlobal.tableName;
		CString FileName="Output\\data\\"+dbName+"\\"+tbName+end; //整合成为表描述文件名
		//创建或打开表描述文件追加入新表的名字
		try
			{
			file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			file.SeekToEnd();
			//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
			CString toE(" ");
			CString TableName = field_value + toE;
			file.Write((unsigned char *)(TableName.GetBuffer(0)), TableName.GetLength()*sizeof(TCHAR));
			file.Flush();
			file.Close();
			log.InLog("Add Field "+field_id+" From Table "+tbName+",Database "+dbName);
			//MessageBox(_T("写入成功！"));

			myGlobal.state="写入成功！";
	        myGlobal.if_reflesh=1;

			}catch (CFileException *e)
			{
			CString str;
			str.Format(_T("写入失败的原因是:%d"), e->m_cause);
			//MessageBox(str);
			myGlobal.state=str;
	        myGlobal.if_reflesh=1;

			file.Abort();
			e->Delete();
			}
		CDialogEx::OnOK();
	}
}


void Add_field_dialog::OnCbnSelchangeComboxFieldtype()
{
	// TODO: 在此添加控件通知处理程序代码
}
