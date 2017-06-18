// DropTable.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KbDbms.h"
#include "DropTable.h"
#include "afxdialogex.h"
#include "MyGloble.h"
#include "string.h" 
#include "log.h"


// DropTable �Ի���

IMPLEMENT_DYNAMIC(DropTable, CDialogEx)

DropTable::DropTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(DropTable::IDD, pParent)
{

}

DropTable::~DropTable()
{
}

void DropTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, database);
	DDX_Control(pDX, IDC_EDIT2, tableName);
}


BEGIN_MESSAGE_MAP(DropTable, CDialogEx)
	ON_BN_CLICKED(IDOK, &DropTable::OnBnClickedOk)
END_MESSAGE_MAP()


// DropTable ��Ϣ�������


void DropTable::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString db;
	CString tb;
	database.GetWindowTextA(db);
	tableName.GetWindowTextA(tb);
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
			i++;
			szA[i] = szA[i] + toE;    //���ϻ��з�����������ٴδ���db�ļ�
		}
		file.Close();

		//���Ϊ0��ʾδ�����ݿ����ҵ��˱�
		if (!ifFind) { 
			//MessageBox(_T("�����ݿ��޴˱���ڣ�")); 
			myGlobal.state="����ʧ��;�����ݿ��޴˱���ڡ�";
	        myGlobal.if_reflesh=1;
		}

		/*�ҵ����ɹ�ɾ�����ʣ��ı��ٴ�д��db�ļ�*/
		else{
			file.Open(dbPath+dbFileName, CFile::modeCreate | CFile::modeWrite );//�����ݿ������ļ�����д��
			for (int j = 0; j < i ;j++){
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
			myGlobal.state="����ʧ��;�����޴����ݿ���ڣ�";
	        myGlobal.if_reflesh=1;
			//MessageBox(_T("�����޴����ݿ���ڣ�"));
		}
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	myGlobal.state="�����ɹ���";
	myGlobal.if_reflesh=1;

	CDialogEx::OnOK();
}
