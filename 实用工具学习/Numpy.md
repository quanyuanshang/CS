# python数据分析

## Numpy

主要用于科学计算和数据分析。它提供了多维数组对象（`ndarray`）以及一系列操作这些数组的函数。

1. numpy创建矩阵：

- `array=np.array([[*1*,*2*,*3*],[*4*,*5*,*6*]])`
- 创建一个矩阵

数组维度：`array.ndim`      2

矩阵尺寸：`array.shape`      （2,3）

​	注意维度：`np.array([[200,17]])`1*2二维矩阵

​	`np.array([200,17])这是个一维的向量`

数组元素个数：`array.size`       6

也可以自己定义类型：`array=np.array([[*1*,*2*,*3*],[*4*,*5*,*6*]]，dtype=np.int)`



`array.dtype`

- 生成全部为0/1的矩阵：

  `a=np.zeros((3,4))`3行4列的矩阵

  `a=np.ones((3,4))`3行4列的矩阵

- 生成有间隔的数列

  `a=np.arange(10,20,2)`

 - 自主决定形状：`a=np.arange(12).reshape((3,4))`从0到11

 - 生成线段：`a=np.linespace(1,10,5)`

   初识值为1终止值为10，均等分成5段，也可以.reshape重新定义形状。
   
   - 利用arange选取数组特定部分：
   
     > y=[1,2,3]样本的正确类别索引
     >
     > scores=[[],
     >
     > ​		[],
     >
     > ​		[],...]共num_train（3） 行
     >
     > scores[np.arange(num_train,y)]=从scores中的每一行（也就是num_train行），取出对应正确类别索引里存放的分数。

2. numpy基础运算

   - a、b都是数组，a-b是元素对应做减法

   - b**2是对b中各个数单独做平方

   - 调用三角函数：`c=10*np.sin/tan/cos(a)`对a每个元素做sin函数求值

   - 判断数组中哪些元素大小是否符合条件：`b<3`![image-20250218204229687](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20250218204229687.png)

   - 运算矩阵：

     `a=np.array([\[1,1][0,1]])`

     `b=np.array(4).reshape((2,2))`

     - 逐个相乘：`c=a*b`
     - 矩阵乘法`c=np.dot(a,b)/a.dot(b)`

     `a=np.random.random((2,4))`随机生成shape为（2,4）的矩阵

     - 元素求和：`np.sum(a)`

     - 求最值：

       `np.min/max(a)`

       `np.min/max(a,axis=0)`0对应列的min

       `np.min/max(a,axis=1)`1对应行的min

### 1. 多维数组（ndarray）

`numpy`的核心是`ndarray`对象，它是一个多维数组，可以存储相同类型的元素。

```py
import numpy as np

# 创建一维数组
a = np.array([1, 2, 3, 4])
print(a)  # 输出: [1 2 3 4]

# 创建二维数组
b = np.array([[1, 2], [3, 4]])
print(b)  # 输出: [[1 2]
          #        [3 4]]
```

索引从0开始

### 2. 数组操作

`numpy`提供了大量的函数来操作数组，包括数学运算、逻辑运算、统计运算等。

```py
# 数学运算
c = a + 1
print(c)  # 输出: [2 3 4 5]

# 逻辑运算
d = a > 2
print(d)  # 输出: [False False  True  True]

# 统计运算
mean_a = np.mean(a)
print(mean_a)  # 输出: 2.5
```

### 3. 数组创建

`numpy`提供了多种方法来创建数组，包括从列表创建、使用内置函数创建等。

```py
# 从列表创建数组
e = np.array([1, 2, 3, 4])

# 使用内置函数创建数组
f = np.zeros((2, 2))  # 创建一个2x2的全零数组
print(f)  # 输出: [[0. 0.]
          #        [0. 0.]]

g = np.ones((2, 2))  # 创建一个2x2的全1数组
print(g)  # 输出: [[1. 1.]
          #        [1. 1.]]

h = np.arange(0, 10, 2)  # 创建一个从0到10（不包括10），步长为2的数组
print(h)  # 输出: [0 2 4 6 8]
```

