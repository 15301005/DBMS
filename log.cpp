#include "stdafx.h"
#include "Log.h"


Log::Log()
{
}


Log::~Log()
{
}

void Log::InLog(CString str){
	CStdioFile file;
	BOOL write=file.Open("Output\\log.ldf",CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
	if(!write){
		AfxMessageBox("���ļ�ʧ��");
	}
	file.SeekToEnd();

	CString message,ss("\n");//typeΪ���ݿ����ͣ�Ĭ��Ϊ1
	char buf[128];
	time_t ti = time(NULL);
	struct tm gmt;
	gmtime_s(&gmt,&ti);//תΪ��������ʱ��  
    strftime(buf, 64, " %Y-%m-%d %H:%M:%S", &gmt);
	CString current_time(buf);
	message=str+current_time+ss;
	file.WriteString(message);
	file.Close();

}
