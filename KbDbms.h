
// KbDbms.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKbDbmsApp: 
// �йش����ʵ�֣������ KbDbms.cpp
//

class CKbDbmsApp : public CWinApp
{
public:
	CKbDbmsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKbDbmsApp theApp;