### 4. 数组索引和切片

`numpy`支持类似于Python列表的索引和切片操作，但功能更强大。

```py
# 索引
print(a[0])  # 输出: 1

# 切片
print(a[1:3])  # 输出: [2 3],左闭右开
a[-4:4]#倒数第四位到正数第四位
a[:1]#默认从0开始
a.index(2)#输出2在列表里的位置
# 多维数组索引
print(b[0, 1])  # 输出: 2

# 多维数组切片
print(b[:, 1])  # 输出: [2 4]
```

### 5. 数组形状操作

`numpy`提供了多种方法来改变数组的形状。



```py
# 改变数组形状
i = np.arange(6)#生成从1到6的等差数列
#np.arange(1, 7) 生成从 1 到 6 的数组：[1 2 3 4 5 6]

#np.arange(0, 1, 0.2) 生成从 0 到 1（不包括 1），步长为 0.2 的数组：[0. 0.2 0.4 0.6 0.8]
print(i)  # 输出: [0 1 2 3 4 5]

j = i.reshape((2, 3))
print(j)  # 输出: [[0 1 2]
          #        [3 4 5]]

# 展平数组
k = j.flatten()
print(k)  # 输出: [0 1 2 3 4 5]
```

### 6. 数组拼接和分割

`numpy`提供了多种方法来拼接和分割数组。

```py
# 拼接数组
l = np.array([1, 2, 3])
m = np.array([4, 5, 6])
n = np.concatenate((l, m))
print(n)  # 输出: [1 2 3 4 5 6]

# 分割数组
o = np.split(n, 2)
print(o)  # 输出: [array([1, 2, 3]), array([4, 5, 6])]
```

### 7. 线性代数运算

`numpy`提供了丰富的线性代数运算功能，包括矩阵乘法、求逆、特征值等。

```py
# 矩阵乘法
p = np.array([[1, 2], [3, 4]])
q = np.array([[5, 6], [7, 8]])
r = np.dot(p, q)
print(r)  # 输出: [[19 22]
          #        [43 50]]

# 求逆矩阵
s = np.linalg.inv(p)
print(s)  # 输出: [[-2.   1. ]
          #        [ 1.5 -0.5]]
```

### 8. 随机生成

`numpy`提供了多种随机数生成函数，用于生成各种分布的随机数。

```py
# 生成均匀分布的随机数
t = np.random.rand(3)
print(t)  # 输出: [0.12345678 0.23456789 0.34567890]

# 生成正态分布的随机数
u = np.random.randn(3)
print(u)  # 输出: [1.23456789 2.34567890 3.45678901]
# 生成一个单一的随机数
random_number = np.random.rand()
print(random_number)
random_array = np.random.rand(3, 3)
print(random_array)

# 生成一个服从标准正态分布的随机数
random_number = np.random.randn()
# 生成均值为 5，标准差为 2 的正态分布随机数
random_normal = np.random.normal(5, 2, size=(3, 3))
print(random_normal)
```



**随机抽样函数：**

### 

```
python


复制编辑
np.random.choice(a, size=None, replace=True, p=None)
```

#### **参数说明**

- `a`：
  - **如果是整数**，表示从 `np.arange(a)` 生成的数组（`[0, 1, ..., a-1]`）中进行选择。
  - **如果是数组**，表示从这个数组中选择元素。
- `size`：要抽取的样本数量（默认为 `None`，即返回单个元素）。
- `replace`：
  - `True`（默认）：**有放回抽样**（可以重复选取同一个元素）。
  - `False`：**无放回抽样**（不会重复选取元素，要求 `size ≤ len(a)`）。
- `p`：每个元素被选中的概率（默认 `None`，即均匀分布）。

### 

```py
np.random.choice(a, size=None, replace=True, p=None)

```



### 9. 文件输入输出

