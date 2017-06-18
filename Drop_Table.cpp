#include "stdafx.h"
#include "Drop_Table.h"
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

int Drop_Table_class::drop_table(){
	CString db;
	CString tb;
	db=myGlobal.db_name;
	tb=myGlobal.tableName;
	//database.GetWindowTextW(db);       //��ȡ���ݿ���
	//tableName.GetWindowTextW(tb);       //��ȡ����
	if (db != "" && tb != "")//��ǰĿ¼���ļ����Ͳ�Ϊ��
	{
		CString str, dbFileName;
		//��������"C:\\My Documents\\*.txt"������
		CString forder("D:\\HOMEWORK_PROGRAM\\KbDBMS\\KbDbms\\Output\\data\\");
		CString string;
		CString m_externDB(".tb");        //��׺
		CString m_externTB1(".trd");      //��׺
		CString m_externTB2(".tid");      //��׺
		dbFileName = db + m_externDB;
		//���ұ�ɾ����¼
		//��db�ļ��������
		CString dbPath=forder + db+"\\";
		if (PathFileExists(dbPath+dbFileName)){
	    CFile file;
		CString szTemp;//�����������
		CString szA[24];//��ű���
		BOOLEAN ifFind=0;//����Ƿ��ҵ���Ӧ�����
		CString toE(" ");               //�Կո�ָ�
		file.Open(dbPath+dbFileName, CFile::modeRead);//�Զ��ķ�ʽ���ļ�
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

			/*���ڹ������ҵ�ƥ�������˱���ڣ�ɾ����Ӧ��������ļ��Լ������ļ�*/
			if (szA[i] == tb) {
				ifFind = 1;
				i--;
				string = dbPath + tb + m_externTB1;
				if (PathFileExists(string))//���������ļ�
				{
					DeleteFile(string);
				}
				string = dbPath + tb + m_externTB2;
				if (PathFileExists(string))//���������ļ�
				{
					DeleteFile(string);
				}
			}
			
			szA[i] = szA[i] + " ";    //���ϻ��з�����������ٴδ���db�ļ�
			i++;
		}
		file.Close();

		//���Ϊ0��ʾδ�����ݿ����ҵ��˱�
		if (!ifFind) { 
			//MessageBox(_T("�����ݿ��޴˱���ڣ�")); 
			return 0;
		}

		/*�ҵ����ɹ�ɾ�����ʣ��ı��ٴ�д��db�ļ�*/
		else{
			log.InLog("Drop Table "+tb+" in Database "+db);
			file.Open(dbPath+dbFileName, CFile::modeCreate | CFile::modeWrite );//�����ݿ������ļ�����д��
			for (int j = 0; j < i;j++){
				file.SeekToEnd();
				//������д�� ע��*sizeof(TCHAR)����д�벻����
				file.Write((unsigned char *)(szA[j].GetBuffer(0)), szA[i].GetLength()*sizeof(TCHAR));
				file.Flush();	
			}
			file.Close();
		  }
		i = 0;     //���ñ��¼��Ŀ
		}
		else{
			//MessageBox(_T("�����޴����ݿ���ڣ�"));
			return 0;
		}
	}
	return 1;
}