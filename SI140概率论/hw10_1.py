import numpy as np

# Number of samples
num_samples = 5000

# Function to compute N for a single sample
def compute_N():
    product = 1
    n = 0
    while product >= np.exp(-1):
        u = np.random.uniform(0, 1)

        product *= u
        n += 1
    return n - 1  # N is the largest n where the product >= e^{-1}

# Generate 5000 samples of N
samples_N = [compute_N() for _ in range(num_samples)]

# Estimate E(N) as the sample mean
mean_N = np.mean(samples_N)
print(f"Estimated E(N): {mean_N}")
var_N = np.var(samples_N, ddof=1)  # Use ddof=1 for unbiased estimator
print(f"Estimated Var(N): {var_N}")
prob_N={}
for i in range(4):
    prob_N[i]= np.mean(np.array(samples_N) == i)

for i in range(4):
    print(f"Estimated P(N = {i}): {prob_N[i]}")