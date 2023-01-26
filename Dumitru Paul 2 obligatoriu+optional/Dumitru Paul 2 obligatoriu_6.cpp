//dfs topological sort
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <limits.h>
using namespace std;
vector<bool>viz;
vector<vector<int>>adj;
stack<int>s;
void dfs(int nod){
    viz[nod]=true;
    for(auto x:adj[nod]){
        if(viz[x]==false)
            dfs(x);
    }
    s.push(nod);
}
int main() {
    int t,n,m,i,j,u,v,nod;
    ifstream cin("easygraph.in");
    ofstream cout("easygraph.out");
    vector<int>c;
    vector<long long>suma;
    cin>>t;
    for(i=1;i<=t;i++){
        cin>>n>>m;
        c.clear();
        viz.clear();
        adj.clear();
        suma.clear();
        suma.resize(n+1);
        adj.resize(n+1);
        c.resize(n+1);
        viz.resize(n+1,false);
        for(j=1;j<=n;j++){
            cin>>c[j];
            suma[j]=c[j];
        }
        for(j=1;j<=m;j++){
            cin>>u>>v;
            adj[u].push_back(v);
        }
        for(j=1;j<=n;j++){
            if(viz[j]==false)
                dfs(j);
        }
        long long mx=INT_MIN;
        while(!s.empty()){
            nod=s.top();
            s.pop();
            for(auto x:adj[nod])
                if(c[x]+suma[nod]>suma[x])
                    suma[x]=c[x]+suma[nod];
            mx=max(mx,suma[nod]);
        }
        cout<<mx<<"\n";
    }
    cin.close();
    cout.close();
}
