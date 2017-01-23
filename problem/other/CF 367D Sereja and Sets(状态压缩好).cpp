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
const int maxn=100000+10;
int cnt[25],id[maxn],bitnum[1<<21];
bool badset[1<<21];
void Init()
{
    memset(bitnum,0,sizeof(bitnum));
    for(int i=0;i<(1<<20);++i)
    {
        int x=i;
        while(x)
        {
            bitnum[i]++;
            x=x&(x-1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,d;
    memset(badset,0,sizeof(badset));
    memset(cnt,0,sizeof(cnt));
    Init();
    scanf("%d%d%d",&n,&m,&d);
    for(int i=0;i<m;++i)
    {
        int size,v;
        scanf("%d",&size);
        for(int j=0;j<size;++j)
        {
            scanf("%d",&v);
            id[v]=i;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(i>d) cnt[id[i-d]]--;
        cnt[id[i]]++;
        if(i>=d)
        {
            int msk=0;
            for(int j=0;j<m;++j)
                if(!cnt[j]) msk|=(1<<j);
            badset[msk]=true;
        }
    }
    int ans=22;
    for(int i=(1<<m)-1;i>0;--i)
    {
        if(!badset[i])
            ans=min(ans,bitnum[i]);
        else
        {
            for(int j=0;j<m;++j)
                if(i&(1<<j)) badset[i-(1<<j)]=true;
        }
    }
    printf("%d\n",ans);
    return 0;
}
