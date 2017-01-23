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
const int maxn=100000+10;
struct Interval
{
    int s,t,pos;
    bool operator < (const Interval & a) const
    {
        return (t<a.t)||(t==a.t&&s<a.s);
    }
};
Interval cs[maxn];
bool vis[maxn];
vector<int>res[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&cs[i].s,&cs[i].t);
            cs[i].pos=i;
        }
        sort(cs+1,cs+n+1);
        memset(vis,0,sizeof(vis));
        int p=0,ps=1;
        while(ps<=n)
        {
            res[++p].clear();
            int tt=cs[ps].t;
            res[p].push_back(cs[ps].pos);
            vis[ps]=true;
            for(int i=ps+1;i<=n;++i)
            {
                if(cs[i].s<tt)
                {
                    vis[i]=true;
                    res[p].push_back(cs[i].pos);
                }
                else break;
            }
            while(vis[ps]) ps++;
        }
        printf("%d\n",p);
        int sz;
        for(int i=1;i<=p;++i)
        {
            sz=res[i].size();
            printf("%d",res[i][0]);
            for(int j=1;j<sz;++j)
              printf(" %d",res[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
