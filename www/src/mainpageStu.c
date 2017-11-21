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
	fprintf(cgiOut,"<html><head><title>MainPage</title></head>");
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
	char **dbresult,*errmsg,username[15],sno[15],sql[100];
	int i,j,nrow,ncolumn,index;

	
	cgiFormString("sno",username,sizeof(username));
	strcpy(sno,username);
	//cgiHeaderCookieSetString("sno",sno,7200,"/","localhost");
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}
	sprintf(sql,"select * from student where sno = %ld;",atol(username));
	sqlite3_get_table(db,sql,&dbresult,&nrow,&ncolumn,&errmsg);
	index = ncolumn;
	fprintf(cgiOut,"<header><h1>%s,welcome to your mainpage</h1><a href=\"exit.cgi\">logout</a> </header><br>",dbresult[index + 2]);
	fprintf(cgiOut,"<h3>Function list!</h3>");
	fprintf(cgiOut,"<li><a href = \"SelectCourse.cgi?sno=%s\">select course</a></li>",username);
	fprintf(cgiOut,"<li><a href = \"viewScore.cgi?sno=%s&name=%s\">view score</a></li>",username,dbresult[index + 2]);
	fprintf(cgiOut,"<li><a href = \"updateStu.cgi?sno=%s\">update information</a></li>",username);
	fprintf(cgiOut,"<br>");
	
	
	//UI
	fprintf(cgiOut,"<artile><header><h2>Student Information</header>");
	fprintf(cgiOut,"<p>UserID:%s<br></p>",username);
	fprintf(cgiOut,"<p>Sex:%s<br></p>",dbresult[index + 1]);
	fprintf(cgiOut,"<p>Name:%s<br></p>",dbresult[index + 2]);
	fprintf(cgiOut,"<p>Age:%s<br></p>",dbresult[index + 3]);
	fprintf(cgiOut,"<p>Class:%s<br></p>",dbresult[index + 4]);
	fprintf(cgiOut,"<p>Major:%s<br></p>",dbresult[index + 5]);
	fprintf(cgiOut,"</article>");
	

	if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	sqlite3_close(db);

	printfoot();
	return 0;
}
