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
//从Ruanko.db文件中读取数据库
CString* Tree_operation::get_database_from_db(){
	CFile file;
	CString szTemp;//存放所有数据
	CString *database_name=new CString[24];//存放表名
	BOOLEAN ifFind=0;//标记是否找到相应表表名
	CString toE(" "); //以空格分隔

	database_num=0;
	//若db文件存在则打开
		if (PathFileExists("Output//Ruanko.db")){
		file.Open(_T("Output//Ruanko.db"), CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符

		/*开始进行长字符串分割以及载入*/
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
		//database_name[i] = database_name[i] + toE;    //加上换行符，方便后续再次存入db文件
		}
			
			file.Close();
		
		


   /* CStdioFile file;
	CString* database_name;
    BOOL ret = file.Open("Output//Ruanko.db",CFile::modeRead | CFile::shareDenyNone);
    if (!ret)
    {
       AfxMessageBox("打开文件失败");
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


//从一个数据库.tb文件中读取表格信息
CString* Tree_operation::get_table_from_tb(CString database_name){
	CFile file;
	CString szTemp;//存放所有数据
	CString *table_name=new CString[24];//存放表名
	BOOLEAN ifFind=0;//标记是否找到相应表表名
	CString toE(" "); //以空格分隔

	table_num=0;
	field_num=0;
	//若db文件存在则打开
	if (PathFileExists("Output//data//"+myGlobal.db_name+"//"+myGlobal.db_name+".tb")){
		file.Open(_T("Output//data//"+myGlobal.db_name+"//"+myGlobal.db_name+".tb"), CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符

		/*开始进行长字符串分割以及载入*/
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
		//database_name[i] = database_name[i] + toE;    //加上换行符，方便后续再次存入db文件
		}
			
			file.Close();

			return table_name;
}


//从tdf文件中读取字段信息
CString* Tree_operation::get_fieldfrom_tdf(CString database_name,CString table_name){
	    CString* field_name=new CString[24];
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		//CString field[24];//存放字段信息
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE("#");               //以空格分隔
		file.Open("Output//data//"+database_name+"//"+table_name+".trd", CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符*/
		field_num=0;
		/*开始进行长字符串分割以及载入*/
	
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