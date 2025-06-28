# sql:

1. SELECT * FROM "table name";

也可以SELECT label1,lbel2 ...

can add "LIMIT 5" only display 5 lines（limit 0,2【1到2行】）

WHERE label=“information”(**LIKE**  "%" %represent 0 or more any string,and **_** only represent one string)  only display the label satisfying those requirments. It also can  compare: label>80 **AND** label<80||BETWEEN 80 AND 90. 



(we can replace = with <>, and will get the opposite answer)

ORDER BY label(seqentially)（也可以写写数字，第几列）

We can also use it as a function:

进行display，排序，选择操作

- 联合查询：union select能帮助查询下面的执行语句，就是执行多次select

![image-20250316233600115](assets/image-20250316233600115.png)

- 

2. AVG![image-20250316205731377](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316205731377.png)

And use it with GROUP BY

![image-20250316205910768](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316205910768.png)

![image-20250316205955244](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316205955244.png)

If not following the sequence will report error

3. COUNT![image-20250316210528358](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316210528358.png)

ignore blank line and with **(DISTINCT label)**, 

4. DISTINCT![image-20250316210518653](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316210518653.png)

5. create tables

   ![image-20250316210659882](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316210659882.png)

   primary key ensure that no repetition

   DROP TABLE clubs(不要这个表格)

6. INSERT INTO table

   VALUES(....,.....)correspond to the table created

7. UPDATE （如果只是某一个数据，要制定内容）

   ![image-20250316211913203](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316211913203.png)

8. DELETE

   ![image-20250316211934978](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316211934978.png)

9. 表格连接：

   ![image-20250316212112899](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250316212112899.png)

   这里还显示了没有社团的同学，如果不想要这些的话把LEFT改成INNER、

   

10. 注释符号

    /**/或者单行--

# SQL注入

注入常用函数（Mysql）

（1）user() 返回当前使用数据库的用户，也就是网站配置文件中连接数据库的账号 （2）version() 返回当前数据库的版本 （3）database() 返回当前使用的数据库，只有在use命令选择一个数据库之后，才能查到 （4）group_concat() 把数据库中的某列数据或某几列数据合并为一个字符串 （5）@@datadir 数据库路径 （6）@@version_compile_os 操作系统版本

。

SQL注入重点关注的表：

![image-20250316231120423](assets/image-20250316231120423.png)

![image-20250316231523271](assets/image-20250316231523271.png)

利用语句查询：![image-20250316231736964](assets/image-20250316231736964.png)

![image-20250316232354469](assets/image-20250316232354469.png)

字符型注入：![image-20250316232936200](assets/image-20250316232936200.png)

但凡‘’内部找到了前面的label就不会对后者进行逻辑判断

数字型注入：

会执行运算和逻辑判断

## 联合查询注入：

- ![image-20250316233904868](assets/image-20250316233904868.png)

![image-20250316234354292](assets/image-20250316234354292.png)

3.判断字段数用order by，是否发生异常![image-20250316234828738](assets/image-20250316234828738.png)

4.回显位置：多输入的联合查询帮助判断字段的拿些位置会在页面中显示。![image-20250316234512785](assets/image-20250316234512785.png)

这里有三个字段，由联合查询判断回显位置是2,3字段

查看显示列：

![image-20250316234928433](assets/image-20250316234928433.png)

![image-20250316234937582](assets/image-20250316234937582.png)

堆叠注入：

![image-20250316235208713](assets/image-20250316235208713.png)

![image-20250316235514206](assets/image-20250316235514206.png)

![image-20250317005017397](assets/image-20250317005017397.png)但是有的时候发现用联合注入没办法获取到信息（按理来说第五关会有5列，应该能够在id=-1的情况下输出union要求的内容，也就是不能显示回显位置)

## 报错盲注：

没办法告诉报错，

通过特殊函数错误使用使其产生错误结果来获取信息。、

![image-20250317005434389](assets/image-20250317005434389.png)

![image-20250317010524456](assets/image-20250317010524456.png)

通过函数后面的错误参数产生报错返回数据库里的信息。![image-20250317010403893](assets/image-20250317010403893.png)

![image-20250317010648297](assets/image-20250317010648297.png)

因为显示字符有限，所以后面再加where排除已经显示出来的名字

![image-20250317010937865](assets/image-20250317010937865.png)

也可以这样，用mid函数截取子字符串：

![image-20250317011502181](assets/image-20250317011502181.png)

把查询语句写在灰色部分。

![image-20250317011730160](assets/image-20250317011730160.png)





## 布尔盲注：

![image-20250317093426854](assets/image-20250317093426854.png)

逐个试每一位的字符。

字符串截取：

1. substr（str，pos，len）

2. mid（）

3. right（）从又开始截取多少位，外面再使用ascii码select  ascii（）/ord()【可以通过二分查找解决】![image-20250317094237102](assets/image-20250317094237102.png)

4. trim（）：

   ![image-20250317154713778](assets/image-20250317154713778.png)

5. between

6. in：  select 1 in 



7. 异或：

   不允许使用注释符号。因为一个数^自身=0 一个数^0=1

id=1'^(...)^ '1'

## 延时盲注

## 