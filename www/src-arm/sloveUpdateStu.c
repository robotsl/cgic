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
	fprintf(cgiOut,"<html><head><title>solve update stu</title></head>");
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

	char *ch,i,j,sql[100];
	int nrow,ncolumn,index;
	printhead();

	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		fprintf(cgiOut, "<script>window.setTimeOut(location.href='mainpage.cgi?sno=%s',1000);</script>\n",sno);
	}

	
	cgiFormString("sno",sno,sizeof(sno));
	cgiFormString("name",name,sizeof(name));
	cgiFormString("sex",sex,sizeof(sex));
	cgiFormString("age",age,sizeof(age));
	cgiFormString("classes",class,sizeof(class));
	cgiFormString("major",major,sizeof(major));
	sprintf(sql,"update student set sex = \'%s\',name=\'%s\',age=%d,classes=\'%s\',major=\'%s\' where sno = %ld;",sex,name,atoi(age),class,major,atol(sno));
	
	ret = sqlite3_exec(db,sql,0,0,&errmsg);
	if (ret != SQLITE_OK)
	{
		ret = sqlite3_exec(db,sql,0,0,&errmsg);
	}
	sqlite3_close(db);
	fprintf(cgiOut,"Update success!");
	fprintf(cgiOut, "<script>window.setTimeout(\"location.href='mainpageStu.cgi?sno=%s'\",1000);</script>\n",sno);


	printfoot();
	return 0;
}
