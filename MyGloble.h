#pragma once
class MyGlobal
{
public:
	MyGlobal(void);
	~MyGlobal(void);
	CString tableName;   //需要用到的全局变量：table名
	CString db_name;
	CString field;
	CString field_name;
	CString data_type;
	CString default_value;
	int if_primary_key;
	int if_null;
	int window_show_type;
	int row_index;
	int ifUpdate;  //是否进行更新操作，更新第几行
	BOOL if_reflesh;//检查状态栏是否为更新 
	CString state;//状态栏文本
};

extern MyGlobal myGlobal;