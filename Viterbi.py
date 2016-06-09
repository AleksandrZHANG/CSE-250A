import numpy as np
import sys
import matplotlib.pyplot as plt

def readfile(file):
	x = []
	for line in open(file):
		line = line.split()
		for i in range(len(line)):
			x.append(float(line[i]))
	return np.array(x)

a = readfile("C:/transitionMatrix.txt").reshape(26, 26)
b = readfile("C:/emissionMatrix.txt").reshape(26, 2)
o = readfile("C:/observations.txt")
pi = np.array([float(line) for line in open("C:/initialStateDistribution.txt")])

l = np.zeros((26, len(o)), dtype=float)
l[:,0] = np.log(pi) + np.log(b[:,o[0]])
for t in range(0, len(o)-1):
	for j in range(26):
		l[j][t+1] = max(l[:,t] + np.log(a[:,j])) + np.log(b[j][o[t-1]])

s = np.zeros(len(o), dtype=float)
s[0] = np.argmax([l[i][0] for i in range(26)])
for t in range(1, len(o)):
	s[-t] = np.argmax(l[:,-t] + np.log(a[:,s[1-t]]))
s += 1

plt.plot(s)
plt.xlabel('time')
plt.ylabel('hidden states')
plt.ylim(0,26)
plt.show()
