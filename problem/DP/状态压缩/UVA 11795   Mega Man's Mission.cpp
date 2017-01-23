#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1<<17;
ll dp[maxn];
int equip[maxn];
int weapon[17],p[17];
int n;
vector<int>s[17];
void Init()
{
    memset(dp,0,sizeof(dp));
    memset(equip,0,sizeof(equip));
    for(int i=0;i<=n;++i) p[i]=1<<i;
    for(int i=0;i<=n;++i)
      s[i].clear();
}
void getState()
{
    int N=p[n];
    equip[0]=weapon[0];
    int cnt=0,state,j;
    for(int i=1;i<N;++i)
    {
        state=i;cnt=0;
        equip[i]|=weapon[0];
        for(j=n-1;j>=0;--j)
        {
            if(state&p[j])
            {
                cnt++;
                equip[i]|=weapon[n-j];
            }
        }
        s[cnt].push_back(state);
    }
}
void solve()
{
    dp[0]=1;
    int state,i,j,k,pre;
    for(i=1;i<=n;++i)
        for(j=0;j<s[i].size();++j)
        {
            state=s[i][j];
            for(k=n-1;k>=0;--k)
            {
                if(state&p[k])
                {
                    pre=state^p[k];
                    if(equip[pre]&p[k])
                      dp[state]+=dp[pre];
                }
            }
        }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    char str[20];
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        Init();
        int j;
        for(int i=0;i<=n;++i)
        {
            scanf("%s",str);
            j=0;
            for(int k=0;k<n;++k)
                if(str[k]=='1') j|=p[n-k-1];
            weapon[i]=j;
        }
        getState();
        solve();
        printf("Case %d: %lld\n",tcase,dp[p[n]-1]);
    }
    return 0;
}
