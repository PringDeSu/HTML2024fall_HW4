import matplotlib.pyplot as plt
import sys

E_out = []

N = 1126
LN = []
for i in range(N):
    E_out.append(float(input()))

sum = 0.0
for i in range(N):
    sum += E_out[i]

sum /= N

plt.xscale("symlog")
plt.hist(E_out, bins = [-1e16, -1e15, -1e14, -1e13, -1e12, -1e11, -1e10, -1e9, -1e8, -1e7])
plt.title(f"average E_out change: {sum}")
plt.savefig(sys.argv[1])
