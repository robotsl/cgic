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
	fprintf(cgiOut,"<header><h1>Welcome mainpage</h1><a href=\"exit.cgi\">logout</a> </header><br>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}


int cgiMain()
{
	int ret,t_ret;
	sqlite3 *db = NULL;
	char **dbresult,*errmsg;
	int i,j,nrow,ncolumn,index;
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}

	fprintf(cgiOut,"<table border=\"3\"><a name  = \"show all course\"></a><caption>information about\
	 students</caption><tr><td>course number</td><td>course name</td><td>Operate Course</td>");

	ret = sqlite3_get_table(db,"select * from coursename",&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		for(i=0;i<nrow;i++){
			printf("<tr>");
			for(j=0;j<ncolumn;j++){
				fprintf(cgiOut,"<td>%s</td>",dbresult[index]);
				index++;
			}
			fprintf(cgiOut,"<td><a  href =\"deleteCourse.cgi?cno=%s\">delete</a></td></tr><br>",dbresult[index - 2]);
		}
	}
	if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	sqlite3_close(db);

	printfoot();
	return 0;
}
