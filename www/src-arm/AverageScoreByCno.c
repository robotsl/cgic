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
	fprintf(cgiOut,"<header><h1>Class average score</h1><a href=\"exit.cgi\">logout</a>|<a href=\"mainpage.cgi\">mainpage</a> </header><br>");
	fprintf(cgiOut,"<br>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}


int cgiMain()
{
	int ret,t_ret;
	sqlite3 *db = NULL;
	char **dbresult,*errmsg,**dbresult1,*errmsg1,sql[100],*pEND;
	int i,j,k,l,nrow,ncolumn,index,index1,nrow1,ncolumn1;
	float score   = 0.0;
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}

	fprintf(cgiOut,"<table border=\"3\"><a name  = \"show all students\">\
	    </a><caption>information about students</caption><tr><td>class</td><td>average</td></tr><br>");
	ret = sqlite3_get_table(db,"select distinct cno from course group  by cno",&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		for(i=0;i<nrow;i++){
			fprintf(cgiOut,"<tr>");
			fprintf(cgiOut,"<td>%s</td>",dbresult[index]);
			for(j=0;j<ncolumn;j++){
				sprintf(sql,"select scores from score where cno = %d;",atoi(dbresult[index]));
				sqlite3_get_table(db,sql,&dbresult1,&nrow1,&ncolumn1,&errmsg1);
				index1=ncolumn1;
				for (k=0;k<nrow1;k++){
				    for(l=0;l<ncolumn1;l++){
				        score  += strtof(dbresult1[index1++],&pEND);
				    }
				}
				score /= (ncolumn1 + 1.0);
				fprintf(cgiOut,"<td>%.2lf</td>",score);
				score  = 0.0;       
			}
			index++;
		}
	}
	if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	sqlite3_close(db);

	printfoot();
	return 0;
}
