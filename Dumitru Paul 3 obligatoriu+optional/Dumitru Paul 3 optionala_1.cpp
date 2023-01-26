//Complexitate O(n*m^2*logn)
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;
#define INF 999999
vector<vector<int>>adj;
vector<int>dist_B;
vector<int>dist;
vector<int>dist_r;
vector<int>tata;
unordered_map<int,bool>viz;
int capacity[351][351];
int cost[351][351];
int n,m,s,d;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
//efectuam bellman-ford(avem costuri negative) si retinem valorile obtinute in vectorul distanta_B
void bellmanford(){
    queue<int>q;
    q.push(s);
    dist_B[s]=0;
    while(!q.empty()){
        int u=q.front();
        viz[u]=0;
        q.pop();
        for(auto v:adj[u]){
            if(capacity[u][v]>0)
                if(dist_B[u]+cost[u][v]<dist_B[v]){
                    dist_B[v]=dist_B[u]+cost[u][v];
                    if(viz[v]==0){
                        viz[v]=1;
                        q.push(v);
                    }
                }

        }
    }
}
//atribuim fiecarei muchii valoarea  distanta_B[x] + cost[x][y] - distanta_B[y] pentru a avea valori pozitive
bool dijkstra(){
    int i,c,u;
    for(i=1;i<=n;i++)
        dist[i]=INF;

    dist[s]=0;
    dist_r[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        c=pq.top().first;
        u=pq.top().second;
        pq.pop();
        if(dist[u]==c){
            for(auto v:adj[u]){
                if(capacity[u][v]>0 && dist[u]+dist_B[u]+cost[u][v]-dist_B[v]<dist[v]){
                    dist[v]=dist[u]+dist_B[u]+cost[u][v]-dist_B[v];
                    dist_r[v]=dist_r[u]+cost[u][v];
                    //pastram si costul real al parcurgerii
                    pq.push({dist[v],v});
                    tata[v]=u;
                }

            }
        }
    }
    return dist[d]!=INF;
}
int main() {
    int i,x,y,c,z,maxflow=0,flow;
    ifstream cin("fmcm.in");
    ofstream cout("fmcm.out");
    cin>>n>>m>>s>>d;
    adj.resize(n+1);
    dist.resize(n+1);
    dist_B.resize(n+1,INF);
    dist_r.resize(n+1);
    tata.resize(n+1);

    for(i=1;i<=m;i++){
        cin>>x>>y>>c>>z;
        adj[x].push_back(y);
        adj[y].push_back(x);
        capacity[x][y]=c;
        cost[x][y]=z;
        cost[y][x]=-z;
    }
    bellmanford();

    while(dijkstra()){
        int u,prev;
        flow=INF;
        u=d;
        while(u!=s){
            prev=tata[u];
            flow=min(flow,capacity[prev][u]);
            u=prev;
        }
        u=d;
        while(u!=s){
            prev=tata[u];
            capacity[u][prev]+=flow;
            capacity[prev][u]-=flow;
            u=prev;
        }
        maxflow+=flow*dist_r[d];
    }
    cout<<maxflow;
    cin.close();
    cout.close();
}
