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
const int maxn=25;
int a[maxn],b[10],n,k,L,ans;
int c[10],d[20];
int flag[155],S[155],tot;
void solve()
{
    d[0]=0;
    tot=0;
    for(int i=1;i<=2*k;++i) d[i]^=d[i-1];
    for(int i=1;i<=k;++i)
        for(int j=1;j<=k;++j)
        {
            flag[d[i-1]^d[i+j-1]]=1;
            S[tot++]=d[i-1]^d[i+j-1];
        }

    int R=L;
    while(flag[R]) R++;
    if(R-L>ans) ans=R-L;
    for(int i=0;i<tot;++i) flag[S[i]]=0;
}
void cal()
{
    tot=0;
    for(int i=1;i<(1<<k);++i)
    {
        int val=0;
        for(int j=0;j<k;++j)
            if(i&(1<<j)) val^=b[j];
        flag[val]=1;
        S[tot++]=val;
    }
    int R=L;
    while(flag[R]) R++;
    for(int i=0;i<tot;++i) flag[S[i]]=0;
    if(R-L>ans)
    {
        int c[10];
        for(int i=0;i<k;++i) c[i]=i;
        do
        {
            for(int i=0;i<k;++i) d[i+1]=d[i+k+1]=b[c[i]];
            solve();
        }
        while(next_permutation(c,c+k));
    }
}
void dfs(int x,int pos)
{
    if(x==k)
    {
        cal();
        return ;
    }
    for(int i=pos;i<n;++i)
    {
        b[x]=a[i];
        dfs(x+1,i+1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&k,&L))
    {
        for(int i=0;i<n;++i)
            scanf("%d",&a[i]);
        memset(flag,0,sizeof(flag));
        ans=0;
        dfs(0,0);
        if(ans==0) printf("0\n");
        else printf("%d\n",L+ans-1);
    }
    return 0;
}
