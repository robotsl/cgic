#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  
#include "cgic.h"
#define DATABASE "./student.db"
#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"

void printhead(void )
{
	fprintf(cgiOut,"Content-type: text/html\n");
	fprintf(cgiOut,"\n");
	fprintf(cgiOut,"<html><head><title>MainPage</title></head>");
	fprintf(cgiOut,"<body>");
	fprintf(cgiOut,"<header><h1>Select your course</h1></header><br>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}

int cgiMain()
{
	int ret,ret1,t_ret,flag = 0;
	sqlite3 *db = NULL;
	char **dbresult,*errmsg,**dbresult1,*errmsg1,sno[15],sql[100],sql1[100];
	int i,j,k,l,nrow,ncolumn,index,nrow1,ncolumn1,index1;

	cgiFormString("sno",sno,sizeof(sno));
	printhead();
	fprintf(cgiOut,"<a href=\"mainpageStu.cgi?sno=%s \">mainpage</a>",sno);
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}
	fprintf(cgiOut,"<table border=\"3\"><caption>Selected course</caption><tr><td>cno</td><td>CourseName</td></tr><br>");
	
	sprintf(sql,"select cno from course where sno = \'%s\' order by cno;",sno);
	ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		for(i=0;i<nrow;i++){
			fprintf(cgiOut,"<tr><td>%s</td>",dbresult[index++]);
			sprintf(sql1,"select name from coursename where cno = \'%s\';",dbresult[index - 1]);
			ret1 = sqlite3_get_table(db,sql1,&dbresult1,&nrow1,&ncolumn1,&errmsg1);
			fprintf(cgiOut,"<td>%s</td>",dbresult1[ncolumn]);
		}
	}
	fprintf(cgiOut,"</tr></table>");
	
	
	fprintf(cgiOut,"<table border=\"3\"><a name  = \"show all students\"></a><caption>Not Selected</caption><tr><td>cno</td><td>CourseName</td><td>Select</td></tr><br>");
	fprintf(cgiOut,"<form action=\"sloveSelectCourse.cgi\" method=\"get\">");
	fprintf(cgiOut,"<td><label><input name=\"sno\" type=\"text\" value=\"%s\" hidden/></label></td><br>",sno);
	sprintf(sql,"select cno from coursename where cno not in (select cno from course where sno = \'%s\' order by cno);",sno);
	ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		for(i=0;i<nrow;i++){
			fprintf(cgiOut,"<tr><td>%s</td>",dbresult[index++]);
			sprintf(sql1,"select name from coursename where cno = \'%s\';",dbresult[index - 1]);
			ret1 = sqlite3_get_table(db,sql1,&dbresult1,&nrow1,&ncolumn1,&errmsg1);
			fprintf(cgiOut,"<td>%s</td>",dbresult1[ncolumn]);
			fprintf(cgiOut,"<td><label><input name=\"Course%d\" type=\"checkbox\" value=\"%s\" /> %s </label></td></tr><br>",i,dbresult[index - 1],dbresult[index - 1]);
		}
	}
	
	fprintf(cgiOut,"<tr><td><label><input type=\"submit\" value =\"submit\" ></label></form></td>");
	fprintf(cgiOut,"</tr></table>");
	
	if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	sqlite3_close(db);
	
	printfoot();
	return 0;
}
