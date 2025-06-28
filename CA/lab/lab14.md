lab14

![image-20250524190258408](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250524190258408.png)

1.1：32B

前3位代表virtual page，后五位代表offset，先去TLB寻找对应vpage，有就通过physical number找找physical Memory上的数据。没有就去page Table找页码，如果是Invalid就there  was a page fault.
The page must now be brought into physical memory from the hard disk（或者是替换LRU的page）.page table里面替换或者存入相应地址的数据，