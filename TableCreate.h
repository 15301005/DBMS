#pragma once
#include "afxwin.h"
#include "log.h"

// TableCreate 对话框

class TableCreate : public CDialogEx
{
	DECLARE_DYNAMIC(TableCreate)

public:
	TableCreate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableCreate();

// 对话框数据
	enum { IDD = IDD_NEWTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	afx_msg void OnBnClickedOk();
	CEdit edit;
};
