#!/bin/bash
c=0
for file in `ls`
do
  filelist[$c]=$file
  c=`expr $c + 1`
done

b=0
while [ $b -lt $c ]
do
  #echo ${filelist[$b]}     
  #gcc `echo ${filelist[$b]}` -o ../cgi-bin/`echo $(${filelist[$b]})`"gi" -lsqlite3 -lpthread -lcgic
  if [[ ${filelist[$b]} != "ls.sh" && ${filelist[$b]} != "ls1.sh" ]]
  then
  	arm-linux-gcc  -c -I/opt/FriendlyARM/root/include ${filelist[$b]} -o "../cgi-bin-arm/"`echo ${filelist[$b]}`"gi" -ldl -lsqlite3 -lpthread -L/opt/FriendlyARM/root/lib
  fi
  b=`expr $b + 1`
done
