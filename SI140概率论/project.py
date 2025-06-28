import numpy as np
import matplotlib.pyplot as plt
#from scipy.stats import beta

def reward(theta_j):
    if np.random.rand()<theta_j:
        return 1
    else:
        return 0
N=5000
oracle=[0.7,0.5,0.4]
def epsilon_greedy(theta,N,eps=0.5):
    total=0
    num=len(theta)
    theta_head=[0]*num
    count = [0] * num
    for t in range(N):
        if np.random.rand() >= eps:#生成（0，1）随机数
            I_t = np.argmax(theta_head)
        else:
            I_t = np.random.randint(num)
        count[I_t] += 1
        r = reward(theta[I_t])
        theta_head[I_t] += (r - theta_head[I_t]) / count[I_t]
        total+= r
        
    return total
epsil=[0.3,0.6,0.9]
for eps in epsil:
    reward1=epsilon_greedy( oracle,N, eps)
    
    print (f"Epsilon-greedy Algorithm with eps = {eps}:{reward1} ;")
    
print()
# Upper Confidence Bound Algorithm
def UCB(theta,N, c=1):
    total = 0
    num = len(theta)
    count = [1] * num
    theta_head = [reward(theta[i]) for i in range(num)]
    for t in range(4, N+1):
        I_t = np.argmax([theta_head[j] + c * np.sqrt(2 * np.log(t) / count[j]) for j in range(num)])
        count[I_t] += 1
        r = reward(theta[I_t])
        total += r
        theta_head[I_t] += (r - theta_head[I_t]) / count[I_t]
        
    return total
C = [3, 6, 9]
for c in C:
    reward2=UCB(oracle,N, c)
    print (f"Upper Confidence Bound Algorithm with c = {c}: {reward2};")
print()
def Thompson(theta,N,  alpha0, beta0):
    total= 0
    num = len(theta)
    alpha = alpha0.copy()
    beta = beta0.copy()
    for t in range(N):

        I_t = np.argmax([np.random.beta(alpha[i], beta[i]) for i in range(num)])
        r = reward(theta[I_t])
        total+= r
        alpha[I_t] += r
        beta[I_t] += 1 - r
    return total

    


alphas = [[1, 1, 1], [601, 401, 2]]
betas = [[1, 1, 1], [401, 601, 3]]
for i in range(2):
    reward3=Thompson(oracle,N,  alphas[i], betas[i])
    print (f"Thompson Sampling Algorithm with alpha = {alphas[i]}, beta = {betas[i]}: {reward3};")



# trials = 200
# # Epsilon-greedy Algorithm

# for i in range(len(epsil)):
#     Ep=0
#     for _ in range(trials):
#         Ep+= epsilon_greedy( oracle,N, epsil[i])
#     Ep/=trials
#     delta1=np.abs(Ep-3500)
#     print(f"Epsilon-greedy Algorithm with eps = {epsil[i]}: {Ep};")
#     print(f"The gap of Epsilon-greedy Algorithm with eps = {epsil[i]}: {delta1};")
# print()
# # Upper Confidence Bound Algorithm
# for i in range(len(C)):
#     U=0
#     for _ in range(trials):
#         U+= UCB(oracle,N, C[i])
#     U/=trials
#     delta2=np.abs(U-3500)
#     print(f"Upper Confidence Bound Algorithm with c = {C[i]}: {U};")
#     print(f"The gap of Upper Confidence Bound Algorithm with c = {C[i]}: {delta2};")
# print()
# # Thompson Sampling Algorithm
# for i in range(len(betas)):
#     T=0
#     for _ in range(trials):
#         T+= Thompson(oracle,N, alphas[i],betas[i])
#     T/=trials
#     delta3=np.abs(T-3500)
#     print(f"Thompson Sampling Algorithm with alpha = {alphas[i]}, beta = {betas[i]}: {T};")
#     print(f"The gap of Thompson Sampling Algorithm with alpha = {alphas[i]}, beta = {betas[i]}: {delta3};")
# print()

#4.2
import matplotlib.pyplot as plt

# 假设 epsilon_greedy 是一个已经定义的函数
trials = 200
epss = [0.1 * i for i in range(11)]
gap_epsil = [0] * len(epss)

