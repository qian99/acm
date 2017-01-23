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
const int maxn=200000+10;
int parents[maxn],sum[maxn];
int Find(int x)
{
    if(x==parents[x]) return x;
    int tmp=parents[x];
    parents[x]=Find(parents[x]);
    sum[x]+=sum[tmp];
    return parents[x];
}
bool Uion(int x,int y,int v)
{
    int a=Find(x);
    int b=Find(y);
    if(a==b)
      return (sum[y]-sum[x])==v;
    parents[b]=a;
    sum[b]=sum[x]-sum[y]+v;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(sum,0,sizeof(sum));
        for(int i=0;i<=n;++i)
            parents[i]=i;
        int cnt=0;
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            if(a>b) swap(a,b);
            a--;
            if(!Uion(a,b,c)) cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
