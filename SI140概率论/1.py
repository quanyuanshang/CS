import numpy as np
import scipy.stats as stats

# 参数设置
n = 100000  # 样本数量
mu_g = 8    # 均值
sigma_g = 1 # 标准差

# 生成 Y_i ~ N(8, 1)
Y = np.random.normal(loc=mu_g, scale=sigma_g, size=n)

# 计算 I(Y_i > 8)
indicator = (Y > 8).astype(int)

# 计算 f(Y_i) 和 g(Y_i)
f_Y = stats.norm.pdf(Y, loc=0, scale=1)
g_Y = stats.norm.pdf(Y, loc=mu_g, scale=sigma_g)

# 计算 h(Y_i) = I(Y_i > 8) * f(Y_i) / g(Y_i)
h_Y = indicator * f_Y / g_Y

# 计算 c
c = np.mean(h_Y)

print(f"c 的值为: {c}")