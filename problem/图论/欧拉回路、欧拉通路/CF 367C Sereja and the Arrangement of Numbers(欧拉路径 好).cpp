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
const int maxn=10000+10;
const int Maxn=100000+10;
ll a[maxn];
int w[Maxn];
bool cmp(int x,int y) { return x>y;}
void Init()
{
    for(ll i=1;i<maxn;++i)
    {
        if(i&1) a[i]=i*(i-1)/2+1;
        else a[i]=i*i/2;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,tmp;
    Init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
        scanf("%d%d",&tmp,&w[i]);
    sort(w+1,w+m+1,cmp);
    int p=0;
    for(int i=1;i<maxn;++i)
        if(a[i]<=n) p=i;
        else break;
    ll ans=0;
    for(int i=1;i<=min(m,p);++i)
        ans+=w[i];
    printf("%I64d\n",ans);
    return 0;
}
