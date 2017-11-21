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
  	gcc  ${filelist[$b]} -o "../cgi-bin/"`echo ${filelist[$b]}`"gi" -lsqlite3 -lpthread -lcgic
  fi
  b=`expr $b + 1`
done
