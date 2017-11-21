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
  	arm-linux-gcc -c -I/opt/FriendlyARM/root/include/ ${filelist[$b]}  

  fi
  b=`expr $b + 1`
done
mv ./*.o ./temp/
