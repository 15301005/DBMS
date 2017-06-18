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
		CString message; 
		message="";
		dbFileName = tb + m_externTB1;
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
			   szA[i] = szA[i] + " ";    //���ϻ��з�����������ٴδ���db�ļ�
			   i++;
			}
			k++;
		}
		file.Close();

			file.Open(dbPath+dbFileName,  CFile:: modeCreate|CFile::modeWrite );//�����ݿ������ļ�����д��
			for (int j = 0; j < i;j++){
				file.SeekToEnd();
				//������д�� ע��*sizeof(TCHAR)����д�벻����
				file.Write((unsigned char *)(szA[j].GetBuffer(0)), szA[i].GetLength()*sizeof(TCHAR));
				file.Flush();	
			}
			file.Close();
			for(int o=0;o<length;o++)
				
			log.InLog("Drop Field "+message+" From Table "+tb+",Database "+db);
		  
		i = 0;     //���ñ��¼��Ŀ
		}
		else{
			myGlobal.state="ɾ��ʧ��;�����޴����ݿ���ڣ�";
	       myGlobal.if_reflesh=1;
			//MessageBox(_T("�����޴����ݿ���ڣ�"));
			return 0;
		}
	}

	myGlobal.state="�����ɹ���";
	myGlobal.if_reflesh=1;
	return 1;
}