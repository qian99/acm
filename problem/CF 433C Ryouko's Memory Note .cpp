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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
vector<int>val[maxn];
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    ll sum=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
        scanf("%d",&a[i]);
    for(int i=2;i<=m;++i)
        sum+=abs(a[i]-a[i-1]);
    if(m==1)
    {
        printf("0\n");
        return 0;
    }
    if(a[2]!=a[1]) val[a[1]].push_back(a[2]);
    if(a[m]!=a[m-1]) val[a[m]].push_back(a[m-1]);
    for(int i=2;i<m;++i)
    {
        if(a[i-1]!=a[i]) val[a[i]].push_back(a[i-1]);
        if(a[i+1]!=a[i]) val[a[i]].push_back(a[i+1]);
    }
    ll ans=Inf,tmp;
    for(int i=1;i<=n;++i)
    {
        int size=val[i].size(),mid;
        if(!size) continue;
        sort(val[i].begin(),val[i].end());
        mid=val[i][size/2];
        tmp=0;
        for(int j=0;j<size;++j)
            tmp+=abs(val[i][j]-mid)-abs(val[i][j]-i);
        ans=min(ans,sum+tmp);
    }
    if(sum==0) ans=0;
    printf("%I64d\n",ans);
    return 0;
}
