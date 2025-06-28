# lab2

![image-20250228144040774](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250228144040774.png)



![image-20250228145206274](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250228145206274.png)

![image-20250228145241692](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250228145241692.png)

#### . **避免悬空指针（Dangling Pointer）**

当你用 `Queue *queue` 时，释放队列内存后，`queue` 本身依然指向已经被释放的内存。如果你在 `queue_free` 调用后再次访问 `queue`，它将成为一个悬空指针，可能导致程序崩溃或者产生未定义行为。通过传递 `Queue**`（指向指针的指针），我们可以在函数内部将 `*queue` 设置为 `NULL`，从而避免了悬空指针的问题。





debug：

b 7 

r

n



1. (gdb) run arg1 arg2 arg3
2. (gdb) break <line_number> if <condition>
3. next
4. step
5. continue
6. (gdb) print x
7. (gdb) display x
8. info locals
9. quit







# lab3



Ex1:

1. 

1. **`.data` 伪指令**

- **作用**：
  `.data` 用于定义 **数据段（data segment）**，即程序中存放全局变量和静态数据的内存区域。

- **特点**：
  在 `.data` 段中定义的数据通常是可读写的，程序运行时可以修改这些数据。

- **示例**：

  assembly

  复制

  ```
  .data
  myVar: .word 42   # 定义一个名为 myVar 的变量，初始值为 42
  ```

------

2. **`.word` 伪指令**

- **作用**：
  `.word` 用于在数据段中分配一个或多个 **字（word）** 大小的内存空间，并初始化其值。一个字的大小通常是 4 字节（32 位系统）或 8 字节（64 位系统），具体取决于目标架构。
- **特点**：
  可以定义单个值，也可以定义多个值（数组）。
- 

3**`.text` 伪指令**

- **作用**：
  `.text` 用于定义 **代码段（text segment）**，即程序中存放指令的内存区域。代码段通常是只读的，存放程序的机器指令。
- **特点**：
  在 `.text` 段中编写的是程序的逻辑代码（如函数、跳转、算术运算等）。



2.  

   1.`la` 通常会被转换为两条指令：

RISC-V 的指令集是固定长度的（每条指令 32 位），因此无法在一条指令中直接加载一个 32 位的地址。为了加载一个完整的 32 位地址，RISC-V 使用以下两条指令的组合：

1. **`auipc`**：将地址的高 20 位与 PC（程序计数器）相加，结果存储到目标寄存器。
2. **`addi`**：将地址的低 12 位与目标寄存器的值相加，得到完整的地址。

​	2. **`mv`（Move）**

- **作用**：将一个寄存器的值复制到另一个寄存器。

- **转换**：
  `mv` 实际上是一个伪指令，通常会被转换为 `addi`（Add Immediate）或 `or` 指令。

  3. **`j`（Jump）**

  - **作用**：无条件跳转到指定的标签或地址。

  - **转换**：
    jal x0 label

    



3. reutrn 0,a0=1,priint a1 value=0 结果是34

4. n的address 0x10000000
5. t3改为13.



## Ex2

1. t0=k

2. t1 pt of source t2
3. loop
4. add t4, t1, t3/（t3=0，4，8,12,每次+4，相当于移动到下一个元素)
5. add t6, t2, t3



# lab4

simple_fn:

使用了unset的t0，临时寄存器的值在 **不同 label 之间不会自动保留**，除非显式保存。

naive_mod:

要存储s0的值

mularr：要存储s0，s1

naivemodloop&&。。。：没用到ra

- Why do we need to store `ra` in the prologue for `mul_arr`, but not in any other function?：

  因为这个函数使用jal、会修改ra的值，但是最后需要还原返回给caller的ra的最初的值

  When a function calls another function (using `jal` or `jalr`), the value of `ra` is overwritten with the return address for the new function call. If the original function needs to return to its caller, it must save the original value of `ra` before making the call.

为什么没有CC报错：检查器的主要目的是帮助开发者快速发现一些常见的调用约定错误，而不是彻底验证代码的正确性。**它只会检查那些通过 `.globl` 导出的函数中的错误。**在汇编语言中，`.globl` 指令用于将某个符号（通常是函数名）标记为 **全局符号**，使其对其他文件或模块可见。helper——fn没有定义在全局变量