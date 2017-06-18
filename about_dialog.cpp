// about_dialog.cpp : 实现文件
//

#include "stdafx.h"
#include "KbDbms.h"
#include "about_dialog.h"
#include "afxdialogex.h"


// about_dialog 对话框

IMPLEMENT_DYNAMIC(about_dialog, CDialogEx)

about_dialog::about_dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(about_dialog::IDD, pParent)
{

}

about_dialog::~about_dialog()
{
}

void about_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(about_dialog, CDialogEx)
END_MESSAGE_MAP()


// about_dialog 消息处理程序
