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
const int maxn=10000+10;
int id[maxn];
bool vis[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int x,y;
        memset(id,0xff,sizeof(id));
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            id[x]=y;
        }
        memset(vis,0,sizeof(vis));
        int ans=0,cnt;
        for(int i=1;i<=10000;++i)
        {
            if(vis[i]||id[i]==-1) continue;
            int j=i;cnt=0;
            while(!vis[j])
            {
                vis[j]=true;
                cnt++;
                j=id[j];
            }
            ans+=(cnt-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
