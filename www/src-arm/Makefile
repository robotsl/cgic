CC=arm-linux-gcc
LIB1=-L/usr/lib -L/optFriendlyARM/root/lib -I/opt/FriendlyARM/root/include
LIB2=-lsqlite3 -lpthread -ldl
CGIC=cgic.c cgic.h

all:login.cgi
.PHONY:all

login.cgi:login.c $(CGIC)
	$(CC) -o login.cgi $(LIB1) login.c cgic.c $(LIB2)

clean:
	rm *.o *.cgi
