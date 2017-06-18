// TableCreate.cpp : ʵ���ļ�
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



// TableCreate �Ի���

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


// TableCreate ��Ϣ�������


void TableCreate::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	edit.UpdateData(FALSE);                  //����edit�ؼ�����
	edit.GetWindowTextA(myGlobal.tableName); //��ȡedit�ؼ��ı�
	if (myGlobal.tableName != ""){
		CFile file;
		//char ss[20]="data.txt";
		CString dbName=myGlobal.db_name;          //��ȡѡ�е����ݿ���
		CString end(".tb");          //���Ϻ�׺
		CString FileName="Output\\data\\"+dbName+"\\"+dbName+end; //���ϳ�Ϊ�������ļ���
		//������򿪱������ļ�׷�����±������
		try
		{
			file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			file.SeekToEnd();
			//���±����д�� ע��*sizeof(TCHAR)����д�벻����
			CString toE(" ");
			CString TableName = myGlobal.tableName + toE;
			file.Write((unsigned char *)(TableName.GetBuffer(0)), TableName.GetLength()*sizeof(TCHAR));
			file.Flush();
			file.Close();
			//MessageBox(_T("д��ɹ���"));
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


		CString str ;
		str= "Output\\data\\"+dbName+"\\"+myGlobal.tableName+".trd";
        ofstream fout(str);
        //���ݿⴴ��ʧ��
        if(!fout){
            myGlobal.state="����ʧ�ܣ�";
	        myGlobal.if_reflesh=1;
        }else{//�����ɹ�
		   fout.close();
		   log.InLog("Create Table "+myGlobal.tableName+" in Database "+myGlobal.db_name);

		   myGlobal.state="�����ɹ�!";
	       myGlobal.if_reflesh=1;

		}
	}
			//DeleteFile((LPCTSTR)"D:\VS2013\KbDBMS\KbDbms\data.tb");
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}