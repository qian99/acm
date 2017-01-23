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
vector<int>fac[maxn];
bool flag[maxn];
void Init()
{
    memset(flag,0,sizeof(flag));
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            fac[i].push_back(i);
            for(int j=i*2;j<maxn;j+=i)
            {
                flag[j]=true;
                fac[j].push_back(i);
            }
        }
    }
}
int cal(int n,int m)
{
    int tot=fac[n].size();
    int sum=0,cnt,tmp;
    for(int i=1;i<(1<<tot);++i)
    {
        cnt=0;tmp=1;
        for(int j=0;j<tot;++j)
        {
            if(i&(1<<j))
            {
                tmp*=fac[n][j];
                cnt^=1;
            }
        }
        if(cnt) sum+=m/tmp;
        else sum-=m/tmp;
    }
    return m-sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        if(n>m) swap(m,n);
        ll ans=m;
        for(int i=2;i<=n;++i)
            ans+=cal(i,m);
        printf("%I64d\n",ans);
    }
    return 0;
}
