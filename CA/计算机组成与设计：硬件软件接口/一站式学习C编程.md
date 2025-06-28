# 一站式学习C编程

## 第13章

- XOR亦或：两个操作数相同结果为0，两个操作数不同结果为1.

- NAND/NOR：在AND/OR基础上取反。

  一位全加器：

![image-20250127164741763](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127164741763.png)

- 十进制数转化为二进制数：

  1. 除二反序取余法：

  ![image-20250127165602695](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127165602695.png)

二进制数每三位一组看就是8进制，没4位一组看就是16进制。A~F代表10~15.

​	2. 十进制小数换算为二进制的小数

​	将十进制小数 0.6250.625 转换为二进制。

1. 0.625×2=1.25 → 整数部分为1，小数部分为0.25
2. 0.25×2=0.5 → 整数部分为0，小数部分为0.5
3. 0.5×2=1.0→ 整数部分为1，小数部分为0

将整数部分按顺序排列，得到二进制小数 0.101。

![image-20250127170349653](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127170349653.png)

- 整数的减法计算：

  1. 1's complement

     正数从00000000到01111111（但是0的表示不唯一，11111111也可以表示为0）

负数用1的补码表示，减法转化为加法，计算结果的最高位如果有进位要加回到最低位上。

![image-20250127171415704](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127171415704.png)

​	2. 2's complement（处理0会有两种表达式）

​	正数从00000000到01111111（0到127）负数10000000到11111111（-128到-1）

​	正数不变，负数先取1的反码再加1，此时计算结果的最高位如果有进位不必加回到最低位上。

​	3. 如何判定溢出

​	![image-20250127175412240](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127175412240.png)

- 浮点数

  1. 浮点数的表示：

     

     ![image-20250127174637438](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127174637438.png)

     因为指数（表示2的多少次方）可以是负数，采用一个偏移量：比如6，指数是-1，那里就填15，是1就填17.

     正规化。小数部分最高位必须是1，所以这个直接会被忽略不写。eg：（17）2是10001（000补3个零因为要求8位）直接写成00010000

  2. 浮点数的加法：

     ![image-20250127175020462](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127175020462.png)

     先根据指数部分化为正常小数。

  3. 浮点数的溢出

     ![image-20250127175247957](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250127175247957.png)

## 第14章 数据类型

- 整型

  ![image-20250128113721452](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128113721452.png)

  ![image-20250128113652689](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128113652689.png)

  ![image-20250128113759953](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128113759953.png)

  

- 浮点型

  表示形式：314e-2就是3.14

  没有后缀的浮点数是double，有f/F后缀的是float，后缀了l/L是long double。

  - `float`：单精度浮点数，通常为32位，提供约6-7位有效数字。
  - `double`：双精度浮点数，通常为64位，提供约15-16位有效数字。

- 类型转换

  - 隐式类型转换

  1. integer promotion：

     - 函数的参数列表里有...,调用函数时要对相应的实参做integer promotion（相应的实参如果是float也要提升为double）
     - ![image-20250128114851875](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128114851875.png)
     - 有/无符号的char/short在算术运算前要做i p转换为int型

  2. usual arithmetic conversion

     +-与<<>>不需要考虑

     ![image-20250128115300170](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128115300170.png)

     ![image-20250128115511766](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128115511766.png)

     ![image-20250128115601026](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128115601026.png)

  3. 由赋值产生的类型转换

     ![image-20250128115952999](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250128115952999.png)

  - 显式类型转换

    eg：double（3）

    

    

## 第15章 运算符详解

1. &、|、~（按位取反）、^（按位亦或）注意integer promotion

2. ![image-20250204132206655](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250204132206655.png)

3. 移位运算符

   移动的位数如果大于操作数的总位数就是undefined

   无符号做右移最高位补全0，有符号implementation defined

4. 复合赋值运算符：

   a+=1,对a只求值1次

   a=a+1求值两次，效率不同

5. 条件运算符

   ![image-20250204132551956](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250204132551956.png)

6. 逗号运算符（左结合）

   从左向右求，但是前面求的值丢掉，只保留最后一个值。

7. sizeof 表达式

   子表达式不求值：sizeof i++，i++不会求值，最后返回类型所占的字节数![image-20250204133709189](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250204133709189.png)

   > sizeof运算符的结果是size_t,

## 第16章 计算机体系结构基础

1. CPU

   从内存中读取指令，然后执行。

   - 寄存器

   ![image-20250205150532165](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205150532165.png)

