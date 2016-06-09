from math import log

def noiseOR(X, Y, p):
    res = 1.0
    for i in range(23):
        res *= (1 - p[i])**int(X[i])
    if Y == 1:
        res = 1 - res
    return res

def loglikelihood(X, Y, p):
    res = 0.0
    for i in range(len(Y)):
        res += log(noiseOR(X[i], int(Y[i][0]), p))
    return res / len(Y)

iteration = [0,1,2,4,8,16,32,64,128,256]
p = [2/23] * 23
L = []
X = []
Y = []
fileX = open('C:/spectX.txt', 'r')
for line in fileX:
    X.append(line.split())
fileY = open('C:/spectY.txt', 'r')
for line in fileY:
    Y.append(line.split())

for k in range(257):
    if k in iteration:
        mistake = 0
        for j in range(len(X)):
            if Y[j][0] == '1':
                if noiseOR(X[j], 1, p) <= 0.5:
                    mistake += 1
            else:
                if 1 - noiseOR(X[j], 0, p) >= 0.5:
                    mistake += 1
        print (mistake)
    L.append(loglikelihood(X, Y, p))
    temp_p = []
    for i in range(23):
        count = 0
        temp = 0.0
        for j in range(len(X)):
            if X[j][i] == '1':
                count += 1
                if Y[j][0] == '1':
                    temp += p[i] / noiseOR(X[j], 1, p)
        temp_p.append(temp/count)
    p = list(temp_p)

for i in iteration:
    print (L[i])
# CSE-250A
