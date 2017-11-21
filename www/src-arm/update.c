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
	fprintf(cgiOut,"<html><head><title>update</title></head>");
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

	char *ch,i,j=0,sql[100];
	int nrow,ncolumn,index;
	printhead();
	cgiFormString("sno",sno,sizeof(sno));

	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi',1000);</script>\n");
	}
	sprintf(sql,"select * from student where sno=%ld;",atol(sno));
	//fprintf(cgiOut,"sql %s<br>",sql);
	fprintf(cgiOut,"<form ACTION=\"./sloveUpdate.cgi\" method=\"GET\">");
	ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		fprintf(cgiOut,"sno:<INPUT TYPE=\"text\" NAME=\"sno\" SIZE=\"10\" value =\"%s\" readonly><BR>",dbresult[index++]);
		if (strcmp(dbresult[index++],"M"))
		{
			fprintf(cgiOut,"sex:<select name=\"sex\"><option value = \"F\">F</option><option value = \"M\">M</option></select><br>");
		} else{
			fprintf(cgiOut,"sex:<select name=\"sex\"><option value = \"M\">M</option><option value = \"F\">F</option></select><br>");
		}
		fprintf(cgiOut,"name:<INPUT TYPE=\"text\" NAME=\"name\" SIZE=\"10\" value =\"%s\" ><BR>",dbresult[index++]);
		fprintf(cgiOut,"age:<INPUT TYPE=\"text\" NAME=\"age\" SIZE=\"10\" value =\"%s\" ><BR>",dbresult[index++]);
		fprintf(cgiOut,"class:<INPUT TYPE=\"text\" NAME=\"classes\" SIZE=\"10\" value =\"%s\" ><BR>",dbresult[index++]);
		fprintf(cgiOut,"major:<INPUT TYPE=\"text\" NAME=\"major\" SIZE=\"10\" value =\"%s\" ><BR>",dbresult[index++]);
		fprintf(cgiOut,"<INPUT TYPE=\"SUBMIT\" values=\"Update\">");
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

