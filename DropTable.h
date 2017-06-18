#pragma once
#include "afxwin.h"
#include "log.h"

// DropTable 对话框

class DropTable : public CDialogEx
{
	DECLARE_DYNAMIC(DropTable)

public:
	DropTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DropTable();

// 对话框数据
	enum { IDD = IDD_DROPTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	afx_msg void OnBnClickedOk();
	CEdit database;
	CEdit tableName;
};
