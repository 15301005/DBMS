#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "log.h"

// CInsertRecord �Ի���

class CInsertRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertRecord)

public:
	CInsertRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInsertRecord();

// �Ի�������
	enum { IDD = IDD_INSERTRECORD };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL CInsertRecord::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	DWORD m_dwItem;
	int m_nSubItem;
	//CListCtrl recordList;
	CEdit m_editValue;
	afx_msg void OnBnClickedOk();
	void OnInsert();
	void OnUpdate();  //�����²���
	void readRecord();
	void writeToFile(); //�����º����������д��
	CString newRecord;
	int ifUpdate;  //�Ƿ��Ǹ��²��������µ�����һ������
	int recordNum;  //��¼��Ŀ
	CString* record;  //����һ����¼
	CString* recordRow;  //����column���ݶ�
	CString* recordColumn;//�ֶ���
	CString* recordDataType;//�ֶ�����
	int num; //��¼�����column���ݶε���Ŀ
	CListCtrl recordList;
	Log log;
};
