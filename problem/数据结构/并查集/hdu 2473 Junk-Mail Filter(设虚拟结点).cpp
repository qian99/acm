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
const int maxn=2000000+10;
int pa[maxn],cnt[maxn];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,tcase=0;
    char str[5];
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        tcase++;
        for(int i=1;i<=n;++i) pa[i]=0;
        pa[0]=0;cnt[0]=1;
        int ans=n,x,y,a,b,tot=n;
        while(m--)
        {
            scanf("%s",str);
            if(str[0]=='M')
            {
                scanf("%d%d",&x,&y);
                x++;y++;
                a=Find(x);
                b=Find(y);
                if(a==0||b==0||a!=b)
                {
                    ans--;tot++;
                    pa[tot]=tot;cnt[tot]=0;
                    if(a!=0)
                    {
                        pa[a]=tot;
                        cnt[tot]+=cnt[a];
                        cnt[a]=0;
                    }
                    else
                    {
                        pa[x]=tot;
                        cnt[tot]++;
                    }
                    if(b!=0)
                    {
                        pa[b]=tot;
                        cnt[tot]+=cnt[b];
                        cnt[b]=0;
                    }
                    else
                    {
                        pa[y]=tot;
                        cnt[tot]++;
                    }
                }
            }
            else
            {
                scanf("%d",&x);
                x++;
                y=Find(x);
                if(y==0||cnt[y]==1) continue;
                pa[x]=0;cnt[y]--;
                ans++;
            }
        }
        printf("Case #%d: %d\n",tcase,ans);
    }
    return 0;
}
