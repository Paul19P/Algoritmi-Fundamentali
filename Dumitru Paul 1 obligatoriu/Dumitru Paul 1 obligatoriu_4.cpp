//O(n+m)
// folosim algoritmul lui Kosaraju
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int mx = 100005;
vector <int> ord;
vector <int> g[mx], gt[mx];
vector <vector<int>> rez;
bool viz[mx];
int cmp[mx];
void dfs1(int nod)
{
    viz[nod] = 1;
    for (int v : g[nod])
        if (viz[v]==0)
            dfs1(v);
    ord.push_back(nod);
}
int nr;
void dfs2(int nod)
{
    cmp[nod] = nr;
    for (int v : gt[nod])
        if (!cmp[v])
            dfs2(v);
}
int main()
{
    ifstream cin("ctc.in");
    ofstream cout("ctc.out");
    int n, m, i,j;
    cin >> n >> m;
    for (i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        gt[b].push_back(a);
    }
    for (i = 1; i <= n; i++)
        if (viz[i]==0)
            dfs1(i);
    for (i = ord.size() - 1; i > -1; i--)
        if (!cmp[ord[i]])
        {
            nr++;
            dfs2(ord[i]);
        }
    cout << nr << "\n";
    rez.resize(nr+1);
    for(i=1;i<=n;i++)
        rez[cmp[i]].push_back(i);
    for(i=1;i<=nr;i++){
        for(j=0;j<rez[i].size();j++)
            cout<<rez[i][j]<<" ";
        cout<<'\n';
    }
}