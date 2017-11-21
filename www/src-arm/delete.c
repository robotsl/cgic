#define SERVER_NAME cgiServerName
#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  
#include "cgic.h"

#define DATABASE "./student.db"


void printhead(void )
{
	fprintf(cgiOut,"Content-type: text/html\n");
	fprintf(cgiOut,"\n");
	fprintf(cgiOut,"<html><head><title>Delete student</title></head>");
	fprintf(cgiOut,"<body>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}


int cgiMain()
{
	
	sqlite3 *db = NULL;
	char *errmsg = NULL,**dbresult;
	int ret,t_ret;
	char sno[100]; 
	char *str;

	char *ch,i,j,sql[100];
	int nrow,ncolumn,index;
	printhead();

	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi',1000);</script>\n");
	}


	cgiFormString("sno",sno,sizeof(sno));	
	fprintf(cgiOut,"%s",sno);
	sprintf(sql,"delete from score where sno=%ld;",atol(sno));
	
	ret = sqlite3_exec(db,sql,0,0,&errmsg);
	if (ret != SQLITE_OK)
	{
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}
	sprintf(sql,"delete from course where sno=%ld;",atol(sno));
	ret = sqlite3_exec(db,sql,0,0,&errmsg);
	if (ret != SQLITE_OK)
	{
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}
	sprintf(sql,"delete from student where sno=%ld;",atol(sno));
	ret = sqlite3_exec(db,sql,0,0,&errmsg);
	if (ret != SQLITE_OK)
	{
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}
	sqlite3_close(db);
	fprintf(cgiOut, "delete success");
	fprintf(cgiOut, "<script>window.setTimeout(\"location.href='mainpage.cgi'\",1000);</script>\n");
	printfoot();
	return 0;
}
