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
	fprintf(cgiOut,"<html><head><title>Solve update score</title></head>");
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
	char *errmsg = NULL,**dbresult;
	int ret,t_ret;
	char name[10],sex[2],class[15],major[20],age[5],sno[15]; 
	char *str,*pEND;
	int count = 0;

	char *ch,i,j,sql[100],cno[10][5],cno1[10][5];
	int nrow,ncolumn,index;
	printhead();
	count = getParaments(cgiQueryString);
	fprintf(cgiOut,"%s<br>%d<br>",cgiQueryString,count);
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi',1000);</script>\n");
	}

	
	cgiFormString("sno",sno,sizeof(sno));
	for (i  = 0;i < count;i++){
		sprintf(cno[i],"cno%d",i);
		cgiFormString(cno[i],cno1[i],sizeof(cno1[i]));
		sprintf(sql,"update score set scores = \'%s\' where cno = %d and sno = %ld;",cno1[i],i + 1,atol(sno));
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
		if (ret != SQLITE_OK)
		{
			ret = sqlite3_exec(db,sql,0,0,&errmsg);
		}
	}

	sqlite3_close(db);
	fprintf(cgiOut,"Update success!");
	fprintf(cgiOut, "<script>window.setTimeout(\"location.href='mainpage.cgi'\",1000);</script>\n");


	printfoot();
	return 0;
}
