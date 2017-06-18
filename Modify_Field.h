#pragma once
#include "MyGloble.h"
#include "afxwin.h"
#include "log.h"

// Modify_Field 对话框

class Modify_Field : public CDialogEx
{
	DECLARE_DYNAMIC(Modify_Field)

public:
	Modify_Field(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Modify_Field();

// 对话框数据
	enum { IDD = IDD_DIALOG_MODIFY_FIELD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	void set_text();
	afx_msg void OnBnClickedOk();
};
