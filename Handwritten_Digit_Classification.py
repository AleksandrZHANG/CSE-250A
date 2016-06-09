import math
import scipy
import numpy as np

def sigmoid(x):
    return 1/(1+math.exp(-x))

class solution:
    def __init__(self): 
        self.W = [0.6526628369680092, 0.81527277964517, 0.9961680092702808, 0.8501850674908034, 0.8898329804074784, 0.06982091824312708, -0.8344768475673042, -1.3635149043841677,
                  -0.1503993420519703, -0.18584462228414309, -0.21917396312143747, 0.16636516553974268, -0.08970053065517491, -0.38101138335958074, 0.6313921007993476, 0.48755541591485646,
                  -1.317751692590794, -1.041079511887651, -0.9478043872714474, -0.4919490677830601, -0.09507940858650174, 1.2851527054243588, 2.2716988196684476, 1.8951409720861112,
                  -1.11761772814048, -0.7243658211485774, -0.6889737218324673, 0.22456679008962507, 0.7208614386028115, 0.4782088289787898, -0.03996400482445781, 0.19575601645785703,
                  -0.26746209013255456, -0.21453679972572184, -0.030354827433074976, 0.28991902398113856, 0.33801326418906824, 0.38031434430713995, 0.21864328058879323, 0.38264263736372567,
                  -0.6617453211524243, 0.3613892812692179, -0.148810723777001, -0.40637659248573643, -0.2774334311721406, 0.14194371215984602, 0.1163194749499923, 0.9308540085230511,
                  -0.33050668078304835, -0.10952127431370988, -0.5303564904309094, -0.4117335103735285, -0.037559591284520216, 0.06414595729232994, -0.2926004391988237, 0.7326167228363266,
                  0.13465084281393, -0.3513378502991563, -0.48734649456714935, -0.8785273869066741, -0.34221766561844064, -0.4608139659387252, 0.18073428710004177, 0.21375158652092136] 
        self.X = []
        self.Y = []
        self.eta = 0

    def readfile(self):
        train3File = open('C:/newTrain3.txt', 'r')
        for line in train3File:
            s = line[:-1]
            self.X.append([int(i) for i in s.split()])
            self.Y.append(1)
        train5File = open('C:/newTrain5.txt', 'r')
        for line in train5File:
            s = line[:-1]
            self.X.append([int(i) for i in s.split()])
            self.Y.append(0)
        self.eta = 0.02/len(self.X)
        
    def gradientascent(self):
        delta = [0] * 64
        for j in range(64):
            gradient = 0
            for i in range(len(self.Y)):
                gradient += (self.Y[i] - sigmoid(np.dot(self.X[i],self.W)))*self.X[i][j]
            delta[j] = self.eta * gradient
        for i in range(64):
            self.W[i] += delta[i]

    def loglikelihood(self):
        res = 0
        for i in range(len(self.Y)):
            if self.Y[i]==0:
                res += math.log(1-sigmoid(np.dot(self.W,self.X[i])))
            else:
                res += math.log(sigmoid(np.dot(self.W,self.X[i])))
        return res

    def partA(self):
        self.readfile()
        for i in range (30000):
            self.gradientascent()
            if i%1000 == 0:
                print(self.loglikelihood())
        print (self.w)

    def partB(self):
        total = 0
        error = 0
        test3File = open('C:/newTest3.txt')
        for line in test3File:
            total += 1
            s = line[:-1]
            X = [int(i) for i in s.split()]
            if sigmoid(np.dot(X,W)) < 0.5:
                error += 1
        print (error/total)
        total = 0
        error = 0
        test5File = open('C:/newTest5.txt')
        for line in test5File:
            total += 1
            s = line[:-1]
            X = [int(i) for i in s.split()]
            if sigmoid(np.dot(X,W)) > 0.5:
                error += 1
        print (error/total)

if __name__ == '__main__':
    s = solution()
    s.partA()
    s.partB()
