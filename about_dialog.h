#pragma once


// about_dialog 对话框

class about_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(about_dialog)

public:
	about_dialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~about_dialog();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
};
