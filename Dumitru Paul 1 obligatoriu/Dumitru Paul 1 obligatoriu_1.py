#verificam daca graful este bipartit
#folosim un vector de culori care initial are toate valorile egale cu -1
#parcurgem fiecare nod si verificam daca este "colorat" sau nu
#daca nu este colorat il coloram cu rosu (0) apoi mergem in toti vecinii lui si verificam:
#1. daca vecinul are aceeasi culoare, graful nu este bipartit
#2. daca vecinul nu este colorat, ii dam culoarea opusa si il adaugam in queue
#eliminam prima pereche din queue si procedam la fel ca in pasii anteriori pana cand queue-ul este gol
#O(n+m)
def isbipartite(n,adj):
    col=[-1]*(n+1)

    q=[]

    for i in range(1,n+1):
        if col[i]==-1:
            col[i]=0;
            q.append([i,0])
            while len(q)!=0:
                p=q[0]
                q.pop(0)

                v=p[0]
                c=p[1]
                for j in adj[v]:
                    if col[j]==c:
                        return False
                    if col[j]==-1:
                        if c==0:
                            col[j]=1
                        elif c==1:
                            col[j]=0
                        q.append([j,col[j]])
    return col


n=4
dislikes=[[1,2],[1,3],[2,4]]
adj=[[] for i in range(n+1)]
for u,v in dislikes:
    adj[u].append(v)
    adj[v].append(u)

ans=isbipartite(n,adj)
ls=[[],[]]
if ans==False:
    print(ans)
else:
    print(True)
    for i in range(1,len(ans)):
        if ans[i]==0:
            ls[0].append(i)
        else:
            ls[1].append(i)
    print(ls)

