#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CString>
#include "resource.h"
#include "log.h"

class database_operation{
//此类中，函数操作成功返回1，失败返回0
public:
	Log log;
	int create_database(CString database_name);//创建数据库，即在output文件夹中创建对应的子文件夹并新建.tb文件，在Ruanko中写入数据库信息
	void if_Ruanko_exist();//判断Ruanko.db文件是否存在，不存在则创建
	int write_database_to_db(CString database_name);//将新数据库信息写进Ruanko.db中
};