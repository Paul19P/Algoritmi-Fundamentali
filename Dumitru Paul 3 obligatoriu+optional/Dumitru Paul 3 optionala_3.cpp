#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define INF 999999
int n, v[2001], capacity[2002][2002], tata[2002],viz[2002];
vector<vector<int>>adj;

bool prim(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int BFS() {
    queue<pair<int,int>>q;
    for (int i = 0; i <= n+1; i++){
        tata[i]=-1;
        viz[i]=0;
    }

    q.push({0,INF});
    while (!q.empty()) {
        int u = q.front().first;
        int flow=q.front().second;
        q.pop();
        for (auto v : adj[u]) {
            if (viz[v] == 0 && capacity[u][v] > 0) {
                tata[v] = u;
                int new_flow=min(flow,capacity[u][v]);
                q.push({v,new_flow});
                viz[v]=1;
                if (v == n+1) {
                    return new_flow;
                }
            }
        }
    }
    return 0;

}

int main() {
    cin >> n;
    adj.resize(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
        if (v[i] % 2)
        {
            adj[0].push_back(i);
            adj[i].push_back(0);
            capacity[0][i] = 1;
        }
        else
        {
            adj[i].push_back(n + 1);
            adj[n + 1].push_back(i);
            capacity[i][n + 1] = 1;
        }
    }

    for(int i=1;i<n;i++)			//Construim un graf bipartit in care nodurile cu valoare para reprezinta o submultime, iar cele cu val impara alta submultime
        for(int j=i+1;j<=n;j++)		//Facem acest lucru deoarece un numar prim se construieste din suma unui numar par cu unul impar
        {
            if (prim(v[i] + v[j])) {		//Problema se transforma intr-o problema de cuplaj maxim, astfel aflam numarul maxim de perechi de numere prime( fara sa se repete numere)
                adj[i].push_back(j);
                adj[j].push_back(i);
                if (v[i] % 2) {
                    capacity[i][j] = 1;
                }
                else {
                    capacity[j][i] = 1;
                }
            }
        }
    int maxflow = 0,flow;
    while(flow=BFS()){
            int u = n+1;
            while (u != 0) {
                int prev=tata[u];
                capacity[u][prev]+=flow;
                capacity[prev][u]-=flow;
                u=prev;
            }
            maxflow += flow;
        }

    cout << maxflow << "\n";
    for (int i = 1; i <= n; i++)
        if (v[i] % 2 && !viz[i] || v[i] % 2 == 0 && viz[i])		//Verificam daca toate numerele impare care puteau forma un numar prim si-au gasit pereche (eliminam impare)
            cout << v[i] << " ";									//Sau daca mai sunt numere impare care cauta o pereche (eliminam pare)
}

//Complexitate O(n*m^2)