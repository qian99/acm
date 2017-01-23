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
const int maxn=1000+10;
int edge[maxn*maxn][2],cnt;
bool vis[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    if((n%2==0)&&k>=(n/2)) printf("-1\n");
    else if((n%2!=0)&&k>(n/2)) printf("-1\n");
    else
    {
        int cnt=0;
        for(int i=1;i<=k;++i)
        {
            memset(vis,0,sizeof(vis));
            for(int j=1;j<=n;++j)
            {
                if(vis[j]) continue;
                int u=j,v;
                while(!vis[u])
                {
                    vis[u]=true;
                    edge[cnt][0]=u;
                    v=(u+i)%n;
                    if(v==0) v=n;
                    edge[cnt++][1]=v;
                    u=v;
                }
            }
        }
        printf("%d\n",cnt);
        for(int i=0;i<cnt;++i)
            printf("%d %d\n",edge[i][0],edge[i][1]);
    }
    return 0;
}