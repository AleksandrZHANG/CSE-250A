from math import log
tokenfile=open("C:/vocab.txt","r")
unigramfile=open("C:/unigram.txt","r")
bigramfile=open("C:/bigram.txt","r")
tokenlist=[]
tokencount=[]
totalcount=0
for token in tokenfile.readlines():
    token=token.strip()
    tokenlist.append(token)
for count in unigramfile.readlines():
    count=int(count.strip())
    totalcount+=count
    tokencount.append(count)
#a
for i in range (0,500):
    if tokenlist[i].startswith("B")==True:
        print(tokenlist[i],tokencount[i]/totalcount)
print('\n')
#b
index1=[]
index2=[]
bicount=[]
key=[]
value=[]
b=[]
count=0
onecount=0
index=tokenlist.index("ONE")
for line in bigramfile.readlines():
    line=line.split('\t')
    index1.append(int(line[0])-1)
    index2.append(int(line[1])-1)
    bicount.append(int(line[2]))
    count+=1
for i in range (0,count):
    if index1[i]==index:
        onecount+=bicount[i]
        key.append(index2[i])
        value.append(bicount[i])     
b=map(lambda x,y:(x,y),key,value)
resb=sorted(list(b),key=lambda x:x[1],reverse=True)
for i in range(0,10):
    print(tokenlist[list(resb)[i][0]],list(resb)[i][1]/onecount)
print('\n')
#c
lu=1
lb=1
tokenclist=['<s>']
strc="The stock market fell by one hundred points last week"
tokenc=strc.upper().strip('\n').split(' ')
for token in tokenc:
    tokenclist.append(token)
    for i in range (0,500):
        if token==tokenlist[i]:
            lu*=tokencount[i]/totalcount
print(log(lu))
for j in range(0,len(tokenclist)-1):
    lukey=[]
    luvalue=[]
    for i in range (0,count):
        if index1[i]==tokenlist.index(tokenclist[j]):
            lukey.append(index2[i])
            luvalue.append(bicount[i])
    index3=tokenlist.index(tokenclist[j+1])
    lb*=luvalue[lukey.index(index3)]/tokencount[tokenlist.index(tokenclist[j])]
print(log(lb))
print('\n')
#d
lu=1
lb=1
tokendlist=['<s>']
e1=[]
e2=[]
strd="The fourteen officials sold fire insurance"
tokend=strd.upper().strip('\n').split(' ')
for token in tokend:
    tokendlist.append(token)
    for i in range (0,500):
        if token==tokenlist[i]:
            lu*=tokencount[i]/totalcount
            e1.append(tokencount[i]/totalcount)
print(e1)
print(log(lu))
message=","
message2="are not observed in the training corpus"
for j in range(0,len(tokendlist)-1):
    lukey=[]
    luvalue=[]
    done=0
    for i in range (0,count):
        if index1[i]==tokenlist.index(tokendlist[j]):
            lukey.append(index2[i])
            luvalue.append(bicount[i])
    index3=tokenlist.index(tokendlist[j+1])
    if not index3 in lukey:
        print(tokendlist[j],message,tokendlist[j+1],message2)
        continue
    lb*=luvalue[lukey.index(index3)]/tokencount[tokenlist.index(tokendlist[j])]
print(e2)
