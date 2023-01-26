#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#define INF 999999
vector<vector<pair<int,int>>>adj;
vector<int>d;
vector<int>tata;
int n;
priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
//folosesc dijkstra pentru a calcula vectorul de distante apoi folosim un for care trece prin fiecare nod (i)
//si un for pentru fiecare vecin (j) al nodului (i) si verificam daca i nu e nodul de start daca i si j au tati diferiti
//si daca j nu e nodul de start sau i nu e vecin al nodului de start, daca da atunci distanta noua va fi
//distanta de la nodul de start pana la i + distanta de la i pana la j si distanta de la nodul de start pana la j
int dijkstra(int node){
    int dmin=INF,i;
    for(auto vecin:adj[node]){
        d[vecin.first]=vecin.second;
        tata[vecin.first]=vecin.first;
        q.push({vecin.second,vecin.first});
    }
    d[node]=0;
    while(!q.empty()){
        int distanta = q.top().first;
        int u = q.top().second;
        q.pop();
        for(auto v:adj[u]){
                if(d[v.first]>d[u]+v.second){
                    d[v.first]=d[u]+v.second;
                    tata[v.first]=tata[u];
                    q.push({d[v.first],v.first});
                }
        }

    }
    for(i=1;i<=n;i++) {
        if(i==node)
            continue;
        for (auto vecin: adj[i]) {
            int vecin_nod = vecin.first;
            int vecin_dist = vecin.second;
            if ((tata[vecin_nod] != tata[i]) && (vecin_nod!=node || tata[i] != i)) {
                int new_dist = d[i] + vecin_dist + d[vecin_nod];
                dmin = min(dmin, new_dist);
            }
        }
    }
    if(dmin==INF)
        return -1;
    else
        return dmin;
}
int main() {
    int m,i,x,y,z;
    ifstream cin("dbz.in");
    ofstream cout("dbz.out");
    cin>>n>>m;
    adj.resize(n+1);
    d.resize(n+1);
    tata.resize(n+1);
    for(i=1;i<=m;i++){
        cin>>x>>y>>z;
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
    }
    for(i=1;i<=n;i++){
        fill(d.begin(), d.end(),INF );
        fill(tata.begin(),tata.end(),0);
        int rezultat = dijkstra(i);
        cout<<rezultat<<" ";
    }
    cin.close();
    cout.close();
}
