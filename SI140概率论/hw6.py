import numpy as np
import matplotlib.pyplot as plt
def inverse_logistic1(y):
    return np.log(y / (1 - y))
y=np.random.rand(1000)
x=inverse_logistic1(y)
plt.hist(x, density=True, alpha=0.6, color='g')
x_pdf = np.linspace(-10, 10, 1000)#从-10到10生成1000个
pdf = np.exp(x_pdf) / (1 + np.exp(x_pdf))**2
plt.plot(x_pdf, pdf, 'r', lw=2)
plt.title('Logistic Distribution')
plt.show()

def inverse_rayleigh(y):
    return np.sqrt(-2*np.log(1-y))
y=np.random.rand(1000)
x=inverse_rayleigh(y)
plt.hist(x,density=True,alpha=0.6,color='g')
x_pdf = np.linspace(0, 5, 1000)
pdf = x_pdf * np.exp(-x_pdf**2 / 2)
plt.plot(x_pdf, pdf, 'r', lw=2)
plt.show()

def inverse_expo(y):
    return -np.log(1-y)
y=np.random.rand(1000)
x=inverse_expo(y)
plt.hist(x,density=True,alpha=0.6,color='g')
x_pdf = np.linspace(0, 6, 1000)
pdf=np.exp(-x_pdf)
plt.plot(x_pdf, pdf, 'r', lw=2)
plt.show()