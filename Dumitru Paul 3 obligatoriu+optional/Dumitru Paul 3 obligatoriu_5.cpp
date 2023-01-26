#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
//Complexitate O(n+m)
//n-numar varfuri
//m-numar muchii
//folosim masti pentru a tine minte ce noduri am vizitat
//folosim un set "viz" in care tinem minte ce nod am vizitat si masca corespunzatoare pentru nodul respectiv
//daca masca ajunge sa fie plina de 1 (all) atunci am vizitat toate nodurile si returnam distanta+1
class Solution {
    int bfs(vector<vector<int>>adj){
        int n,all,i,mask;
        n=adj.size();
        all=(1<<n)-1;
        queue<pair<int,pair<int,int>>>q;
        set<pair<int,int>> viz;
        //pornim din toate nodurile in acelasi timp
        for(i=0;i<n;i++){
            mask=(1<<i);
            q.push({i,{0,mask}});
            viz.insert({i,mask});
        }
        while(!q.empty()){
            int nod,dist;
            nod=q.front().first;
            dist=q.front().second.first;
            mask=q.front().second.second;
            q.pop();
            for(auto v:adj[nod]){
                //construim o masca noua din masca nodului pe care l vizitam si masca nodului din care vizitam
                int new_mask=mask|(1<<v);
                if(new_mask==all)
                    return dist+1;
                else if(viz.count({v,new_mask}))
                    continue;

                q.push({v,{dist+1,new_mask}});
                viz.insert({v,new_mask});
            }
        }
        return 0;
    }
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n=graph.size();
        if(n==1)
            return 0;
        int d=bfs(graph);
        return d;
    }
};
int main() {

}
