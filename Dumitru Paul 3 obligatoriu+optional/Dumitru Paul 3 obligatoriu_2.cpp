//Complexitate O(n*m)
//Folosim algoritmul Edmonds-Karp

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
#define INF 9999999
//lista de adiacenta in care luam in calcul si arcele inverse
vector<vector<int>>adj;
int capacity[20002][20002];
int tata[20002];
int n,m;
//rulam un bfs pentru a afla un lant de la nodul de inceput la nodul final cu flux maxim
int bfs(){
    queue<pair<int,int>> q;
    for(int i=0;i<=n+m+1;i++){
        tata[i]=-1;
    }
    q.push({0,INF});
    tata[0]=-2;
    while(!q.empty()){
        int u=q.front().first;
        int flow=q.front().second;
        q.pop();
        for(auto v:adj[u]){
            if(tata[v]==-1 && capacity[u][v]>0){
                tata[v]=u;
                //calculam flow-ul maxim pe lant
                int new_flow=min(flow,capacity[u][v]);
                //daca am atins ultimul nod returnam flow-ul maxim pe lant
                if(v==n+m+1)
                    return new_flow;
                q.push({v,new_flow});
            }
        }
    }
    return 0;
}
int main() {
    int x,y,i,j,flow,maxflow=0,e;
    ifstream cin("cuplaj.in");
    ofstream cout("cuplaj.out");
    cin>>n>>m>>e;
    adj.resize(n+m+2);
    for(i=1;i<=e;i++){
        cin>>x>>y;
        //adaugam 2 noduri 0 si n+m+1
        //adaugam muchii de la 0 la x si de la y+n la n+m+1
        //adaugam muchii de la x la y+n
        //asociem fiecarui arc de la 0 la x,de la y+n la n+m+1 si de la x la y+n capacitatea 1
        adj[0].push_back(x);
        adj[x].push_back(0);
        capacity[0][x]=1;
        capacity[y+n][n+m+1]=1;
        adj[y+n].push_back(n+m+1);
        adj[n+m+1].push_back(y+n);

        adj[x].push_back(y+n);
        adj[y+n].push_back(x);
        capacity[x][y+n]=1;
    }
    while(flow=bfs()){
        maxflow+=flow;
        //revizuim flux lant
        int cur=n+m+1;
        while(cur!=0){
            int prev=tata[cur];
            capacity[cur][prev]+=flow;
            capacity[prev][cur]-=flow;
            cur=prev;
        }
    }
    cout<<maxflow<<'\n';
    for(i=1;i<=n;i++)
        for(j=n+1;j<=n+m;j++)
            if(capacity[j][i]==1){
                cout<<i<<" "<<j-n<<'\n';
            }

    cin.close();
    cout.close();
}