工作过程：eip寄存器从低位取指令，把指令指向的地址中的值给到指定的eax寄存器

2. 设备

   ![image-20250205151328117](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205151328117.png)

   存在设备寄存器（）

   - 与CPU通过总线连接，按地址读写访问

   - 集成在CPU芯片中

     内存映射：像内存一样访问

     端口：用专用的指令访问

     ![image-20250205151505001](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205151505001.png)

     ![image-20250205151447928](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205151447928.png)

   - 加载：将硬盘上的程序拷贝到内存。

   - 进程：程序加载到内存之后成为操作系统调度执行的一个任务。一个程序也可以多次加载到内存。
   - 中断机制：设备主动通知CPU产生的新数据，CPU正在执行的指令被打断。

   - 操作系统：

     ![image-20250205152252904](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205152252904.png)

     内核：管理进程调度、内存分配使用

3. MMU（虚拟内存管理）

   作用：将虚拟地址映射到物理地址（以页为单位，映射关系由页表规定，并且每一页只能设置一种权限）

   ![image-20250209142401282](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209142401282.png)

   32位处理器的内地址总显示32位，MMU就是32位，但物理地址不一定。

   - 内存保护机制：用户模式和特权模式

     ![image-20250205154158125](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205154158125.png)

​	

4. Memory Hierarchy

   越靠近CPU的存储器容量越小，但访问速度也加快。

   ![image-20250205154623367](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205154623367.png)

   ![image-20250205154825143](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205154825143.png)

## 第17章 x86汇编程序基础

1.  

   .section:把代码分成若干个段，程序被操作系统加载执行时，每个段被加载到不同的地址。

   .data ：保存程序的数据，可读可写。

   .text :只读可执行

   .global：告诉汇编器后面的符号会被链接器用到。

   _start是一个代表地址的符号，需要定义eg：

   > _start:
   >
   > ​	movl $1,%eax #汇编语言中立即数需要前面加$,寄存器名前面要加%，并且第一个操作数总是源操作数，第二个操作数总是目标操作数。

   int:软中断指令，故意产生一个异常。CPU赚到内核模式。

2.  

   cmpl 比较两数是否相等，两数相减结果放到eflags中，如果计算结果为0，那么ZF位为1.

   j（l）e（jump if （less or）equal） 条件跳转：检查eflag中的ZF位是否为1，为1就发生跳转。

   jmp 是无条件跳转到指令位置

   incl %edi 将edi里面的值加1

3. 寻址方式

   ![image-20250205162218499](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205162218499.png)

4. ELF文件

   ![image-20250205162551409](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250205162551409.png)

例子：p218

5. 可执行文件

   可执行文件中会多出来Program Header Table 来描述两个segment的信息（text和data），每个segment加载到内存中两个不同的页，并且文件在页面中的偏移量和内存页面中的偏移量一致。

## 第18章 汇编与C之间的关系

1. 函数调用

   ![image-20250206183516860](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206183516860.png)

   参数从右到左依次压栈，然后ebp寄存器一直会在栈底（最上面），然后函数调用完之后需要把下一条指令的地址压栈。

![image-20250206183543850](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206183543850.png)

![image-20250206184616867](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206184616867.png)

2. main函数、启动历程、退出状态

   gcc调用C编译器、汇编器、链接器

   - main.c被ccl编译成汇编程序

   - > gcc -c main.c
     >
     > gcc main.o -o main

   - 汇编程序被as汇编成目标文件

   - 目标文件和编译器提供的另外几个目标文件链接在一起生成可执行文件。（包括crtl.o）

   启动历程： C程序的入口点是crtl.o提供的_start.main函数被start调用

   操作系统在加载执行main这个程序的时候首先查看它是否有需要动态连接的未定义符号。若有就回去查看需要哪些共享库，然后加载共享库。在其中查找这些未定义符号的定义。![image-20250206201517593](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206201517593.png)

   退出状态：![image-20250206201855797](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206201855797.png)

   ![image-20250206201927829](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206201927829.png)

3. 变量的存储布局

   ![image-20250206202933678](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206202933678.png)

   ![image-20250206202944310](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206202944310.png)

A作为全局变量再用const修饰相当于做了双重保险，必须在定义时做初始化，如果是const局部变量，由于局部变量是在栈上做分配，操作系统无法对栈空间做只读保护。

![image-20250206203438013](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206203438013.png)

可以根据readlf来确定变量所在的字段是在哪里

![image-20250206203211729](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206203211729.png)

