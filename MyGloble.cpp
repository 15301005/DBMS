#include "stdafx.h"
#include "MyGloble.h"


MyGlobal::MyGlobal()
{
	tableName = "";               //��ʼ��table��
	db_name="";
	field= "";
	window_show_type=0;
	field_name="";
	data_type="";
	default_value="";
    if_primary_key=0;
	if_null=0;
	row_index=0;
	ifUpdate=-1;
	if_reflesh=0; 
	state="";
}


MyGlobal::~MyGlobal()
{
}
MyGlobal myGlobal = MyGlobal();    //�������Ϊȫ����