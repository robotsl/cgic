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
	fprintf(cgiOut,"<html><head><title>Reset</title></head>");
	fprintf(cgiOut,"<body>");
}

void printfoot(void)
{
	fprintf(cgiOut,"</body></html>");
}


int cgiMain()
{
	
	sqlite3 *db = NULL;
	char *errmsg = NULL,**dbresult,*errmsg1 = NULL,**dbresult1;
	int ret,t_ret;

	char username[100], passwd[100],type[15],sql[100];
	char *ch,i,j;
	int nrow,ncolumn,index,nrow1,ncolumn1,index1;

	printhead();
	
	cgiFormString("sno",username,sizeof(username));
	cgiFormString("passwd",passwd,sizeof(passwd));
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}
	sprintf(sql,"select * from student where sno = %ld;",atol(username));

	ret = sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		if (nrow != 0){
			sprintf(sql,"select * from passwdStu where sno = %ld;",atol(username));
			sqlite3_get_table(db,sql,&dbresult1,&nrow1,&ncolumn1,&errmsg1);
			if (nrow1 == 0){
				sprintf(sql,"insert into passwdStu values(\'%s\',\'%s\');",username,passwd);
				sqlite3_exec(db,sql,0,0,&errmsg);
				fprintf(cgiOut,"Reset successfully!<br>");
				fprintf(cgiOut, "<script>window.setTimeout(\"location.href='../index.html'\",1000);</script>\n");
			}else{
				sprintf(sql,"update passwdStu set passwd = \'%s\' where sno = %ld;",passwd,atol(username));
				sqlite3_exec(db,sql,0,0,&errmsg);
				fprintf(cgiOut,"Reset successfully!<br>");
				fprintf(cgiOut, "<script>window.setTimeout(\"location.href='../index.html'\",1000);</script>\n");
			}
		} else {
			fprintf(cgiOut,"student not exist!<br><script>history.back()</script><br>");
		}
	}
	sqlite3_close(db);

	printfoot();
	return 0;
}
