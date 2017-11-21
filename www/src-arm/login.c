/* Change this if the SERVER_NAME environment variable does not report
	the true name of your web server. */
#define SERVER_NAME cgiServerName

/* You may need to change this, particularly under Windows;
	it is a reasonable guess as to an acceptable place to
	store a saved environment in order to test that feature. 
	If that feature is not important to you, you needn't
	concern yourself with this. */

#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"  
#include "cgic.h"

#define DATABASE "./student.db"

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


int cgiMain() {
	sqlite3 *db = NULL;
	char *errmsg = NULL,**dbresult;
	int ret,t_ret;
	char *t_username = "admin";
	char *t_passwd = "lxbbugudan";
	char username[100], passwd[100],type[15],sql[100];
	char *ch,i,j;
	int nrow,ncolumn,index;
	 /* DEBUG */
	/* Load a previously saved CGI scenario if that button
		has been pressed. */
	/* Send the content type, letting the browser know this is HTML */
	cgiHeaderContentType("text/html");
	/* Top of the page */
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>cgic test</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY><H1>logining.......</H1>\n");
	/* If a submit button has already been clicked, act on the 
		submission of the form. */

	cgiFormString("username",username,sizeof(username));
	cgiFormString("passwd",passwd,sizeof(passwd));
	cgiFormString("type",type,sizeof(type));
	fprintf(cgiOut,"%s  %s  %s<br>",username,passwd,type);
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}
	if (!strcmp(type,"Admin"))
	{
		ret = sqlite3_get_table(db,"select * from passwd;",&dbresult,&nrow,&ncolumn,&errmsg);
		if(ret == SQLITE_OK){
			index=ncolumn;

		}
		if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error<br>");
		fprintf(cgiOut, "<script>window.setTimeout(\"location.href='login.html'\",1000);</script>\n");
	}
	else if (strcmp(type,"student"))
	{

		ret = sqlite3_get_table(db,"select * from passwdStu;",&dbresult,&nrow,&ncolumn,&errmsg);
		if(ret == SQLITE_OK){
			index=ncolumn;
		}
		if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	}
	if (nrow == 0 || strcmp(dbresult[index + 1],passwd) != 0)
	{
		fprintf(cgiOut,"passwd error!Back to login page");
		fprintf(cgiOut, "<script>window.setTimeout(\"location.href='login.html'\",1000);</script>\n");
	}
	if (strcmp(t_passwd,passwd) != 0)
	{
		fprintf(cgiOut,"passwd error!Back to login page");
		fprintf(cgiOut, "<script>window.setTimeout(\"location.href='login.html'\",1000);</script>\n");
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

	sqlite3_close(db);

	printfoot();
	return 0;
}
