//Complexitate O(N*M)
//N-numar varfuri
//M-numar muchii
//Folosim algoritmul Edmonds-Karp
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
#define INF 9999999
//lista de adiacenta in care luam in calcul si arcele inverse
vector<vector<int>>adj;
int capacity[202][202];
int tata[202];
int n;
//rulam un bfs pentru a afla un lant de la nodul de inceput la nodul final cu flux maxim
int bfs(){
    queue<pair<int,int>> q;
    for(int i=0;i<=2*n+1;i++){
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
                if(v==2*n+1)
                    return new_flow;
                q.push({v,new_flow});
            }
        }
    }
    return 0;
}
int main() {
    int x,y,i,j,flow,maxflow=0;
    ifstream cin("harta.in");
    ofstream cout("harta.out");
    cin>>n;
    adj.resize(2*n+2);
    //varfurile 1,2,..,n se pun in ambele clase ale bipartitiei (cate o copie)
    for(i=1;i<=n;i++){
        cin>>x>>y;
        //adaugam muchii (0,i) cu capacitatea x
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i]=x;
        //adaugam muchii (n+i,2*n+1) cu capacitatea y
        capacity[n+i][2*n+1]=y;
        adj[n+i].push_back(2*n+1);
        adj[2*n+1].push_back(n+i);
        for(j=n+1;j<=2*n;j++){
            //adaugam muchii (i,j) cu i diferit de j si cu capacitatea 1
            if(j-i==n)
                continue;
            capacity[i][j]=1;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    while(flow=bfs()){
        maxflow+=flow;
        int cur=2*n+1;
        //revizuim flux lant
        while(cur!=0){
            int prev=tata[cur];
            capacity[cur][prev]+=flow;
            capacity[prev][cur]-=flow;
            cur=prev;
        }
    }
    cout<<maxflow<<'\n';
    for(i=1;i<=n;i++)
        for(j=n+1;j<=2*n;j++)
            if(capacity[j][i]==1){
                cout<<i<<" "<<j-n<<'\n';
            }

    cin.close();
    cout.close();
}
