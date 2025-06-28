# LaTeX学习

## overleaf

左上方Menu里可以下载源码导出pdf

![image-20240925213736831](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925213736831.png)

### 格式

\documentclass{article/...}

\begin{document}



\title{First document}

\author{quanquan}

\date{\today}



\begin{titlepage}

\maketitle

\end{titlepage}//这对begin end没有生成的就直接跟在标题后面

> 这是给文章添加标题页，在最外层的begin外面还要添加三行代码



\begin{abstract}

> 摘要内容

\end{abestract}

> 正文

\section{Introduction}

> 正文分块

\subsection{}

> 子段落

\section{Method}

\section{Experimrnt}

\end{document}

### 如何使用中文

第一行之后

\usepackage{xeCJK}

- 切换编译器

![image-20240925214750334](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925214750334.png)

### 换行符和换页符号

1. 换行
   - 两个回车
   - 段尾：\par

2. 换页
   - \newpage

### 左右居中对齐

\begin{center}

\end{center}

\begin{flushleft/flushright}--左右对齐

### 字体设置

\textbf{}粗体效果

\underline{}下划线

\textit{}斜体效果

可以互相嵌套

- 改变字体大小

  {\tiny ...}

​	tiny->scriptsize->footnotesize->small->normalsize->large->Large->LARGE->huge->Huge

### 放图片

1. 先创建文件夹上传图片

2. 代码前面需要添加\usepackage{grahicx}

3. 指定图片所保存的路径\graphicspath{{./images/}}

4. 在想要插入图片的地方使用代码

   

   \includegraphics[scale=1.5(放缩比例)，angle=45（旋转角度），width=3cm，height=4cm，left/right/center(对齐方向)]{images文件夹下的图片名称}

   - 在这行代码里使图片对齐需要导入包：、usepackage[export]{adjustbox}

5. \begin{figure}[h]

   \\includegraphics{universe}

   \end{figure}

   > 使图片能够浮动，排版更加美观

### 文字包围图片

1. 导入wrapfig包

2. \begin{wrapfigure}{r/l（代表对齐方向）}{0.25\textwidth}

   \includegraphics[width=0.25\textwidth]{...}

> 这里图片把包围盒填满了

### 图片插入标题

\caption{图片标题}//写在插入上面就是在图片上方插入标题，写在下方就插入在下方

\centering//让图片标题居中

#### 让一个标题对应多张图片

1. subcaption包
2. 每张图片都用begin{subfigure}包围起来

![image-20240925221658965](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925221658965.png)

![image-20240925221728762](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925221728762.png)

### 图片引用

在正文中用\ref{图片名}//自动帮你对应图片标题

\pageref{...}自动对应图片所在的页码

### 插入表格

\begin{tabular}{c c c}//三个c表示有三列，l/r/c表示对齐方式

![image-20240925222234078](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925222234078.png)

- 添加竖线{|c|c|c|}

- 添加横线

\hline

cell1&cell2&cell3

\hline

