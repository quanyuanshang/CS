# Venus

 Dump:完全复制出machine code

Assembler Directive:

.equiv three 3 相当于宏替换 把代码中的3替换成three

.data 把数据放入.data段中

​	![image-20250309024058222](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309024058222.png)

​	.align是为了让数据对齐

.text 使用.data的数据

​	![image-20250309024427737](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309024427737.png)

​	la：加载地址

Evironmental call

相当于调用操纵系统函数

把environmental call的id放到a0寄存器里面，后面的寄存器

存放不同指令需要的参数

![image-20250309111935363](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309111935363.png)

1. print_int :let register be a printer and print the value of the pointer

2. sbrk: memory manegment in heap but don't have free

   vlib:![image-20250309112048156](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309112048156.png)

   a0里放0x3CC，然后a6：![image-20250309112127868](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309112127868.png)

3. exit：退出程序

   exit2：以a1里的值推出





eg：![image-20250309112459171](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250309112459171.png)

先是ecall了9号sbrk，开辟了以a0为指针的4字节的 内存。



上传文件，新建文件如果要保存一定要选中save on close。

mutable text：（关闭以下操作直接报错）

```
li t0,0 #t0 is set to be 0这时候是invalid instruction
sw t0, 0(t0) #set the word begins at t0 be 0(32bits)
```



exit call：不遇到ecall不会停止



2. 