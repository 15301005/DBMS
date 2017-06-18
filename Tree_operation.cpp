#include "stdafx.h"
#include "Tree_operation.h"
#include <CString>
#include <direct.h>
#include <io.h>
#include "shlwapi.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>  
#include <vector>  
#include "MyGloble.h"

using namespace std;
//��Ruanko.db�ļ��ж�ȡ���ݿ�
CString* Tree_operation::get_database_from_db(){
	CFile file;
	CString szTemp;//�����������
	CString *database_name=new CString[24];//��ű���
	BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
	CString toE(" "); //�Կո�ָ�

	database_num=0;
	//��db�ļ��������
		if (PathFileExists("Output//Ruanko.db")){
		file.Open(_T("Output//Ruanko.db"), CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���

		/*��ʼ���г��ַ����ָ��Լ�����*/
		int nPos = szTemp.Find(strGap);
		CString strLeft = _T(" ");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			{
			   database_name[i]=strLeft;
			   database_num++;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap); 
			if (!szTemp.IsEmpty()) {
				database_name[i+1]=strLeft;
				//database_num++;
			}
			i++;
			}
		//database_name[i] = database_name[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
			
			file.Close();
		
		


   /* CStdioFile file;
	CString* database_name;
    BOOL ret = file.Open("Output//Ruanko.db",CFile::modeRead | CFile::shareDenyNone);
    if (!ret)
    {
       AfxMessageBox("���ļ�ʧ��");
    }else{
    file.SeekToBegin();
    CString cstrLine;
	int length=0,i=0;
    while (file.ReadString(cstrLine))
    {
       length++;
    }
    database_name=new CString[length];
	file.SeekToBegin();
	while (file.ReadString(cstrLine))
    {
		char *h=(LPSTR)(LPCTSTR)cstrLine;
		char *p=strtok(h," ");
		database_name[i]=p[0];
		i++;
    }
    file.Close();
	}
	*/
	return database_name;
}


//��һ�����ݿ�.tb�ļ��ж�ȡ�����Ϣ
CString* Tree_operation::get_table_from_tb(CString database_name){
	CFile file;
	CString szTemp;//�����������
	CString *table_name=new CString[24];//��ű���
	BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
	CString toE(" "); //�Կո�ָ�

	table_num=0;
	field_num=0;
	//��db�ļ��������
	if (PathFileExists("Output//data//"+myGlobal.db_name+"//"+myGlobal.db_name+".tb")){
		file.Open(_T("Output//data//"+myGlobal.db_name+"//"+myGlobal.db_name+".tb"), CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���

		/*��ʼ���г��ַ����ָ��Լ�����*/
		int nPos = szTemp.Find(strGap);
		CString strLeft = _T(" ");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			{
			   table_name[i]=strLeft;
			   table_num++;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap); 
			if (!szTemp.IsEmpty()) {
				table_name[i+1]=strLeft;
				//database_num++;
			}
			i++;
			}
		//database_name[i] = database_name[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
			
			file.Close();

			return table_name;
}


//��tdf�ļ��ж�ȡ�ֶ���Ϣ
CString* Tree_operation::get_fieldfrom_tdf(CString database_name,CString table_name){
	    CString* field_name=new CString[24];
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		//CString field[24];//����ֶ���Ϣ
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE("#");               //�Կո�ָ�
		file.Open("Output//data//"+database_name+"//"+table_name+".trd", CFile::modeRead);//�Զ��ķ�ʽ���ļ�
		int i = 0;                             //��ʼ���������־
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//��ʼ���ָ���*/
		field_num=0;
		/*��ʼ���г��ַ����ָ��Լ�����*/
	
		int nPos = szTemp.Find(strGap);
		int nn=0;
		CString strLeft = _T(" ");
		CString str=_T("");
		int j=0;
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			{
			   szA[i]=strLeft;
			   field_num++;
			}

	
			nn=szA[i].Find(toE);
			str = szA[i].Left(nn); 
			if (!str.IsEmpty())
			{
			   field_name[j]=str;
			   j++;
			}
			

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}
			i++;
		}
		file.Close();

		return field_name;
}