import matplotlib.pyplot as plt
import sys

E_in = []

N = 1126
LN = []
for i in range(N):
    E_in.append(float(input()))

sum = 0.0
for i in range(N):
    sum += E_in[i]

sum /= N

plt.hist(E_in)
plt.title(f"average E_in gain: {sum}")
plt.savefig(sys.argv[1])