![image-20250206203410964](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250206203410964.png)

![image-20250207154134706](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207154134706.png)

helloworld字符串只把首地址压入.rodata栈.因为helloworld是字符串字面值，运行时.rodata段加载到Text segment，操作系统会保护text segment 不被改写，因此改写它会导致段错误。如：

![image-20250211170608015](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211170608015.png)

gcc实现中字符串字面值只读。

- 标识符号的链接属性

  ![image-20250207160420008](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207160420008.png)

内部链接的解释与上面static的解释相呼应

- 变量的生存期：
  - 静态生存期：（External、Internal Linkage或者被static修饰的变量，在程序开始执行时分配内存初始化之后一直到程序结束。）通常位于.rodata,.data,.bss段上。
  - 自动生存期
  - 动态分配生存期：由malloc和free函数控制。



4. C内联汇编

   ![image-20250207163519364](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207163519364.png)

   例子：![image-20250207163545111](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207163545111.png)

   “r”(a)告诉编译器分配一个寄存器保存a的值，作为输入，也就是%1（占位符，为作区分eax前面加两个%），b对应%0

5. volatile限定符号

   gcc编译优化：

   ![image-20250207193726356](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207193726356.png)

   - 普通内存单元（编译优化之后出错）

   普通内存单元程序不去写它就不会变化，可以先把内存单元的值读到寄存器中缓存。

   碎一个普通的内存单元连续做三次写操作只有最后一次的值会保存在内存单元中。

   - 设备寄存器：

     设备不需要改写就自己发生变化，每次读上来的值都可能不一样。

     连续多次向设备寄存器中写数据是有意义的

   可以用volatile限定符修饰变量告诉编译器哪些内存单元的访问不能优化。

5. 内存对齐：![image-20250207200106480](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207200106480.png)

   ![image-20250207200120611](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207200120611.png)

   ![image-20250207200200903](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207200200903.png)



- 特殊情况：Cache

  ![image-20250207194121528](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207194121528.png)![image-20250207194136289](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250207194136289.png)

## 第19章 链接详解

1. 多目标文件的链接

   

2. 定义和声明

   main.c的函数找不到原型：（pop、is——empty()写在stack.c里面）

   编译器不知道去哪里找函数定义，只能隐式声明推测函数原型。![image-20250208112626999](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208112626999.png)

   解决：用extern关键字修饰的函数名具有External linkage(对于函数而言extern通常省略，但是变量不可以省略)

   在最前面补上函数的声明而不是定义。

   ![image-20250208112910423](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208112910423.png)

   而static：![image-20250208113135874](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208113135874.png)

   如果不希望外界（其他文件访问到该文件的变量或函数就加上static，这是一种封装）

3. 头文件

   如何避免写重复的声明，自己写一个头文件

   这样需要声明的所有文件只需要include这个头文件就可以![image-20250208114349756](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208114349756.png)

   ![image-20250208114625197](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208114625197.png)

   ![image-20250208114634040](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208114634040.png)

​	#ifdef XXX

​	#endif

​	如果XXX这个宏没被定义过，那么预处理的输出中包含中间包括的代码，反之则空。

​	![image-20250208115122885](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208115122885.png)

![image-20250208115139477](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208115139477.png)

原则：![image-20250208115359362](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208115359362.png)

4. 静态库

   ![image-20250208153349321](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208153349321.png)

   ![image-20250208154427170](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208154427170.png)

   ![image-20250208153612418](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208153612418.png)

   链接器会把目标文件取出来和可执行文件真正链接在一起，不需要的文件可以不链接。写静态库的一个好处是只需要写一个库文件名，不需要写一长串目标文件名。

5. 共享库

   链接时可以把目标文件中各段的地址做重定位，重定位需要修改指令中的地址。![image-20250208154952918](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208154952918.png)![image-20250208155002167](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155002167.png)![image-20250208155029873](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155029873.png)编译链接成可执行文件![image-20250208155038917](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155038917.png)

​	使用-fPIC：![image-20250208155548972](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155548972.png)![image-20250208155605292](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155605292.png)

![image-20250208155620065](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250208155620065.png)

​	共享库的命名管理：

	- real name：包括完整的版本号
	- soname：只含主版本号，动态链接只要找到soname一致的共享库就可以加载它的动态链接。
	- linker name:仅在编译链接时使用

6. 虚拟内存管理

​	![image-20250209143256544](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209143256544.png)

