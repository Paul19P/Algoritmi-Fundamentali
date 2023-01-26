//Complexitate O(n+m)
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define INF 50002
vector<pair<int,int>>adj[INF];
vector<int>grad;
vector<bool>viz;
vector<int>sol[INF];
int k;
//rulam un dfs ca sa aflam numarul de etape si drumul corespunzator fiecarei etape
void dfs(int node){
    while(!adj[node].empty()){
        int x,id;
        x=adj[node].back().first;
        id=adj[node].back().second;
        adj[node].pop_back();
        if(viz[id]==false){
            viz[id]=true;
            dfs(x);
        }
    }
    if(node==0)
        k++;
    else
        sol[k].push_back(node);

}
int main() {
    int n,m,u,v,i,j;
    ifstream cin("johnie.in");
    ofstream cout("johnie.out");
    cin>>n>>m;
    grad.resize(n+2,0);
    for(i=1;i<=m;i++){
        cin>>u>>v;
        //adaugam in lista de adiacenta pentru fiecare nod, vecinul si id-ul muchiei
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
        grad[u]++;
        grad[v]++;
    }
    viz.resize(n+m+2,false);
    k=-1;
    //nodurile cu grad impar le legam de nodul 0
    for(i=1;i<=n;i++)
        if(grad[i]%2){
            adj[0].push_back({i,m+i});
            adj[i].push_back({0,m+i});
        }
    dfs(0);
    cout<<k<<'\n';
    for(i=0;i<k;i++){
        cout<<sol[i].size()<<" ";
        for(j=0;j<sol[i].size();j++)
            cout<<sol[i][j]<<" ";
        cout<<'\n';
    }
    cin.close();
    cout.close();

}
