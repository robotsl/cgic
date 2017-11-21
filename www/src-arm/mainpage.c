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
	fprintf(cgiOut,"<h3>Function list!</h3>");
	fprintf(cgiOut,"<li><a href = \"addnewstudents.html\">add new</a></li>");
	fprintf(cgiOut,"<li><a href = \"#show all students\">view all students</a></li>");
	fprintf(cgiOut,"<li> <a href = \"course.cgi\">view  course</a></li>");
	fprintf(cgiOut,"<li> <a href = \"AddCourse.html\">add  course</a></li>");
	fprintf(cgiOut,"<li> <a href = \"AverageScoreByClass.cgi\">class average score</a></li>");
	fprintf(cgiOut,"<li> <a href = \"AverageScoreByCno.cgi\">course average score</a></li>");
	fprintf(cgiOut,"<li> <a href = \"#show all students\">upload score</a></li>");
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
	char **dbresult,*errmsg;
	int i,j,nrow,ncolumn,index;
	printhead();
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		fprintf(cgiOut,"Open database failed<br>");
		exit (1);
	}

	fprintf(cgiOut,"<table border=\"3\"><a name  = \"show all students\"></a><caption>information\
		 about students</caption><tr><td>sno</td><td>sex</td><td>name</td>");
	fprintf(cgiOut,"<td>age</td><td>claeese</td><td>major</td><td>operator</td></tr><b>");
	ret = sqlite3_get_table(db,"select * from student",&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK){
		index=ncolumn;
		for(i=0;i<nrow;i++){
			fprintf(cgiOut,"<tr>");
			for(j=0;j<ncolumn;j++){
				fprintf(cgiOut,"<td>%s</td>",dbresult[index]);
				index++;
			}
			fprintf(cgiOut,"<td><a  href =\"update.cgi?sno=%s\">update</a>|<a  href=\"delete.cgi?sno=%s\">delete</a>|<a  href =\"uploadScore.cgi?sno=%s\">score</a></td></tr><br>",dbresult[index-6],dbresult[index-6],dbresult[index-6]);
		}
	}
	if (ret != SQLITE_OK)
		fprintf(cgiOut,"Error");
	sqlite3_close(db);

	printfoot();
	return 0;
}
