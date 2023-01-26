//Complexitate O(n*m^2)
//Folosim algoritmul lui Edmonds-Karp
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAXN 1001
#define INF 999999
using namespace std;
//capacitatea reziduala
int capacity[MAXN][MAXN];
//capacitatea initiala
int capacityin[MAXN][MAXN];
vector<pair<int,int>>taietura_minima;
int n;
//lista de adiacenta pentru graful dat in care luam in calcul si muchiile inverse
vector<vector<int>>adj;
//rulam un bfs pentru a afla un lant de la nodul de inceput la nodul final cu flux maxim
int bfs(int s,int f,vector<int>&parent){
    fill(parent.begin(),parent.end(),-1);
    taietura_minima.clear();
    queue<pair<int,int>> q;
    parent[s]=-2;
    q.push({s,INF});
    while(!q.empty()){
        int cur=q.front().first;
        int flow=q.front().second;
        q.pop();
        for(auto el:adj[cur]){
            if(parent[el]==-1 && capacity[cur][el]){
                parent[el]=cur;
                //calculam flow-ul maxim pe lant
                int new_flow=min(flow,capacity[cur][el]);
                //daca nodul atins e cel final returnam flow-ul maxim pe lant
                if(el==f)
                    return new_flow;
                q.push({el,new_flow});
            }
            else if(parent[el]==-1 && capacity[cur][el]==0)
                taietura_minima.push_back({cur,el});
        }
    }
    return 0;
}
int max_flow(int source,int sink){
    int maxflow=0;
    vector<int>parent(n+1);
    int flow;
    while(flow=bfs(source,sink,parent)){

        maxflow+=flow;
        int cur=sink;
        //revizuiesc flux lant
        while(cur!=source){
            int prev=parent[cur];
            capacity[cur][prev]+=flow;
            capacity[prev][cur]-=flow;
            cur=prev;
        }
    }
    return maxflow;
}
int main() {
    int m,u,v,c,i,mx;
    ifstream cin("maxflow.in");
    ofstream cout("maxflow.out");
    cin>>n>>m;
    adj.resize(n+1);
    for(i=1;i<=m;i++){
        cin>>u>>v>>c;
        capacity[u][v]=c;
        capacityin[u][v]=c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    mx=max_flow(1,n);
    cout<<mx<<'\n';
    for(auto x:taietura_minima)
        cout<<x.first<<" "<<x.second<<'\n';
    cin.close();
    cout.close();
}
