#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int tata[2002], capacity[2002][2002];
vector<vector<int>>adj;
#define INF 9999999
int n, x;
bool BFS() {
    queue<pair<int,int>>q;
    for (int i = 1; i <= 2 * n + 1; i++)
        tata[i] = -1;
    q.push({0,INF});
    tata[0] = -2;
    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (auto v : adj[u])
            if (capacity[u][v] > 0 and tata[v] == -1)
            {
                int new_flow = min (flow,capacity[u][v]);
                q.push({v,new_flow});
                tata[v] = u;
                if (v == 2 * n + 1)
                    return new_flow;
            }
    }
    return 0;
}

int main() {
    cin >> n;
    adj.resize(2 * n + 2);
    for(int i=1;i<=n;i++)
        for (int j = 1; j <= n; j++) {
            cin >> x;
            if (x == 1)
            {
                adj[i].push_back(n + j);
                adj[n + j].push_back(i);
                capacity[i][n + j] = 1;
            }
        }
    for (int i = 1; i <= n; i++)
    {
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = 1;

        adj[n + i].push_back(2 * n + 1);
        adj[2 * n + 1].push_back(n + i);
        capacity[n + i][2 * n + 1] = 1;
    }
    int total = 0,flow;
    while (flow=BFS()) {
            int v = 2 * n + 1;
            while (v != 0) {
                int prev=tata[v];
                capacity[prev][v] -= flow;
                capacity[v][prev] += flow;
                v = prev;
            }
            total += flow;
        }

    vector<int>poz;
    poz.resize(n+1);
    for(int i=1;i<=n;i++)
        for (int j = 1; j <= n; j++)
            if (capacity[n+j][i] != 0)
                poz[i]=j;
    if (total == n)
    {for(int i = 1; i <= n; i++)
        {if(poz[i]==i)
                continue;
            int loc=find(poz.begin()+1,poz.end(),i)-poz.begin();
            cout<<"R "<<i<<" "<<loc<<'\n';
            swap(poz[i],poz[loc]);

        }
    }
    else
        cout<<-1;

}