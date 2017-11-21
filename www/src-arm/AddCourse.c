#define SERVER_NAME cgiServerName
#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sqlite3.h>  
#include <unistd.h>
#include "cgic.h"

#define DATABASE "./student.db"


void printhead(void )
{
	fprintf(cgiOut,"Content-type: text/html\n");
	fprintf(cgiOut,"\n");
	fprintf(cgiOut,"<html><head><title>CGI TEST</title></head>");
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
	char name[10],sex[2],class[15],major[20],age[5]; 
	char *str,**choice;

	char *ch,i,j,sql[100];
	int nrow,ncolumn,index,total;
	bzero(name,10);
	bzero(sex,2);
	bzero(class,15);
	bzero(major,20);
	bzero(age,5);
	
	printhead();


	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi',5000);</script>\n");
	}


	cgiFormString("name",name,sizeof(name));
	
	sprintf(sql,"insert into coursename(name) values(\'%s\');",name);
	
	ret = sqlite3_exec(db,sql,0,0,&errmsg);
	if (ret != SQLITE_OK)
	{
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}
	sqlite3_close(db);
	fprintf(cgiOut,"add success!");
	fprintf(cgiOut, "<script>window.setTimeout(\"location.href='mainpage.cgi'\",1000);</script>\n");


	printfoot();
	return 0;
}
