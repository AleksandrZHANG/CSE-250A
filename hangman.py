# a
import string
num = 10
words = []
count = []
file = open("C:\hw1_word_counts_05.txt","r")
for line in file.readlines():
	word = line.strip('\n').split(' ')
	words.append(word[0])
	count.append(int(word[1]))
wordsnum = len(words)
sorti = sorted(range(wordsnum), key=lambda x: count[x], reverse=True)
print ("Ten Most Frequent 5-letter Words:")
for i in range(0, num):
	index = sorti[i]
	print (words[index], count[index])
print ("Ten Least Frequent 5-letter Words:")
for i in range(wordsnum - num, wordsnum):
	index = sorti[i]
	print (words[index], count[index])
# b
def guess(wordsnum, words, count, correct, wrong):
        sumCount = 0
        flag = []
        guessc = [0] * 26
        guessChar = string.ascii_uppercase
        for i in range(wordsnum):
                guessres = True
                word = words[i]
                for j in range(5):
                        if (correct[j] != '*' and correct[j] != word[j]) or (correct[j] == '*' and words[j] in correct):
                                guessres = False
                                break
                        if word[j] in wrong:
                                guessres = False
                                break
                if guessres:
                        sumCount += count[i]
                        flag.append(1)
                else:
                        flag.append(0)
        for i in range(wordsnum):
                if flag[i] == 0:
                        continue
                pr = float(count[i]) / sumCount
                for j in range(26):
                        if not (guessChar[j] in correct) and not (guessChar[j] in wrong) and (guessChar[j] in words[i]):
                                guessc[j] += pr
        prob = max(guessc)
        best = chr(65+guessc.index(prob))
        print (best, prob)
guess(wordsnum, words, count, '*****', [])
guess(wordsnum, words, count, '*****', ['E','A'])
guess(wordsnum, words, count, 'A***S', [])
guess(wordsnum, words, count, 'A***S', ['I'])
guess(wordsnum, words, count, '**O**', ['A','E','M','N','T'])
guess(wordsnum, words, count, 'D**I*', [])
