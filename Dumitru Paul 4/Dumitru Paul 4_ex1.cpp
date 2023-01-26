#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;
int n;
vector<vector<pair<int, int>>> adj;
priority_queue<pair<int, int>>q;
vector<bool>viz;
#define INF 999999
int Dijkstra() {
    q.push({ INF,1 });
    while (!q.empty()) {
        int u = q.top().second;
        int greutate = q.top().first;
        viz[u] = 1;
        q.pop();
        if (u == n)
            return greutate;
        for (auto v : adj[u])
            if (viz[v.second] == 0)
                q.push({ min(greutate,v.first),v.second });
    }
    return 0;
}

int main() {

    int m,x,y,w;
    ifstream cin("transport2.in");
    ofstream cout("transport2.out");
    cin >> n >> m;
    adj.resize(n + 1);
    viz.resize(n+1,false);
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y>>w;
        adj[x].push_back({ w,y });
        adj[y].push_back({ w,x });
    }
    cout << Dijkstra();

    cin.close();
    cout.close();
}