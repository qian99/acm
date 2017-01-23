#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
vector<int>g[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(cin>>n>>m)
    {
        map<int,int>mp;
        for(int i=0;i<=n;++i)
            g[i].clear();
        int tp,s=1;
        for(int i=1;i<=n;++i)
        {
            cin>>tp;
            if(mp[tp]==0)
            {
                mp[tp]=s;
                g[s].push_back(i);
                s++;
            }
            else
            {
                g[mp[tp]].push_back(i);
            }
        }
        int k,v;
        for(int i=0;i<m;++i)
        {
            cin>>k>>v;
            int u=mp[v];
            int sz=g[u].size();
            if(mp[v]==0||sz<k)
            {
                cout<<0<<endl;
                continue;
            }
            cout<<g[u][k-1]<<endl;
        }
    }
    return 0;
}

