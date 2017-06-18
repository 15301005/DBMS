// Add_field_dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "Add_field_dialog.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "log.h"


// Add_field_dialog �Ի���

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


// Add_field_dialog ��Ϣ�������


void Add_field_dialog::OnBnClickedOk()
{
	CString field_id,default_value,field_type;
	int if_primary=0,if_null=0;
	field_id="",default_value="",field_type="INT";

	GetDlgItemText( IDC_EDIT_FIELD_NAME,field_id);  //��ȡ�ֶ�id
	GetDlgItemText(IDC_COMBOX_FIELDTYPE,field_type);
	GetDlgItemText( IDC_EDIT_DEFAULT,default_value);  //��ȡĬ��ֵ
	CButton *pButton = (CButton*)GetDlgItem(IDC_CHECK1);
	if_primary=pButton->GetCheck();//��ȡ���״̬�������Ϊ����ֵ
	CButton *dButton = (CButton*)GetDlgItem(IDC_CHECK2);
	if_null=dButton->GetCheck();//��ȡ���״̬�������Ϊ����ֵ

	if(field_id==""||field_type==""){
		AfxMessageBox(_T("�ֶ����ƻ��ֶ����Ͳ���Ϊ��!"));
	}else{
		CString primary,ii;
		primary.Format("%d",if_primary);
		ii.Format("%d",if_null);
		CString field_value=field_id+"#"+field_type+"#"+default_value+"#"+primary+"#"+ii+"#";
		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //��ȡѡ�е����ݿ���
		CString tbName=myGlobal.tableName;          //��ȡѡ�е����ݿ���
		CString end(".trd");          //���Ϻ�׺
		tbName=myGlobal.tableName;
		CString FileName="Output\\data\\"+dbName+"\\"+tbName+end; //���ϳ�Ϊ�������ļ���
		//������򿪱������ļ�׷�����±������
		try
			{
			file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			file.SeekToEnd();
			//���±����д�� ע��*sizeof(TCHAR)����д�벻����
			CString toE(" ");
			CString TableName = field_value + toE;
			file.Write((unsigned char *)(TableName.GetBuffer(0)), TableName.GetLength()*sizeof(TCHAR));
			file.Flush();
			file.Close();
			log.InLog("Add Field "+field_id+" From Table "+tbName+",Database "+dbName);
			//MessageBox(_T("д��ɹ���"));

			myGlobal.state="д��ɹ���";
	        myGlobal.if_reflesh=1;

			}catch (CFileException *e)
			{
			CString str;
			str.Format(_T("д��ʧ�ܵ�ԭ����:%d"), e->m_cause);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
