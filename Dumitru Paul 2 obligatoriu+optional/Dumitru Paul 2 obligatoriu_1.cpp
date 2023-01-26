#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits.h>
#include<iomanip>
using namespace std;
double distance(pair<double,double> c,pair<double,double> b){
    double x1,x2,y1,y2;
    x1=c.first;
    y1=c.second;
    x2=b.first;
    y2=b.second;
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main() {
    int n,m,i,j;
    double x,y,cost=0;
    ifstream cin("retea2.in");
    ofstream cout("retea2.out");
    cin>>n>>m;
    vector<pair<double,double>> centrale;
    vector<pair<double,double>> bl;
    vector<double>d;
    vector<bool> viz;
    d.resize(m+1,INT_MAX);
    viz.resize(m+1, false);
    bl.resize(m+1);
    centrale.resize(n+1);
    for(i=1;i<=n;i++){
        cin>>x>>y;
        centrale[i]={x,y};
    }
    for(i=1;i<=m;i++){
        cin>>x>>y;
        bl[i]={x,y};
    }
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            d[i]=min(d[i],distance(centrale[j],bl[i]));

    for(i=1;i<=m;i++){
        int index_min=-1;
        double d_min=INT_MAX;
        for(j=1;j<=m;j++)
            if(d[j]<d_min && viz[j]==false){
                d_min=d[j];
                index_min=j;
            }
        cost+=d_min;
        viz[index_min]=true;
        for(j=1;j<=m;j++)
            if(viz[j]==false)
                d[j]=min(d[j], distance(bl[j],bl[index_min]));
    }
    cout<<setprecision(6)<<fixed<<cost;
    cin.close();
    cout.close();
}
