#pragma once
class MyGlobal
{
public:
	MyGlobal(void);
	~MyGlobal(void);
	CString tableName;   //��Ҫ�õ���ȫ�ֱ�����table��
	CString db_name;
	CString field;
	CString field_name;
	CString data_type;
	CString default_value;
	int if_primary_key;
	int if_null;
	int window_show_type;
	int row_index;
	int ifUpdate;  //�Ƿ���и��²��������µڼ���
	BOOL if_reflesh;//���״̬���Ƿ�Ϊ���� 
	CString state;//״̬���ı�
};

extern MyGlobal myGlobal;