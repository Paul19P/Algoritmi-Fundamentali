#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<vector<pair<int,int>>>adj;
vector<long long>dist;
vector<long long>d_subgraf;
vector<bool>viz;
int start;
void dfs(int u, long long timp)
{
    viz[u] = 1;
    if (u == start || adj[u].size() != 1) {
        for (auto v: adj[u]) {
            int nod=v.first;
            int t=v.second;
            if (viz[nod]==0) {
                dfs(nod, t+timp);
                d_subgraf[u] += min(d_subgraf[nod] + 2 * t, dist[nod] + timp + t);
                dist[u] = min(dist[u], dist[nod] + t -min(d_subgraf[nod] + 2 * t, dist[nod]+t+timp));
            }
        }
        dist[u] += d_subgraf[u];
    }
}

int main() {
    int n,k,x,y,z,i;
    ifstream cin("riremito.in");
    ofstream cout("riremito.out");
    cin>>n;
    adj.resize(n+1);
    dist.resize(n+1);
    d_subgraf.resize(n+1);
    viz.resize(n+1);
    for(i=1;i<=n-1;i++){
        cin>>x>>y>>z;
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
    }
    cin>>k;
    while(k>0){
        cin>>start;
        for(i=1;i<=n;i++){
            viz[i]=0;
            dist[i]=0;
            d_subgraf[i]=0;
        }
        dfs(start,0);
        cout<<dist[start]<<'\n';
        k--;
    }
    cin.close();
    cout.close();
}
