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
class BuildingRoutes
{
    public:
    int g[maxn][maxn],used[maxn][maxn],n;
    int d[maxn][maxn];
    bool inq[maxn];
    void floyd()
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                d[i][j]=g[i][j];
        for(int k=0;k<n;++k)
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j)
                    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        for(int s=0;s<n;++s)
            for(int t=0;t<n;++t)
            {
                if(s==t) continue;
                for(int i=0;i<n;++i)
                    for(int j=0;j<n;++j)
                        if(d[s][i]+g[i][j]+d[j][t]==d[s][t])
                            used[i][j]++;
            }
    }
    int build(vector <string> dist, int T)
    {
        n=dist.size();
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                g[i][j]=dist[i][j]-'0';
        memset(used,0,sizeof(used));
        floyd();
        int ans=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(used[i][j]>=T)
                    ans+=g[i][j];
        return ans;
    }
};