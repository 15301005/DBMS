#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CString>
#include <string>
#include "resource.h"

class Tree_operation{
public:
   CString* get_database_from_db();//��Ruanko.db�ļ��ж�ȡ���ݿ�
   CString* get_table_from_tb(CString database_name);//��һ�����ݿ�.tb�ļ��ж�ȡ�����Ϣ
   CString* get_fieldfrom_tdf(CString database_name,CString table_name);//��tdf�ļ��ж�ȡ�ֶ���Ϣ
   int database_num;
   int table_num;
   int field_num;
};