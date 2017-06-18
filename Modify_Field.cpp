// Modify_Field.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "Modify_Field.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "KbDbmsDlg.h"
#include "log.h"


// Modify_Field �Ի���

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


// Modify_Field ��Ϣ�������


void Modify_Field::OnBnClickedOk()
{
	CString field_name,datatype,default_value;
	int if_primary_key,if_null;
	field_name="";
	datatype="";
	default_value="";
	if_primary_key=0;
	if_null=0;
	
	GetDlgItemText( IDC_EDIT_FIELD_NAME,field_name);  //��ȡ�ֶ�id
	GetDlgItemText( IDC_COMBOX_FIELDTYPE,datatype);  //��ȡ�ֶ�id
	GetDlgItemText( IDC_EDIT_DEFAULT,default_value);  //��ȡ�ֶ�id
	CButton *pButton = (CButton*)GetDlgItem(IDC_CHECK1);
	if_primary_key=pButton->GetCheck();//��ȡ���״̬�������Ϊ����ֵ
	CButton *dButton = (CButton*)GetDlgItem(IDC_CHECK2);
	if_null=dButton->GetCheck();//��ȡ���״̬�������Ϊ����ֵ

	if(field_name==""||datatype==""){
		//AfxMessageBox(_T("�ֶ����ƻ��ֶ����Ͳ���Ϊ��!"));
		myGlobal.state="����ʧ�ܣ��ֶ����ƻ��ֶ����Ͳ���Ϊ��!";
	    myGlobal.if_reflesh=1;
	}else{
		CString primary,ii;
		primary.Format("%d",if_primary_key);
		ii.Format("%d",if_null);
		CString field_value=field_name+"#"+datatype+"#"+default_value+"#"+primary+"#"+ii;

		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //��ȡѡ�е����ݿ���
		CString tbName=myGlobal.tableName;          //��ȡѡ�е����ݿ���
		CString end(".trd");          //���Ϻ�׺
		tbName=myGlobal.tableName;
		CString FileName="Output\\data\\"+dbName+"\\"+tbName+end; //���ϳ�Ϊ�������ļ���
		//������򿪱������ļ�׷�����±������
		if (PathFileExists(FileName)){
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE(" ");               //�Կո�ָ�
		file.Open(FileName, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���

		/*��ʼ���г��ַ����ָ��Լ�����*/
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

			   szA[i] = szA[i] + " ";    //���ϻ��з�����������ٴδ���db�ļ�
			   i++;
		}
		file.Close();

		szA[myGlobal.row_index]=field_value+" ";
		CFile f;
			f.Open(FileName,  CFile:: modeCreate|CFile::modeWrite );//�����ݿ������ļ�����д��
			for (int j = 0; j <= i;j++){
				f.SeekToEnd();
				//������д�� ע��*sizeof(TCHAR)����д�벻����
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
	SetDlgItemText( IDC_EDIT_FIELD_NAME,myGlobal.field_name);  //��ȡ�ֶ�id
	SetDlgItemText( IDC_COMBOX_FIELDTYPE,myGlobal.data_type);  //��ȡ�ֶ�id
	SetDlgItemText( IDC_EDIT_DEFAULT,myGlobal.default_value);  //��ȡ�ֶ�id
	if(myGlobal.if_primary_key==1)
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if(myGlobal.if_null==1)
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
}
