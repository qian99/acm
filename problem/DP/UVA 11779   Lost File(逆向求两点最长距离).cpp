#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
int d[maxn][maxn];
vector<int>g[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n,m;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        memset(d,0,sizeof(d));
        int u,v,w;
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            d[u][v]=w;
        }
        for(int i=0;i<=n;++i) g[i].clear();
        for(int k=0;k<n;++k)
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j)
                    d[i][j]-=d[i][k]*d[k][j];
        int tot=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(d[i][j])
                {
                    g[i].push_back(j);
                    tot++;
                }
        printf("Case %d: %d %d\n",tcase,n,tot);
        int size;
        for(int i=0;i<n;++i)
        {
            size=g[i].size();
            printf("%d",size);
            for(int j=0;j<size;++j)
                printf(" %d",g[i][j]);
            printf("\n");
        }
    }
    return 0;
}

