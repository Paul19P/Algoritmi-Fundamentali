//folosim algoritm clasic de dfs si cautam urmatorul nod din permutare, daca il gasim aplicam recursiv functia dfs
//pana cand indexul elementului pe care l cautam este mai mare decat n

#include <iostream>
#include <vector>
using namespace std;
vector<int> perm;
vector<int> visited;
vector<vector<int>> adj;

int n,m,ok=1,indexurm;

void DFS(int node){
    int sem=0,gasiturm=0,i;

    visited[node]=1;
    for(i=0;i<adj[node].size();i++){
        if(adj[node][i]==perm[indexurm]){
            i=-1;
            gasiturm=1;
            indexurm++;
            if(indexurm>n)
                return;
            DFS(perm[indexurm - 1]);
        }
        else if(visited[adj[node][i]]==0)
            sem=1;

    }
    if(gasiturm==0 && sem==1)
        ok=0;

}

int main() {
    int i,u,v;
    cin>>n>>m;
    perm.resize(n+1);
    visited.resize(n+1,0);
    adj.resize(n+1);
    for(i=1;i<=n;i++)
        cin>>perm[i];
    for(i=1;i<=m;i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    indexurm=2;
    DFS(1);
    if(indexurm>n && ok==1)
        cout<<1;
    else
        cout<<0;

}
