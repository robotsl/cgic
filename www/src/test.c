#define SERVER_NAME cgiServerName
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>  


void printhead(void )
{
	printf("Content-type: text/html\n");
	printf("\n");
	printf("<html><head><title>Login</title></head>");
	printf("<body>");
}

void printfoot(void)
{
	printf("</body></html>");
}


int main()
{
	
	printhead();
	printfoot();
	return 0;
}
