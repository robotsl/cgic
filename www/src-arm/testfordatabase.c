#include <stdio.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  

#define DATABASE "./student.db"
int main()
{
	
	sqlite3 *db = NULL;
	char *errmsg = NULL,**dbresult;
	int ret,t_ret;

	char *ch,i,j;
	int nrow,ncolumn,index=0;
	if ((ret = sqlite3_open(DATABASE,&db)) != SQLITE_OK)
	{
		printf("Open database failed<br>");
		exit (1);
	}
	ret = sqlite3_get_table(db,"select * from passwd;",&dbresult,&nrow,&ncolumn,&errmsg);
	printf("%s",errmsg);

	printf("ret = %d nrow %d ncolumn %d\n",ret,nrow,ncolumn);
	
	for (i = 0;i < nrow;i++)
	{
		for (j = 0;j < ncolumn-1;j++)
		{
			printf("tttt %s\t",dbresult[index++]);
		}
	}
	sqlite3_close(db);

	return 0;
}
