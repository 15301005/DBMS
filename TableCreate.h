#pragma once
#include "afxwin.h"
#include "log.h"

// TableCreate �Ի���

class TableCreate : public CDialogEx
{
	DECLARE_DYNAMIC(TableCreate)

public:
	TableCreate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TableCreate();

// �Ի�������
	enum { IDD = IDD_NEWTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	afx_msg void OnBnClickedOk();
	CEdit edit;
};
