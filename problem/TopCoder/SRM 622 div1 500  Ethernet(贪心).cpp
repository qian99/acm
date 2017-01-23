#include<iostream>
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
typedef long long ll;
const int maxn=55;
class Ethernet
{
    public:
    vector<pair<int,int> >g[maxn];
    int maxd[maxn],val[maxn],n,mxd;
    void dfs(int u)
    {
        maxd[u]=0;val[u]=0;
        int cnt=0;
        vector<int>num;
        for(int i=0;i<(int)g[u].size();++i)
        {
            int v=g[u][i].first;
            dfs(v);
            val[u]+=val[v];
            num.push_back(maxd[v]+g[u][i].second);
        }
        sort(num.begin(),num.end());
        cnt=num.size();
        while(cnt>0&&num[cnt-1]>mxd) val[u]++,cnt--;
        while(cnt>1&&num[cnt-1]+num[cnt-2]>mxd) val[u]++,cnt--;
        if(cnt) maxd[u]=num[cnt-1];
    }
    int connect(vector <int> parent, vector <int> dist, int maxDist)
    {
        n=parent.size()+1;
        for(int i=0;i<n;++i) g[i].clear();
        mxd=maxDist;
        for(int i=0;i<n-1;++i)
        {
            g[parent[i]].push_back(make_pair(i+1,dist[i]));
        }
        dfs(0);
        return val[0]+1;
    }
};