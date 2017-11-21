#define SERVER_NAME cgiServerName
#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  
#include "cgic.h"

#define DATABASE "./databases/student.db"


void printhead(void )
{
	fprintf(cgiOut,"Content-type: text/html\n");
	fprintf(cgiOut,"\n");
	fprintf(cgiOut,"<html><head><title>Upload Score</title></head>");
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
	char name[10],sex[2],class[15],major[20],age[5],sno[15]; 
	char *str;

	char *ch,i,j=0,sql[100],*pEND;
	int nrow,ncolumn,index;

	printhead();
	cgiFormString("sno",sno,sizeof(sno));

	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi',1000);</script>\n");
	}
	sprintf(sql,"select scores,cno from score where sno=%ld;",atol(sno));
	//fprintf(cgiOut,"sql %s<br>",sql);
	fprintf(cgiOut,"<form ACTION=\"./sloveUpdateScore.cgi\" method=\"GET\">");
	ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		fprintf(cgiOut,"sno:<INPUT TYPE=\"text\" NAME=\"sno\" SIZE=\"10\" value =\"%s\" readonly><BR>",sno);
		for (i = 0;i < nrow;i++){
			for (j = 0;j < ncolumn -  1;j++){	
				fprintf(cgiOut,"cno:%s<INPUT TYPE=\"text\" NAME=\"cno%d\" SIZE=\"10\" value =\"%s\" required=\"required\"><BR>",dbresult[index++],i,dbresult[index++]);
			}
		}
		fprintf(cgiOut,"<INPUT TYPE=\"SUBMIT\" values=\"Update\"></form>");
		sqlite3_close(db);
	}
	else {
		sqlite3_close(db);
		fprintf(cgiOut,"Failed to select");	
		fprintf(cgiOut,"<script>window.setTimeOut(\"location.href='mainpage.cgi\",1000);</script>\n");
	}
	printfoot();
	return 0;
}

