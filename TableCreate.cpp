// TableCreate.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "TableCreate.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include <io.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include<assert.h>
#include "log.h"
#pragma comment(lib,"shlwapi.lib")
using namespace std;



// TableCreate 对话框

IMPLEMENT_DYNAMIC(TableCreate, CDialogEx)

TableCreate::TableCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(TableCreate::IDD, pParent)
{

}

TableCreate::~TableCreate()
{
}

void TableCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, edit);
}


BEGIN_MESSAGE_MAP(TableCreate, CDialogEx)
	ON_BN_CLICKED(IDOK, &TableCreate::OnBnClickedOk)
END_MESSAGE_MAP()


// TableCreate 消息处理程序


void TableCreate::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	edit.UpdateData(FALSE);                  //设置edit控件属性
	edit.GetWindowTextA(myGlobal.tableName); //获取edit控件文本
	if (myGlobal.tableName != ""){
		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //获取选中的数据库名
		CString end(".tb");          //加上后缀
		CString FileName="Output\\data\\"+dbName+"\\"+dbName+end; //整合成为表描述文件名
		//创建或打开表描述文件追加入新表的名字
		try
		{
			file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			file.SeekToEnd();
			//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
			CString toE(" ");
			CString TableName = myGlobal.tableName + toE;
			file.Write((unsigned char *)(TableName.GetBuffer(0)), TableName.GetLength()*sizeof(TCHAR));
			file.Flush();
			file.Close();
			//MessageBox(_T("写入成功！"));
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


		CString str ;
		str= "Output\\data\\"+dbName+"\\"+myGlobal.tableName+".trd";
        ofstream fout(str);
        //数据库创建失败
        if(!fout){
            myGlobal.state="创建失败！";
	        myGlobal.if_reflesh=1;
        }else{//创建成功
		   fout.close();
		   log.InLog("Create Table "+myGlobal.tableName+" in Database "+myGlobal.db_name);

		   myGlobal.state="创建成功!";
	       myGlobal.if_reflesh=1;

		}
	}
			//DeleteFile((LPCTSTR)"D:\VS2013\KbDBMS\KbDbms\data.tb");
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}