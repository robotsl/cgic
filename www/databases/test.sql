select distinct classes from student group  by classes;
select scores from score where sno =  (select sno  from student where classes = 141);
select scores from score where sno =  (select sno  from student where classes = 142);
select scores from score where sno =  (select sno  from student where classes = 143);