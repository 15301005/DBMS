#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CString>
#include "resource.h"
#include "log.h"

class database_operation{
//�����У����������ɹ�����1��ʧ�ܷ���0
public:
	Log log;
	int create_database(CString database_name);//�������ݿ⣬����output�ļ����д�����Ӧ�����ļ��в��½�.tb�ļ�����Ruanko��д�����ݿ���Ϣ
	void if_Ruanko_exist();//�ж�Ruanko.db�ļ��Ƿ���ڣ��������򴴽�
	int write_database_to_db(CString database_name);//�������ݿ���Ϣд��Ruanko.db��
};