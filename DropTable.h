#pragma once
#include "afxwin.h"
#include "log.h"

// DropTable �Ի���

class DropTable : public CDialogEx
{
	DECLARE_DYNAMIC(DropTable)

public:
	DropTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DropTable();

// �Ի�������
	enum { IDD = IDD_DROPTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	afx_msg void OnBnClickedOk();
	CEdit database;
	CEdit tableName;
};
