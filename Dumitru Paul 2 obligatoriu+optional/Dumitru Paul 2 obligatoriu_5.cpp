//Algoritmul lui Dijkstra
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include<queue>
using namespace std;
int main() {
    int n,m,k,i,nr,x,y,z;
    vector <int> nk;
    vector <int> str;
    vector <int> d;
    vector <int> t;
    vector <bool> viz;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> queue;
    vector<vector<pair<int,int>>> adj;
    ifstream cin("catun.in");
    ofstream cout("catun.out");
    cin>>n>>m>>k;
    viz.resize(n+1,false);
    d.resize(n+1,INT_MAX);
    str.resize(n+1);
    t.resize(n+1,0);
    adj.resize(n+1);
    for(i=1;i<=k;i++){
        cin>>nr;
        d[nr]=0;
        queue.push({0,nr});
        str[nr]=nr;
    }
    for(i=1;i<=m;i++){
        cin>>x>>y>>z;
        adj[x].push_back({z,y});
        adj[y].push_back({z,x});
    }
    while(!queue.empty()){
        int dist=queue.top().first;
        int nod=queue.top().second;
        viz[nod]=true;
        queue.pop();
        for(auto x : adj[nod]){
            if(viz[x.second]==false && dist+x.first<d[x.second]){
                d[x.second]=dist+x.first;
                str[x.second]=str[nod];
                queue.push({d[x.second],x.second});
            }
            else if(viz[x.second]==false && dist+x.first==d[x.second]){
                str[x.second]=min(str[x.second],str[nod]);
            }
        }
    }
    for(i=1;i<=n;i++){
        if(str[i]==i)
            str[i]=0;
        cout<<str[i]<<" ";
    }
}
