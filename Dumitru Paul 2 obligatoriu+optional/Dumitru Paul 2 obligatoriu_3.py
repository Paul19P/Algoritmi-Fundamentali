#Iniţial fiecare obiect (cuvânt) formează o clasă
#La un pas determinăm cele mai asemănătoare (apropiate) două obiecteaflate în clase diferite (cu distanţacea mai mică între ele) şiunim clasele lor
#Repetămpână obținem k clase => n –k paşi

def lev_dis(cuv1,cuv2):
    c=[[0 for i in range(len(cuv2)+1)] for j in range(len(cuv1)+1)]
    for i in range(len(cuv1)+1):
        for j in range(len(cuv2)+1):
            if i==0:
                c[0][j]=j
            elif j==0:
                c[i][0]=i
            elif cuv1[i-1]==cuv2[j-1]:
                c[i][j]=c[i-1][j-1]
            else:
                c[i][j]=1+min(c[i-1][j],c[i][j-1],c[i-1][j-1])
    return c[len(cuv1)][len(cuv2)]

def init(u):
    r[u]=u

def reprez(u):
    return r[u]

def reuneste(u,v):
    r1=reprez(u)
    r2=reprez(v)
    for k in range(n):
        if r[k]==r2:
            r[k]=r1

with open("cuvinte.in","r") as file:
    x=file.read()
    cuvinte=x.split()
file.close()
n=len(cuvinte)
r=[0]*n
adj=[]

for i in range(n-1):
    for j in range(i+1,n):
        d=lev_dis(cuvinte[i],cuvinte[j])
        adj.append([i,j,d])

adj=sorted(adj,key= lambda x:x[2])
for i in range(n):
    init(i)

k=int(input("k="))

for i in range(1,n-k+1):
    j=0
    for u,v,c in adj:
        if r[u]!=r[v]:
            reuneste(u,v);
            last=[u,v,c]
            break
        j+=1

grad=adj[j+1][2]
dict={i:[] for i in range(max(r)+1)}
for i in range(len(r)):
    dict[r[i]].append(cuvinte[i])
with open("cuvinte.out","w") as file:
    for i in range(len(dict)):
        if dict[i]!=[]:
            for x in dict[i]:
                file.write(x+" ")
            file.write('\n')
    file.write(str(grad))
