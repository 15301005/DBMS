#pragma once
#include "log.h"

// create_database_dialog �Ի���

class create_database_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(create_database_dialog)

public:
	create_database_dialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~create_database_dialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_DATABASE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	Log log;
	afx_msg void OnEnChangeEditDatabaseName();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
