import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import multivariate_normal
from mpl_toolkits.mplot3d import Axes3D
def generate_bivariate_normal(rho, n_samples=10000):
    Z=np.random.normal(0,1,n_samples)
    W=np.random.normal(0,1,n_samples)
    X=Z
    Y=rho*Z+np.sqrt(1-rho**2)*W
    return X,Y

def plot_bivariate_normal(rho):
    X, Y = generate_bivariate_normal(rho)

    mean = [0, 0]
    cov = [[1, rho], [rho, 1]]

    x, y = np.mgrid[-3:3:.01, -3:3:.01]
    pos = np.dstack((x, y))
    rv = multivariate_normal(mean, cov)
    pdf = rv.pdf(pos)

    fig = plt.figure(figsize=(12, 6))
# Subplot 1: 3D Surface Plot
    ax1 = fig.add_subplot(1, 2, 1, projection='3d')
    ax1.plot_surface(x, y, pdf, cmap='viridis', alpha=0.8)
    ax1.set_title(f'3D Joint PDF (ρ = {rho})')
    ax1.set_xlabel('X')
    ax1.set_ylabel('Y')
    ax1.set_zlabel('PDF')
    
    # Subplot 2: Contour Plot
    ax2 = fig.add_subplot(1, 2, 2)
    ax2.contour(x, y, pdf, levels=20, colors='black')
    ax2.scatter(X, Y, s=1, alpha=0.1, color='red')
    ax2.set_title(f'Contour Plot (ρ = {rho})')
    ax2.set_xlabel('X')
    ax2.set_ylabel('Y')
    plt.show()
plot_bivariate_normal(rho=-0.8)
plot_bivariate_normal(rho=-0.4)
plot_bivariate_normal(rho=0)
plot_bivariate_normal(rho=0.4)
plot_bivariate_normal(rho=0.8)