- 固定表格规格
  1. 导入array包
  2. \begin{tabular}{|m{3cm} |m{1cm}|m{1cm}<{\centering}//居中对齐| }

- 合并单元格

  1. \begin{tabular}{c c c}

     \multicolumn{3}{|c|}{想要的名字}&{剩下的名字}

     ![image-20240925223136706](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925223136706.png)

![image-20240925223146041](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925223146041.png)

### 数学公式

- 希腊字母

$$
\delta,\lambda\\
\Delta,\Lambda\\
\Alpha,\Beta\\
\phi,\varphi\\
\epsilon,\varepsilon
$$

![image-20240925223646575](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240925223646575.png)

- 上下标
  $$
  a^2,a_1\\
  x^{y+z},p_{ij}\\
  $$
  
- 分式与根式
  $$
  \frac{1}{2},\frac1 2\\
  \frac1 {x+y}\\
  \frac{\dfrac 1 x+1}{y+1}
  $$
  
- 

$$
根号\\
\sqrt 2,\sqrt {x+y}\\
运算符\\
\times,\cdot,\div\\
\pm\\
\mp\\
比较符号\\
<>,\ge,\le,\ll.\gg,\ne\\,\approx,\equiv\\
集合\\
\cap,\cup,\in,\notin,\subset,\subseteq,\subsetneq,\varnothing,\forall,\exists,\nexists,\because,\therefore\\
\mathbb R,\R,\N,\Z\\
\cdots\\
偏分等\\
\infty,\partial,\nabla,\propto,\degree\\

函数\\
\sin x,\sec x\\
\log_2 x,\ln x\\
极限\\
\lim\limits_{x \to 0} \frac {x}{\sin x}
最大值\\
\max\limits x
$$



- 大型运算符
  $$
  求和\\
  \sum,\prod\\
  \sum_{i=0}^n\\
  积分\\
  \int,\iint,\iiint,\oint,\oiint\\
  \int_{-\infty}^0 f(x)\,\text d x{}{}
  $$
  
- 间隔
  $$
  a\, a\\
  a\ a\\
  a\quad a\\
  a\qquad a\\
  $$

- 标注符号
  $$
  \vec x,\overrightarrow AB\\
  \bar x, \overline {AB}\\
  $$
  
- 箭头
  $$
  \leftarrow,\rightarrow,\Rightarrow,\leftrightarrow,\Leftrightarrow
  $$
  
- 

![image-20240926152326524](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20240926152326524.png)

- 括号与定界符
  $$
  \{\}\\
  \lceil,\rceil,\lfloor,\rfloor,||\\
  高度自适应的括号\\
  \left(0,\frac1 a\right ]\\
  大小自适应的竖线\\
  \left.\frac{\partial f}{\partial x}\right|_{x=0}\\
  $$
  
- 多行公式

$$
\begin{align}//默认右对齐，加入\&，\&之间对齐\\
a&=b+c+d\\
&=e+f
\end{align}
$$

- 大括号
  $$
  f(x)=
  \begin{cases}
  \sin x, & \pi\le x \le \pi\\
  0, & \text 其他
  \end{cases}
  $$
  
- 矩阵

$$
\begin{matrix}
a & b & \cdots & c\\
\vdots & \vdots & \ddots& \vdots\\
e &f  &\cdots &g
\end{matrix}
$$

$$
bmatrix\\
\begin{bmatrix}
a & b & \cdots & c\\
\vdots & \vdots & \ddots& \vdots\\
e &f  &\cdots &g
\end{bmatrix}
$$

$$
pmatrix\\
\begin{pmatrix}
a & b & \cdots & c\\
\vdots & \vdots & \ddots& \vdots\\
e &f  &\cdots &g
\end{pmatrix}
$$

$$
vmatrix行列式\\
\begin{vmatrix}
a & b & \cdots & c\\
\vdots & \vdots & \ddots& \vdots\\
e &f  &\cdots &g
\end{vmatrix}
$$

- 组合公式
  $$
  \binom{n}{k}
  $$
  
- 实操
  $$
  f(x) =\frac1 {\sqrt {2\pi}\sigma}e^{-\frac{(x-\mu)^2}{2\sigma^2}}
  $$
  

$$
\lim\limits_{N \to \infty} P
\left\{

\left|\frac{I(a_i)}{N}-H(s)\right|
<\varepsilon
\right\}
=1
$$

$$
x(n)=\frac1 {2\pi}\int_{-\pi}^\pi X\left({\rm e}^{{\rm j} \omega}\right){\rm e}^{{\rm j} \omega n}\, \rm d \omega
$$

$$
\begin{align}
\vec B\left(\vec r \right) &=\frac{\mu_0}{4\pi}\oint_c \frac{I \, \rm{d}\vec l \times \vec R}{R^3}\\
 &=\frac{\mu_0}{4\pi}\oint_V \frac{\vec J_V \times \vec R}{R^3} {\rm d}V'\\
\end{align}
$$

