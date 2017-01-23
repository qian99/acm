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
ll val[maxn][maxn],sa[maxn][maxn],ta[maxn][maxn];
ll sb[maxn][maxn],tb[maxn][maxn];
int n,m;
void cal()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            sa[i][j]=max(sa[i-1][j],sa[i][j-1])+val[i][j];
    for(int i=n;i>=1;--i)
        for(int j=m;j>=1;--j)
            ta[i][j]=max(ta[i+1][j],ta[i][j+1])+val[i][j];
    for(int i=n;i>=1;--i)
        for(int j=1;j<=m;++j)
            sb[i][j]=max(sb[i+1][j],sb[i][j-1])+val[i][j];
    for(int i=1;i<=n;++i)
        for(int j=m;j>=1;--j)
            tb[i][j]=max(tb[i-1][j],tb[i][j+1])+val[i][j];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            scanf("%I64d",&val[i][j]);
    cal();
    ll ans=0,tmp;
    for(int i=2;i<n;++i)
        for(int j=2;j<m;++j)
        {
            tmp=sa[i-1][j]+ta[i+1][j]+sb[i][j-1]+tb[i][j+1];
            ans=max(ans,tmp);
            tmp=sa[i][j-1]+ta[i][j+1]+sb[i+1][j]+tb[i-1][j];
            ans=max(ans,tmp);
        }
    printf("%I64d\n",ans);
    return 0;
}