#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CString>
#include <string>
#include "resource.h"

class Tree_operation{
public:
   CString* get_database_from_db();//从Ruanko.db文件中读取数据库
   CString* get_table_from_tb(CString database_name);//从一个数据库.tb文件中读取表格信息
   CString* get_fieldfrom_tdf(CString database_name,CString table_name);//从tdf文件中读取字段信息
   int database_num;
   int table_num;
   int field_num;
};