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
	fprintf(cgiOut,"<html><head><title>View Score</title></head>");
	fprintf(cgiOut,"<body>");

}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}


int cgiMain()
{
	int ret,t_ret;
	sqlite3 *db = NULL;
	char **dbresult,*errmsg,username[15],name[15],sql[100];
	int i,j,nrow,ncolumn,index;

	printhead();
	cgiFormString("sno",username,sizeof(username));
	cgiFormString("name",name,sizeof(name));
	
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}

	fprintf(cgiOut,"<header><h1>%s,view your scores</h1><a href=\"exit.cgi\">logout</a>|<a href=\"mainpageStu.cgi?sno=%ld\">mainpage</a> </header><br>",name,atol(username));
	fprintf(cgiOut,"<br>");
	
	
	//UI
	sprintf(sql,"select cno,scores from score where sno = %ld",atol(username));
	fprintf(cgiOut,"<artile><header><h2>Student Information</header>");
	sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	index = ncolumn;
	for (i = 0;i <nrow;i++){
		fprintf(cgiOut,"<p>cno_%d:",i);
		for (j = 0;j < ncolumn - 1;j++){
			fprintf(cgiOut,"%s:%s</p><br>",dbresult[index],dbresult[index + 1]);
			index += 2;
		}
	}
		sqlite3_close(db);

	printfoot();
	return 0;
}
