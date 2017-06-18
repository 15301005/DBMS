// Modify_Field.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "Modify_Field.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "KbDbmsDlg.h"
#include "log.h"


// Modify_Field 对话框

IMPLEMENT_DYNAMIC(Modify_Field, CDialogEx)

Modify_Field::Modify_Field(CWnd* pParent /*=NULL*/)
	: CDialogEx(Modify_Field::IDD, pParent)
{

}

Modify_Field::~Modify_Field()
{
}

void Modify_Field::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Modify_Field, CDialogEx)
	ON_BN_CLICKED(IDOK, &Modify_Field::OnBnClickedOk)
END_MESSAGE_MAP()


// Modify_Field 消息处理程序


void Modify_Field::OnBnClickedOk()
{
	CString field_name,datatype,default_value;
	int if_primary_key,if_null;
	field_name="";
	datatype="";
	default_value="";
	if_primary_key=0;
	if_null=0;
	
	GetDlgItemText( IDC_EDIT_FIELD_NAME,field_name);  //获取字段id
	GetDlgItemText( IDC_COMBOX_FIELDTYPE,datatype);  //获取字段id
	GetDlgItemText( IDC_EDIT_DEFAULT,default_value);  //获取字段id
	CButton *pButton = (CButton*)GetDlgItem(IDC_CHECK1);
	if_primary_key=pButton->GetCheck();//获取点击状态，点击后为非零值
	CButton *dButton = (CButton*)GetDlgItem(IDC_CHECK2);
	if_null=dButton->GetCheck();//获取点击状态，点击后为非零值

	if(field_name==""||datatype==""){
		//AfxMessageBox(_T("字段名称或字段类型不能为空!"));
		myGlobal.state="操作失败：字段名称或字段类型不能为空!";
	    myGlobal.if_reflesh=1;
	}else{
		CString primary,ii;
		primary.Format("%d",if_primary_key);
		ii.Format("%d",if_null);
		CString field_value=field_name+"#"+datatype+"#"+default_value+"#"+primary+"#"+ii;

		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //获取选中的数据库名
		CString tbName=myGlobal.tableName;          //获取选中的数据库名
		CString end(".trd");          //加上后缀
		tbName=myGlobal.tableName;
		CString FileName="Output\\data\\"+dbName+"\\"+tbName+end; //整合成为表描述文件名
		//创建或打开表描述文件追加入新表的名字
		if (PathFileExists(FileName)){
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE(" ");               //以空格分隔
		file.Open(FileName, CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符

		/*开始进行长字符串分割以及载入*/
		int nPos = szTemp.Find(strGap);
		CString strLeft = _T("");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			szA[i]=strLeft;

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}

			   szA[i] = szA[i] + " ";    //加上换行符，方便后续再次存入db文件
			   i++;
		}
		file.Close();

		szA[myGlobal.row_index]=field_value+" ";
		CFile f;
			f.Open(FileName,  CFile:: modeCreate|CFile::modeWrite );//打开数据库描述文件重新写入
			for (int j = 0; j <= i;j++){
				f.SeekToEnd();
				//将表名写入 注意*sizeof(TCHAR)否则写入不完整
				f.Write((unsigned char *)(szA[j].GetBuffer(0)), szA[j].GetLength()*sizeof(TCHAR));
				//file.Flush();	
				f.Flush();
			}	
			f.Close();

			log.InLog("Modify field to "+field_name+" from Table "+tbName+",Database "+dbName);
		}
	}
	CDialogEx::OnOK();
}
void Modify_Field::set_text(){
	SetDlgItemText( IDC_EDIT_FIELD_NAME,myGlobal.field_name);  //获取字段id
	SetDlgItemText( IDC_COMBOX_FIELDTYPE,myGlobal.data_type);  //获取字段id
	SetDlgItemText( IDC_EDIT_DEFAULT,myGlobal.default_value);  //获取字段id
	if(myGlobal.if_primary_key==1)
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if(myGlobal.if_null==1)
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
}
