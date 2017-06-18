#include "stdafx.h"
#include "DropField.h"
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
#include "log.h"
using namespace std;

int Drop_Field_class::drop_field(int field_id[],int length){
	CString db;
	CString tb;
	db=myGlobal.db_name;
	tb=myGlobal.tableName;
	int j=0,k=0;
	//database.GetWindowTextW(db);       //获取数据库名
	//tableName.GetWindowTextW(tb);       //获取表名
	if (db != "" && tb != "")//当前目录和文件类型不为空
	{
		CString str, dbFileName;
		//构造类似"C:\\My Documents\\*.txt"的类型
		CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string;
		CString m_externDB(".tb");        //后缀
		CString m_externTB1(".trd");      //后缀
		CString m_externTB2(".tid");      //后缀
		CString message; 
		message="";
		dbFileName = tb + m_externTB1;
		//查找表并删除记录
		//若db文件存在则打开
		CString dbPath=forder + db+"\\";
		if (PathFileExists(dbPath+dbFileName)){
	    CFile file;
		CString szTemp;//存放所有数据
		CString szA[24];//存放表名
		BOOLEAN ifFind=0;//标记是否找到相应表表名
		CString toE(" ");               //以空格分隔
		file.Open(dbPath+dbFileName, CFile::modeRead);//以读的方式打开文件
		int i = 0;                             //初始化表个数标志
		file.Read(szTemp.GetBufferSetLength(file.GetLength()), file.GetLength());
		CString strGap = _T(" ");//初始化分隔符

		/*开始进行长字符串分割以及载入*/
		int nPos = szTemp.Find(strGap);
		CString strLeft = _T("");
		while (0 <= nPos){
			strLeft = szTemp.Left(nPos); 
			if (!strLeft.IsEmpty())
			{
				if(k==field_id[j])
					message=message+strLeft+" ";
			     else
			        szA[i]=strLeft;
			}

			szTemp = szTemp.Right(szTemp.GetLength() - nPos - 1);
			nPos = szTemp.Find(strGap);
			if (!szTemp.IsEmpty()) {
				szA[i+1]=szTemp;
			}

			if(k==field_id[j]){
				j++;
			}
			else{
			   szA[i] = szA[i] + " ";    //加上换行符，方便后续再次存入db文件
			   i++;
			}
			k++;
		}
		file.Close();

			file.Open(dbPath+dbFileName,  CFile:: modeCreate|CFile::modeWrite );//打开数据库描述文件重新写入
			for (int j = 0; j < i;j++){
				file.SeekToEnd();
				//将表名写入 注意*sizeof(TCHAR)否则写入不完整
				file.Write((unsigned char *)(szA[j].GetBuffer(0)), szA[i].GetLength()*sizeof(TCHAR));
				file.Flush();	
			}
			file.Close();
			for(int o=0;o<length;o++)
				
			log.InLog("Drop Field "+message+" From Table "+tb+",Database "+db);
		  
		i = 0;     //重置表记录数目
		}
		else{
			myGlobal.state="删除失败;本地无此数据库存在！";
	       myGlobal.if_reflesh=1;
			//MessageBox(_T("本地无此数据库存在！"));
			return 0;
		}
	}

	myGlobal.state="操作成功！";
	myGlobal.if_reflesh=1;
	return 1;
}