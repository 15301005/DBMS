#pragma once
#include "MyGloble.h"
#include "afxwin.h"
#include "log.h"

// Modify_Field �Ի���

class Modify_Field : public CDialogEx
{
	DECLARE_DYNAMIC(Modify_Field)

public:
	Modify_Field(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Modify_Field();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODIFY_FIELD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Log log;
	void set_text();
	afx_msg void OnBnClickedOk();
};
