# Valgrind

1. 使用要求：编译程序时使用调试信息-g

2. 使用方法：`valgrind --leak-check=full ./your_program`

3. 常用选项：

--leak-check=fulll：启用详细的内存泄漏检测

--track-origins=yes：内存未初始化时报告来源，这时候工作时间比较长

--log-file=filename：结果输出到filename里面。

4. 常见内存泄漏场景

   - new了两次，第一次给到的空间就找不到了

     ![image-20250304111135912](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250304111135912.png)

   - 结构体的指针delete了但是忘记释放里面成员的指针

     ![image-20250304111507746](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250304111507746.png)

   - 无效写入，使用未初始化指针。容易非法使用空间。

     ![image-20250304111711204](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250304111711204.png)

