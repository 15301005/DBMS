#pragma once


// about_dialog �Ի���

class about_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(about_dialog)

public:
	about_dialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~about_dialog();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
};