# 计算平均 Gap
for _ in range(trials):
    for i in range(len(epss)):
        gap_epsil[i] += epsilon_greedy(oracle, N, epss[i])

# 计算平均值
gap_epsil = [3500 - gap / trials for gap in gap_epsil]

# 绘图
plt.figure(figsize=(8, 6))  # 设置图表大小
plt.plot(epss, gap_epsil, marker='o', linestyle='-', color='b', label='Gap vs Epsilon')

# 标注每个点的数值
for i, (x, y) in enumerate(zip(epss, gap_epsil)):
    plt.annotate(f"{y:.2f}",  # 标注的文本，保留两位小数
                 xy=(x, y),  # 标注的点
                 xytext=(x, y + 50),  # 标注文本的位置（稍微偏移）
                 ha='center',  # 水平对齐方式
                 va='bottom',  # 垂直对齐方式
                 fontsize=9,  # 字体大小
                 arrowprops=dict(arrowstyle='-', color='gray'))  # 箭头样式

plt.xlabel("Epsilon", fontsize=12)
plt.ylabel("Gap", fontsize=12)
plt.title("Gap vs Epsilon", fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)
plt.tight_layout()  # 自动调整布局
plt.show()


C= [0, 0.1, 0.3, 0.5, 0.7, 0.9, 2, 6, 10]
gap_UCB = [0] * len(C)
for _ in range(trials):
    for i in range(len(C)):
        gap_UCB[i] += UCB(oracle,N,  C[i])
gap_UCB = [3500 - it / trials for it in gap_UCB]
plt.plot(C, gap_UCB, marker='o', linestyle='-', color='b', label='Gap vs Epsilon')

# 标注每个点的数值
for i, (x, y) in enumerate(zip(C, gap_UCB)):
    plt.annotate(f"{y:.2f}",  # 标注的文本，保留两位小数
                 xy=(x, y),  # 标注的点
                 xytext=(x, y + 50),  # 标注文本的位置（稍微偏移）
                 ha='center',  # 水平对齐方式
                 va='bottom',  # 垂直对齐方式
                 fontsize=9,  # 字体大小
                 arrowprops=dict(arrowstyle='-', color='gray'))  # 箭头样式

plt.xlabel("c", fontsize=12)
plt.ylabel("Gap", fontsize=12)
plt.title("Gap vs c", fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)
plt.tight_layout()  # 自动调整布局
plt.show()


alphas = [[7,7, 7], [7, 7, 7], [7, 7, 7], [88, 99, 120], [1, 1, 1]]
betas = [[32, 33, 11], [91, 11, 51], [3, 7, 11], [40, 105, 190], [1, 1, 1]]
gap_TS = [0] * len(alphas)
for _ in range(trials):
    for i in range(len(alphas)):
        gap_TS[i] += Thompson(oracle,N,  alphas[i], betas[i])
gap_TS = np.abs([3500 - it / trials for it in gap_TS])


x_labels = [f"({alphas[i]}, {betas[i]})" for i in range(len(alphas))]

# 绘图
plt.figure(figsize=(10, 6))  # 设置图表大小
plt.plot(range(len(alphas)), gap_TS, marker='o', linestyle='-', color='b', label='Gap vs Alpha/Beta')
for i, (x, y) in enumerate(zip(range(len(alphas)), gap_TS)):
    plt.annotate(f"{y:.2f}",  # 标注的文本，保留两位小数
                 xy=(x, y),  # 标注的点
                 xytext=(x, y + 50),  # 标注文本的位置（稍微偏移）
                 ha='center',  # 水平对齐方式
                 va='bottom',  # 垂直对齐方式
                 fontsize=9,  # 字体大小
                 arrowprops=dict(arrowstyle='-', color='gray'))  # 箭头样式

plt.xlabel("Alpha/Beta Combinations", fontsize=12)
plt.ylabel("Gap", fontsize=12)
plt.title("Gap vs Alpha/Beta Combinations", fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.xticks(range(len(alphas)), x_labels, rotation=45, fontsize=10)  # 设置 x 轴标签
plt.yticks(fontsize=10)
plt.tight_layout()  # 自动调整布局
plt.show()