//folosim un vector distanta care are toate elementele egale cu -1 mai putin cele 2 puncte de control care au valoarea 0
//parcurgem fiecare nod si vecinii lui
//daca un vecin are valoarea in vectorul distanta diferita de -1 atunci:
//daca nodul are valoarea -1 in dist, atunci va primi valoarea vecinului+1
//daca nodul nu are valoarea -1 in dist, dar valoarea vecinului+1 este mai mica decat valoarea sa,atunci va primi valoarea vecinului+1
//repetam pana cand nu mai exista valoarea -1 in dist
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    int n,m,u,v,i,j,p1,p2,sem=-1;
    ifstream cin("graf.in");
    ofstream cout("graf.out");
    vector<vector<int>> adj;
    vector<int> dist;
    cin>>n;
    cin>>m;
    adj.resize(n+1);
    dist.resize(n+1,-1);

    for(i=1;i<=m;i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin>>p1>>p2;
    dist[p1]=0;
    dist[p2]=0;

    while(sem==-1){
        sem=0;
        for(i=1;i<=n;i++)
            for(j=0;j<adj[i].size();j++){
                if(dist[adj[i][j]]!=-1){
                    if(dist[i]==-1 || dist[i]>dist[adj[i][j]]+1)
                        dist[i]=dist[adj[i][j]]+1;
                }
                if(dist[i]==-1)
                    sem=-1;
            }
    }
    for(i=1;i<=n;i++)
        cout<<dist[i]<<" ";

}