/bin/bash、动态链接器和各共享库的加载也是根据不同的访问权限分几段加载到进程地址空间的。

但是堆（malloc控制）、保存进程环境变量和命名行参数的栈空间、[vdso]地址段（该共享库由内存虚拟）

作用：

- 控制物理内存的访问权限

- 使每个进程有独立的地址空间

  两个进程在同一个系统中同时运行，可读可写地址段占据相同的虚拟地址范围，由于每个进程被映射到不用的物理页面，每个进程有自己的一套VA到PA的映射表。

  ![image-20250209144621713](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209144621713.png)

- ![image-20250209144733042](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209144733042.png)

- ![image-20250209144818465](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209144818465.png)

![image-20250209144956439](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209144956439.png)

![image-20250209145016366](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209145016366.png)

## 第20章 预处理

![image-20250209160918112](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209160918112.png)

eg：函数式宏定义![image-20250209160935164](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209160935164.png)

- 内联函数

  inline告诉编译器这个函数的调用要快，可以当普通的函数调用，也可以用宏展开的办法实现。

- 运算符和可变参数

  ![image-20250209162243244](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209162243244.png)

  ![image-20250209162757178](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209162757178.png)

#undef是取消宏定义。

![image-20250209182716645](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250209182716645.png)

C语言标准库的头文件是相互独立的。

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210180652249.png" alt="image-20250210180652249" style="zoom:150%;" />

## 第21章 Makefile

1. 为什么需要：

一般编译的时候是好几个文件一起编译：

> gcc main.o stack.o maze.o -o main

但如果修改了其中某个文件，忘记重新编译gcc -c main.c 或者你修改的头文件被很多文件include就需要对其他所有文件都重新编译。这个时候协议额个makefile文件和源代码放在同一个目录下，

![image-20250210182225736](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210182225736.png)

![image-20250210182306609](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210182306609.png)

2. 命令列表中的每一个命令必须以Tab开头

欲更新目标，先更新所有条件；所有条件中只要有一个条件被更新了，目标也随之更新。

也可以这样写：

![image-20250210193513750](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210193513750.png)

没有编译命令makefile会通过隐含规则推断。

3. 变量：

   ![image-20250210193957482](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210193957482.png)

   ：=直接展开

   ![image-20250210194338241](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210194338241.png)

   ![image-20250210194431367](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210194431367.png)

   一些自动变量：

   ![image-20250210194518678](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250210194518678.png)

4. 自动处理头文件的依赖关系：

   gcc -MM main.c > main.d自动把main.c的依赖关系写到文件main.d

5. 常用的make命令行选项

   

![image-20250211120410561](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211120410561.png)

![image-20250211120427673](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211120427673.png)

![image-20250211120603746](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211120603746.png)

## 第22章 指针

全局变量只能用常量表达式初始化。但是变量的地址在编译链接时就确定了，不需要像i上的值一样需要等到运行时才能知道。

![image-20250211120947591](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211120947591.png)

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211120959936.png" alt="image-20250211120959936" style="zoom:200%;" />

1. ![image-20250211121251610](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211121251610.png)

   野指针：指向不确定地址的指针。为了避免野指针出现，在定义指针变量时就要明确给它赋初值，或者初始化为NULL。

2. 数组类型做右值时自动转换成指向首元素的指针，语法和指针相同

   int *p=a;

   int *p=a[10]

   ![image-20250211123321816](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211123321816.png)

3. 指针与const限定符

   > const int *a;
   >
   > int const a；

   a指向的内存单元不可改写，但指针a还是可以指向其他内存单元。

   > int* const a;

   *a可以改写，a不能能改写

   ![image-20250211170133029](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211170133029.png)

   ![image-20250211170716987](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211170716987.png)

   

4. 指针数组

   > int *a[10];指针数组
   >
   > int **pa=&a[0];指向数组首元素的指针
   >
   > 

   int main（int argc，char *argv[]）;argv是指针的指针这里写成类似数组的形式其实为了传递信息“argv是数组指针首元素的指针。

5. 指向数组的指针

   int a[10];

   int （*pa）[10]=&a;

   int *p=arr;p是指向整型的指针（数组第一个元素的指针）

   int *p[10]

   &a[0]表示数组a的首元素的首地址，类型为int*

   &a表示数组a地首地址，类型为int*()[10]

   二维：

   ![image-20250211173819433](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250211173819433.png)

   

6. 函数类型和函数指针类型

   函数类型和数组类型相似，做右值自动转换为函数指针类型。

   
