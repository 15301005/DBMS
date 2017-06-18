#include "stdafx.h"
#include "database_operation.h"
#include <CString>
#include <direct.h>
#include <io.h>
#include "shlwapi.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include<assert.h>
#include "log.h"
#pragma comment(lib,"shlwapi.lib")
using namespace std;

int database_operation::create_database(CString database_name){
	CString str ;
	str= "Output";
    if (!PathIsDirectory(str))
    {
       ::CreateDirectory(str, NULL);
    }
    str += "\\data";
    if (!PathIsDirectory(str))
    {
       ::CreateDirectory(str, NULL);
    }
    CString a("\\");
    str +=a+database_name;
    if (!PathIsDirectory(str))
    {
       ::CreateDirectory(str, NULL);
    }
    CString tb_file(".tb");
    str+=a+database_name+tb_file;
    ofstream fout(str);
    //数据库创建失败
    if(!fout){
        return 0;
    }else{//创建成功
		fout.close();
		if_Ruanko_exist();
		try{
		    write_database_to_db(database_name);
		}catch(exception e){
			printf("数据库信息写入失败");
			return 0;
		}
    }
	str.ReleaseBuffer();
	a.ReleaseBuffer();
	tb_file.ReleaseBuffer();

    return 1;
}


void database_operation::if_Ruanko_exist(){
    CString str("Output");
	 if (!PathIsDirectory(str))
    {
       ::CreateDirectory(str, NULL);
    }
	CString db_file("Ruanko.db");
    str+=db_file;
    ofstream fout(str);
	if(fout)
	   fout.close();
	str.ReleaseBuffer();
}

int database_operation::write_database_to_db(CString database_name){
	CFile file;
	try
			{
			file.Open(_T("Output//Ruanko.db"), CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			file.SeekToEnd();
			//将新表表名写入 注意*sizeof(TCHAR)否则写入不完整
			CString toE(" ");
			CString database = database_name + toE;
			file.Write((unsigned char *)(database.GetBuffer(0)), database.GetLength()*sizeof(TCHAR));
			file.Flush();
			file.Close();
			log.InLog("Create Database "+database_name);
			//MessageBox(_T("写入成功！"));
			}catch (CFileException *e)
			{
			CString str;
			str.Format(_T("写入失败的原因是:%d"), e->m_cause);
			log.InLog("Write database "+database_name+" error");
			//MessageBox(str);
			file.Abort();
			e->Delete();
			}



	/*CStdioFile file;
	BOOL write=file.Open("Output//Ruanko.db",CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
	if(!write){
		AfxMessageBox("打开文件失败");
        return 0;
	}
	file.SeekToEnd();

	char *str=NULL;
	CString h(" "),type(" 1"),database_message,ss("\n");//type为数据库类型，默认为1
	char buf[128];
	time_t ti = time(NULL);
	struct tm gmt;
	gmtime_s(&gmt,&ti);//转为格林威治时间  
    strftime(buf, 64, " %Y-%m-%d %H:%M:%S", &gmt);
	CString current_time(buf);
	database_message=database_name+type+current_time+ss;
	file.WriteString(database_message);
	file.Close();


	h.ReleaseBuffer();
	current_time.ReleaseBuffer();
	type.ReleaseBuffer();
	database_message.ReleaseBuffer();
	free(str);
	*/
	return 1;
}