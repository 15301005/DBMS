
// KbDbmsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Tree_operation.h"
#include "about_dialog.h"
#include "log.h"
#include "Drop_Table.h"
#include "DropField.h"
#include "Modify_Field.h"
#include "InsertRecord.h"


// CKbDbmsDlg 对话框
class CKbDbmsDlg : public CDialogEx
{
// 构造
public:
	CKbDbmsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KBDBMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CStatusBarCtrl *m_StatBar;
	CToolBar m_ToolBar;
	//void OnTvnSelchangedWebTree(); //NMHDR*pNMHDR, LRESULT *pResult 
public:
	afx_msg void OnDatabaseCreatedatabase();
	CTreeCtrl m_web_tree;
	Tree_operation tree_operation;
	Drop_Table_class drop_table;
	Drop_Field_class drop_field;
	Modify_Field modify_field;
	Log log;
	int type;
	MyGlobal return_myGlobal();
	afx_msg void OnHelpAboutdbms();
	afx_msg void OnTableCreatetable();
	CListCtrl m_tableList;
	afx_msg void OnTableDroptable();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFieldAddfield();
	afx_msg void OnDatabaseOpendatabase();
	afx_msg void OnDatabaseShowdatabase();
	afx_msg void OnSystemExit();
	afx_msg void OnFieldDropfield();
	afx_msg void OnTableAltertable();
	afx_msg void OnTableShowtabledata();
	afx_msg void OnFieldModifyfield();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRecordInsertrecord();
	afx_msg void OnRecordSelectrecord();
	afx_msg void OnRecordUpdaterecord();
	afx_msg void OnRecordDeleterecord();
	void selectRecord();
	void readTableConlumn();
	void writeRecordToFile();
	CString*recordColumn;
	int ConNum;//字段数目
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
