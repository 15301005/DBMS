// create_database_dialog.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "create_database_dialog.h"
#include "afxdialogex.h"
#include "database_operation.h"
#include <CString>
#include "MyGloble.h"
#include "log.h"


// create_database_dialog 对话框

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


// create_database_dialog 消息处理程序


void create_database_dialog::OnEnChangeEditDatabaseName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void create_database_dialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代
	database_operation data_op;
	CString database_name;
	database_name="";

	SetDlgItemText(IDC_error,database_name);//清空警示框
	GetDlgItemText( IDC_EDIT_DATABASE_NAME,database_name);  //获取数据库名
	if(database_name==""){
		database_name="数据库名不能为空！";
		SetDlgItemText( IDC_error, database_name);
		myGlobal.state="操作失败;数据库名不能为空！";
	    myGlobal.if_reflesh=1;
	}else{
		data_op.create_database(database_name);//逻辑操作
		log.InLog("Create database "+database_name);
		CDialogEx::OnOK();
	}
}


void create_database_dialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


