#pragma once
#include "afxwin.h"
#include "log.h"

// Add_field_dialog 对话框

class Add_field_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Add_field_dialog)

public:
	Add_field_dialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Add_field_dialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_Add_Field };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	int ADD_FIELD_DIALOG;
	afx_msg void OnBnClickedOk();
	CButton if_primary_key;
	CButton if_null;
	CComboBox get_field_type;
	afx_msg void OnCbnSelchangeComboxFieldtype();
};
