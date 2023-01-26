#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
map <string,vector<pair<string,char>>> adj;
map <string,int> gradin;
map <string,int> gradout;
string raspuns;
void euler(string s){
    while(!adj[s].empty()){
        string urm = adj[s].back().first;
        char label = adj[s].back().second;
        adj[s].pop_back();
        euler(urm);
        raspuns.push_back(label);
    }
}
int main() {
    int n,k,i;
    string st;
    cin>>n>>k;
    for(i=1;i<=n;i++){
        string suf,pref,s;
        cin>>s;
        suf=pref=s;
        pref.erase(int(pref.size()-1));
        suf.erase(suf.begin());
        adj[pref].push_back({suf,s[s.size()-1]});
        gradout[pref]++;
        gradin[suf]++;
    }
    int noduri_st=0,noduri_end=0;
    for(auto node:adj){
        if(gradout[node.first]-gradin[node.first]==0)
            continue;
        else if(gradout[node.first]-gradin[node.first]==1){
            noduri_st++;
            st=node.first;
        }
        else if(gradout[node.first]-gradin[node.first]==-1)
            noduri_end++;
        else{
            cout<<-1;
            return 0;
        }
    }
    if(noduri_st>1 || noduri_end>1){
        cout<<-1;
        return 0;
    }
    else if(noduri_st==0)
        st=adj.begin()->first;

    euler(st);
    reverse(st.begin(),st.end());
    raspuns+=st;
    reverse(raspuns.begin(),raspuns.end());
    if(raspuns.size() != n+k-1){
        cout<<-1;
        return 0;
    }
    cout<<raspuns;
    return 0;
}
