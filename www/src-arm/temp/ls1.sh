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
  if [[ ${filelist[$b]} != "ls.sh" && ${filelist[$b]} != "ls1.sh" && ! -d ${filelist[$b]} ]]
  then
  	arm-linux-gcc ${filelist[$b]} -o "../../cgi-bin-arm/"`echo ${filelist[$b]}`"cgi" -L/opt/FriendlyARM/root/lib -lsqlite3 -lpthread -ldl -lcgic 

  fi
  b=`expr $b + 1`
done
mv ./*.o ./temp/
rename 's//.ocgi//.cgi' ../../cgi-bin-arm/*.ocgi
