//Folosim algoritmul Edmonds-Karp
//Complexitate O(n*m^2)
// Dublam nodurile si construim 2 multimi. Avem un nod sursa care duce in orice nod din prima multime si
// arce din a doua multime care duc in nodul de destinatie
// Avem muchiile date din input dar si cele 2 multimi sunt legate intre ele
// Calculam fluxul maxim care o sa ne dea cuplajul maxim, raspunsul fiind n - cuplajul maxim
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#define INF 999999
vector<vector<int>>adj;
vector<int>tata;
int capacity[202][202],n;
//rulam bfs pentru a afla un lant de la nodul 0 la 2*n+1 cu flux maxim
int bfs(){
    int i,flow,u;
    for(i=0;i<=2*n+1;i++){
        tata[i]=-1;
    }
    tata[0]=-2;
    queue<pair<int,int>>q;
    q.push({0,INF});
    while(!q.empty()){
        u = q.front().first;
        flow = q.front().second;
        q.pop();
        for(auto v:adj[u])
            if(tata[v]==-1 && capacity[u][v]){
                tata[v]=u;
                int new_flow=min(flow,capacity[u][v]);
                if(v==2*n+1)
                    return new_flow;
                q.push({v,new_flow});
            }
    }
    return 0;
}
int main() {
    int m,u,v,i,flow,maxflow=0;
    ifstream cin("drumuri2.in");
    ofstream cout("drumuri2.out");
    cin>>n>>m;
    adj.resize(2*n+2);
    tata.resize(2*n+2);
    for(i=1;i<=m;i++){
        cin>>u>>v;
        capacity[u][n+v]=1;
        adj[u].push_back(n+v);
        adj[v+n].push_back(u);
    }
    for(i=1;i<=n;i++){
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i]=1;

        adj[n+i].push_back(2*n+1);
        adj[2*n+1].push_back(n+i);
        capacity[n+i][2*n+1]=1;

        adj[n+i].push_back(i);
        adj[i].push_back(n+i);
        capacity[n+i][i]=1;
    }
    while(flow=bfs()){
        maxflow+=flow;
        u=2*n+1;
        //revizuim fluxul
        while(u!=0){
            int prev=tata[u];
            capacity[u][prev]+=flow;
            capacity[prev][u]-=flow;
            u=prev;
        }
    }
    cout<<n-maxflow;
    cin.close();
    cout.close();
}
