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
	fprintf(cgiOut,"<html><head><title>Login</title></head>");
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

	char username[100], passwd[100],type[15],sql[100];
	char *ch,i,j;
	int nrow,ncolumn,index;

	
	
	cgiFormString("username",username,sizeof(username));
	cgiFormString("passwd",passwd,sizeof(passwd));
	cgiFormString("type",type,sizeof(type));
	fprintf(cgiOut,"%s  %s  %s<br>",username,passwd,"Admin");
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}
	if (!strcmp(type,"Admin"))
	{
		sprintf(sql,"select * from passwd where username =\'%s\';",username);
		ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
		if(ret == SQLITE_OK){
			index=ncolumn;

		}
		if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	}
	else if (strcmp(type,"student"))
	{
		sprintf(sql,"select * from passwdStu where sno =\'%s\';",username);
		ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
		if(ret == SQLITE_OK){
			index=ncolumn;
		}
		if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	}
	if (nrow == 0 || strcmp(dbresult[index + 1],passwd) != 0)
	{
		fprintf(cgiOut,"%s %s %stest  passwd error!Back to login page",dbresult[index],dbresult[index + 1],passwd);
		fprintf(cgiOut, "<script>window.setTimeout(\"location.href='../index.html'\",1000);</script>\n");
	}
	
	else {
	    if (!strcmp(type,"Admin")){
	        //TODO:Add cookies
    		fprintf(cgiOut, "<script>window.location.href='mainpage.cgi';</script>\n");
    	}
    	if (strcmp(type,"Admin")){
    	    //TODO:Add cookies
    		fprintf(cgiOut, "<script>window.location.href='mainpageStu.cgi?sno=%s';</script>\n",username);
    	}
	}
	sqlite3_close(db);

	printfoot();
	return 0;
}
