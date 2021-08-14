# 集合运算

## intersect set1.txt set2.txt set3.txt
求多个文件并集，允许有重复行，会改变原有顺序

## merge set1.txt set2.txt set3.txt
union 合并多个文件的所有行，且去重复   
文件可以有重复行，会改变原有顺序  

## difference ordered_file1.txt file2.txt
求两文件差集, 允许有重复行, 不会改变原来行的顺序.  如果第一个文件有重复行，会继续保留

# 去重求唯一
## unique file.txt
一个文件的行的去重，不改变原来的顺序  
Linux下的uniq命令会改变原来的顺序  

# 寻找各科目均优秀的学生
## excellent 0.3 subject1.txt subject2.txt subject3.txt
求多个科目的优秀学生，保留原有优秀顺序。第一个参数为优秀的前百分位   
如果 ./excellent 0.3 subject1.txt subject2.txt subject3.txt      
0.3表示每个科目名次在30%以内, subject是成绩排名，第一名是为最优秀    
从每科目的第一名开始找，求各科目的交集  

# 寻找差学生，只要有一科成绩差，就会被列为差学生
## worse 0.2 subject1.txt subject2.txt subject3.txt 排名倒数20%之内的学生
