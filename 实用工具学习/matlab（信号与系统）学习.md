# Matlab

## Matlab Variables

###  Create Variables

1. 向量

```matlab
vector=[1,2,3]%行向量
vector3 = [4;5;6] % 列向量：使用分号分隔列向量中的元素
vector_3_4 = [vector3; vector4] % 向量组合

```

2. 矩阵

```matlab
matrix1 = [10 20 30; 40 50 60;70 80 90] % 矩阵，包含行和列；使用空格或逗号分隔一行
中的元素；使用分号分隔不同的行

```

3. 冒号的使用

起始值 : 步长 : 终止值（升序时默认为1）

```matlab
colon2 = [1:2:10;... % 从 1 开始，以 2 递增，直到 10（小于等于 10）的等差序列。（代码太长
时可使用...来换行）
 2:2:10] % 从 2 开始，以 2 递增，直到 10（小于等于 10）的等差序列
```

4. 变量及元素的调用

   - 索引从1开始，用小括号括起来。用end表示最后一个元素。

     ```matlab
     scalar1 % 使用变量名直接引用
     scalar1(1) % 使用 变量名(索引) 引用变量中的元素
     scalar1(end)
     vector1(1:end) % 索引的头尾都包含
     vector1(end-1:-1:1) % 利用冒号来引用向量中的多个元素
     matrix1(2,2) % 行列索引，位于第 2 行，第 2 列的元素
     matrix1(4) % 元素索引，按列的方向计数
     matrix1(1:2:end, end:-1:1)
     matrix1(3,:)
     
     ```

     

5. 矩阵运算

   - 区分.\*与*![image-20241007164230624](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241007164230624.png)

     

### Plotting

1. 创建信号

   ```matlab
   clear; clf;%clear;这个命令将从工作空间中删除所有变量，使工作空间变为空白状态。这个命令将从工作空间中删除所有变量，使工作空间变为空白状态。clf 在需要清除当前图形窗口内容并重新开始绘制时非常有用。
   t = 0:pi/4:2*pi % 先定义时间轴（横轴）
   
   sigt = sin(t) % 根据时间轴算出函数值
   sigy = cos(t);
   
   ```

2. 画出信号

​	plot 用于绘制时间连续信号

​	stem 用于绘制时间离散信号

```matlab
plot(sigx); 
plot(t,sigx, '--r'); %使用 t 作为横轴，sigx 作为纵轴，绘制红色虚线。
plot(t,sigx,'--r',t,sigy,'-y'); %同时绘制两条曲线，sigx 用红色虚线表示，sigy 用黄色实线表示。
stem(t(1:10:end),sigx(1:10:end),'* g')%使用干涉图绘制每隔 10 个点的 sigx 值表示，并用绿色星号标记数据点。

```

3. 创建带符号变量的信号

   fplot其语法与 `plot` 命令略有不同，因为 `fplot` 直接接受一个函数句柄，而不是具体的函数值列表。

   ```matlab
   clear; clf;
   syms x y % 定义符号变量
   y = sin(x) % 写出符号表达式
   fplot(x,y); 
   fplot(y,[0 2*pi]); % 第二个参数[0 2*pi]限制了 y 的横轴范围，如省略，默认范围为[-5 5]
   fplot(x,y,[0 2*pi],"Color",'m',"LineStyle","--") % 键值对限制线形,'Color', 'm'：设置绘制线条的颜色为紫色 ('m’表示magenta)。'LineStyle', '--'：设置线条的样式为虚线。
   
   ```

4. subplot

   ```matlab
   subplot(2,2,1); plot(t,sigx);xlabel('t');%这将工作区域划分为一个 2x2 的子图网格，并激活第1个子图。具体来说，这把绘图窗口分成 2 行 2 列的子图布局，并激活左上角的第一个子图窗口。plot(t, sigx);：在第一个子图窗口中绘制 t 对 sigx 的图形。xlabel('t');：给横轴添加标签为 t。
   subplot(2,2,3); plot(t,sigy);xlabel('t');
   subplot(2,2,[2 4]); plot(t,sigx,'--r',t,sigy);
   
   ```

   

