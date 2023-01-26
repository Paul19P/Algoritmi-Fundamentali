//O(log n)
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<int> t;
vector<int> rang;
int radacina(int k){
    if(t[k]==0)
        return k;
    else{
        int x = radacina(t[k]);
        t[k]=x;
        return x;
    }
}

void unire(int k,int p){
    int rk=radacina(k),rp=radacina(p);
    if(rk!=rp){
        if(rang[rk]>rang[rp])
            t[rp]=rk;
        else{
            t[rk]=rp;
            if(rang[rk]==rang[rp])
                rang[rp]++;
        }
    }
}

int main() {
    int n,m,i,op,u,v;
    ifstream cin("disjoint.in");
    ofstream cout("disjoint.out");
    cin>>n>>m;
    t.resize(n+1,0);
    rang.resize(n+1,0);
    for(i=1;i<=m;i++){
        cin>>op>>u>>v;
        if(op==1)
            unire(u,v);
        else
            if(radacina(u)==radacina(v))
                cout<<"DA"<<'\n';
            else
                cout<<"NU"<<'\n';
    }
    cin.close();
    cout.close();
}
