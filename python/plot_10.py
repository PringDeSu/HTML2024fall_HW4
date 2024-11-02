import matplotlib.pyplot as plt
import sys

E_in = []
E_out = []
E_lin_in = float(input())
E_lin_out = float(input())

N = 100000 // 200
LN = []
for i in range(N):
    E_in.append(float(input()))
for i in range(N):
    E_out.append(float(input()))
    LN.append(200 * i)

plt.scatter(LN, E_in, c = "r")
plt.scatter(LN, E_out, c = "b")
plt.axhline(y = E_lin_in, color = "orange")
plt.axhline(y = E_lin_out, color = "purple")
plt.savefig(sys.argv[1])