5. 绘图标注

   ```matlab
   clf;
   plot(t,sigx,t,sigy);
   title('Sine');
   xlabel('time');
   ylabel('amplitude');
   legend('sin(x)','sin(y)');%给多个函数的标注。
   ```

   

### Range

只显示有意义的信号部分，比如因果信号只显示 0 时刻之后的部分

```matlab
axis([0 6.5 -1.1 1.1]); % 使用数组的形式组织范围参数:[xmin xmax ymin ymax]
% xlim([0 5]); % [xmin xmax]
% ylim([-1 1]); % [ymin ymax]
```

### Grid

```matlab
plot(sigx);
grid on;
grid minor;% 开启主网格线和次网格线
```

## Functions to Generate Typical Signal

### Asin/cos(wt+phi)

```matlab
A=1;
w=2*pi;
pha=pi/6;
%Numeric methods
dt=0.01;
t=0:dt:10;
ft=A*cos(w*t+pha);
plot(t,ft);axis[0 5 -1 1];
%Symbolic methods
syms x
y=A*cos(w*x+pha);
fplot(y,[0 5]);ylim([-1 1]);
```

#### 采样信号：sinc(t)

```matlab
%numeric
dt=0.01;
t=-3:dt:3;
ft=sinc(t);
%symbol
syms x;
y=sinc(x);

```

### A\*exp(a\*t)

```matlab
%numeric
dt=0.01;
t=-3:dt:3;

plot(t,ft);hold on;%用于保持当前绘图和所有轴属性，以便随后的绘图命令添加到现有图形中，而不重置颜色和线型。也就是和之后绘制的图形在同一个窗口。

%symbol
syms x;
y=A*exp(a*x);
fplot(x,y,[0 10],'--');hold off;

```

### Aperiodic Triangle

tripuls(t,w,s)

t:时间轴

w:三角形底边宽度

s:顶点位置[-1,1]

![image-20241014153832655](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014153832655.png)

![image-20241014153848891](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014153848891.png)

### SawTooth/Triangle wave

sawtooh(t,xmax)

t:时间轴

xmax：顶点位置。范围[0,1]

默认周期是2pi。

```matlab
f1=sawtooth(t,0);%顶点的位置相当于一个周期里的某个位置。
f2=sawtooth(pi*t,1);%w*t=(2*pi/T)*t 改变了周期。
```

![image-20241014154835627](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014154835627.png)

### Aperiodic Rectangle

rectpuls（t,w）

w:矩阵宽度。

![image-20241014154749078](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014154749078.png)

![image-20241014154811673](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014154811673.png)

### Square wave

square（t,d）

d:占空比，信号为正的部分所占比例，范围[0 100]

![image-20241014155052716](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014155052716.png)

![image-20241014155107691](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014155107691.png)

### **Step Function**

heaviside(t)

![image-20241014155312366](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014155312366.png)

![image-20241014155325652](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014155325652.png)

### Delta Function

冲击信号：dirac（x）

![image-20241014155430490](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014155430490.png)

## Signal Operation

### Differential and Integral微分（求导）

1. symbolic method: diff(S,'v'，N)每次微分，序列长度会减一，微分结果还要除以dt。
2. numeric：diff(x,n)

![image-20241014160158888](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014160158888.png)

### Integral 积分

1. symbolic：int（s,v）(对函数s，对v求积分)
2. numeric:cumtrapz(t,y)

```matlab
y1=heaviside(x);
y2=int(y1,x)+c;
```

3. 定积分int（S，v,a,b）、trapz（t,y）

### Complex Arithmetic

```matlab
z=complex(x,y)%z=x+y*i
real(z)=x;
imag(z)=y;
ans(z);%求模
angel（z）；%求相位
```

## Programing Structure

#### Loop

```matlab
%for loop
for i=1:10
...
end
%while
while i>0
...
end

```

#### Branch

![image-20241014161234265](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014161234265.png)

![image-20241014161249993](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241014161249993.png)