`numpy`提供了多种方法来读写文件，包括文本文件和二进制文件。

```py
# 保存数组到文件
np.save('array_file', a)

# 从文件加载数组
v = np.load('array_file.npy')
print(v)  # 输出: [1 2 3 4]
```

### 10. 广播（Broadcasting）

`numpy`支持广播机制，使得不同形状的数组之间可以进行运算。

```py
# 广播
w = np.array([1, 2, 3])
x = np.array([[1], [2], [3]])
y = w + x
print(y)  # 输出: [[2 3 4]
          #        [3 4 5]
          #        [4 5 6]]
```

1. **`theta.ravel()`**:

   - `ravel()` 是 NumPy 的方法，用于将多维数组展平为一维数组。
   - 例如，如果 `theta` 是 `[[1, 2, 3]]`，`theta.ravel()` 会返回 `[1, 2, 3]`。


**`np.power(error, 2)每一位上的值都平方`**



# Panda

data.head()查看数据集的前几行（5行）

**`data`**:

- 这是一个 `pandas` 的 `DataFrame` 或 `Series` 对象，通常是通过 `pd.read_csv()`、`pd.read_excel()` 等方法加载的数据。
- 对于二维数组读入，直接通过names对两列定义数组姓名

```py
df = pd.read_csv('data.csv')
data = pd.read_csv(path, header=None, names=['Population', 'Profit'])
df.to_excel('data.xlsx')



```

insert：

参数（插入位置索引，新列名称，新列的值）

```py
data.insert(0, 'Ones', 1)
```

iloc：

X = data.iloc[:,0:cols-1]#X是所有行，去掉最后一列
y = data.iloc[:,cols-1:cols]#y是所有行的最后一列

# matplotlib

```py
import matplotlib.pyplot as plt
#或者是
from matplotlib import pyplot as plt
x=
y=#x,y维度要保持一致
plt.plot(x,y)
plt.show()
```

1. 设置图片大小：

   **`plt.figure(figsize=(10,6)，dpi=80)`**:写在plot前面

   dpi越高可以让图片更加清晰。

2. 图片保存

   在绘制之后plt.savefig("***.png"),要想放大不会失帧放网页，采用svg格式

3. 调整x轴刻度

   调整疏密

   ```py
   _xticks_labels=[i/2 for i in range(4,49)]
   plt.xticks(_xticks_labels)
   plt.yticks(range(min(y),max(y)+1))
   ```

   改成字符串

   ```py
   _x=list(x)[::10]
   _xticks_labels=["hello,{}".format(i) for i in _x]#format用法：使用 {} 作为占位符，format() 中的参数会按顺序替换占位符。
   plt.xticks(x,_xticks_labels)#把数字和字符串做一一对应
   ```

   还可以旋转，设置字体：

   ```py
   from matplotlib import font_manager
   my_font=font_manager.FontProperties(fname="C:\Windows\Fonts\msyh.ttc")
   plt.xticks(_x[::3],_xticks[::3],rotation=45,fontproperties=my_font)
   ```

   

- 创建一个新的图形窗口。
- `figsize=(10,6)` 指定图形的大小为宽度 10 英寸，高度 6 英寸。

**`plt.scatter(data['Population'], data['Profit'], marker='x', c='red')
plt.show()`**

- 用红十字画出训练集的图像

```
x = np.linspace(data.Population.min(), data.Population.max(), 100)
```

1. **`data.Population.min()`**:
   - 获取 `data` 数据集中 `Population` 列的最小值。
2. **`data.Population.max()`**:
   - 获取 `data` 数据集中 `Population` 列的最大值。
3. **`np.linspace(start, stop, num)`**:
   - 这是 NumPy 的函数，用于生成从 `start` 到 `stop` 的等间隔数值数组。
   - `start`：起始值。
   - `stop`：结束值。
   - `num`：生成的样本数（默认是 50）。
4. **`x`**:
   - 生成的等间隔数组，长度为 100。