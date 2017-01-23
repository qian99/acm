#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1100000+10;
int edges[maxn][2],degree[maxn];
vector<int>vt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k,n;
    scanf("%d%d",&n,&k);
    memset(degree,0,sizeof(degree));
    int tmp,cnt=0,maxd=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&tmp);
        vt[tmp].push_back(i);
        if(tmp==0) cnt++;
        maxd=max(maxd,tmp);
    }
    if(cnt!=1)
    {
        printf("-1\n");
        return 0;
    }
    bool flag=true;
    cnt=0;
    for(int i=1;i<=maxd&&flag;++i)
    {
        int sz1=vt[i].size(),sz2=vt[i-1].size();
        if(sz2==0||sz1==0) flag=false;
        int w=0;
        for(int j=0;j<sz1&&flag;++j)
        {
            int u=vt[i][j];
            int v=vt[i-1][w];
            while(degree[v]==k&&w<sz2) {w++;if(w<sz2)v=vt[i-1][w];}
            if(w==sz2&&degree[v]==k) flag=false;
            edges[cnt][0]=u;edges[cnt++][1]=v;
            degree[u]++;degree[v]++;
        }
    }
    if(!flag)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n",n-1);
        for(int i=0;i<n-1;++i)
            printf("%d %d\n",edges[i][0],edges[i][1]);
    }
    return 0;
}