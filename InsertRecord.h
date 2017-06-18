#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "log.h"

// CInsertRecord 对话框

class CInsertRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertRecord)

public:
	CInsertRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInsertRecord();

// 对话框数据
	enum { IDD = IDD_INSERTRECORD };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	void OnUpdate();  //做更新操作
	void readRecord();
	void writeToFile(); //将更新后的数据重新写入
	CString newRecord;
	int ifUpdate;  //是否是更新操作，更新的是哪一行数据
	int recordNum;  //记录数目
	CString* record;  //读入一条记录
	CString* recordRow;  //读入column数据段
	CString* recordColumn;//字段名
	CString* recordDataType;//字段类型
	int num; //记录读入的column数据段的数目
	CListCtrl recordList;
	Log log;
};
