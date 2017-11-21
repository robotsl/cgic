#define SERVER_NAME cgiServerName
#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  
#include "cgic.h"

#define DATABASE "/var/www/databases/student.db"


void printhead(void )
{
	fprintf(cgiOut,"Content-type: text/html\n");
	fprintf(cgiOut,"\n");
	fprintf(cgiOut,"<html><head><title>Slove course</title></head>");
	fprintf(cgiOut,"<body>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}

int getParaments(const char *str)
{
	int i = 0,count = 0;
	fprintf(cgiOut,"%c<br>",str[i]);
	if (str[i] == '&')
			count++;
	while (str[i++])
	{
		if (str[i] == '&')
			count++;
	}
	return count;
}
extern char *cgiQueryString;
int cgiMain()
{	
	sqlite3 *db = NULL;
	char *errmsg = NULL,**dbresult,*cookresult;
	int ret,t_ret,count;
	char sno[15],cno[15][15],cno1[15][15]; 
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
	count = getParaments(cgiQueryString);
	for (i  = 0;i < count;i++){
		sprintf(cno[i],"Course%d",i);
		cgiFormString(cno[i],cno1[i],sizeof(cno1[i]));
		sprintf(sql,"insert into course values(%s,%s);",sno,cno1[i]);
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
		sprintf(sql,"insert into score values(%s,%s,0);",sno,cno1[i]);
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}

	sqlite3_close(db);
	fprintf(cgiOut, "<script>window.setTimeout(\"location.href='mainpageStu.cgi?sno=%s'\",1000);</script>\n",sno);
	printfoot();
	return 0;
}
