// create_database_dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "create_database_dialog.h"
#include "afxdialogex.h"
#include "database_operation.h"
#include <CString>
#include "MyGloble.h"
#include "log.h"


// create_database_dialog �Ի���

IMPLEMENT_DYNAMIC(create_database_dialog, CDialogEx)

create_database_dialog::create_database_dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_DATABASE_DIALOG, pParent)
{

}

create_database_dialog::~create_database_dialog()
{
}

void create_database_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(create_database_dialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_DATABASE_NAME, &create_database_dialog::OnEnChangeEditDatabaseName)
	ON_BN_CLICKED(IDOK, &create_database_dialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &create_database_dialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// create_database_dialog ��Ϣ�������


void create_database_dialog::OnEnChangeEditDatabaseName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void create_database_dialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������
	database_operation data_op;
	CString database_name;
	database_name="";

	SetDlgItemText(IDC_error,database_name);//��վ�ʾ��
	GetDlgItemText( IDC_EDIT_DATABASE_NAME,database_name);  //��ȡ���ݿ���
	if(database_name==""){
		database_name="���ݿ�������Ϊ�գ�";
		SetDlgItemText( IDC_error, database_name);
		myGlobal.state="����ʧ��;���ݿ�������Ϊ�գ�";
	    myGlobal.if_reflesh=1;
	}else{
		data_op.create_database(database_name);//�߼�����
		log.InLog("Create database "+database_name);
		CDialogEx::OnOK();
	}
}


void create_database_dialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


