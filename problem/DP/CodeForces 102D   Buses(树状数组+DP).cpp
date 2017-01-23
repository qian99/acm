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
const int mod=1000000007;
const int maxn=200000+10;
ll sum[maxn];
vector<pair<int,int> >bus;
int num[maxn],p[maxn][2];
map<int,int>mp;
inline int lowbit(int x)
{
    return x&-x;
}
void Add(int x,ll v)
{
    while(x<maxn)
    {
        sum[x]+=v;
        if(sum[x]>=mod) sum[x]-=mod;
        x+=lowbit(x);
    }
}
ll cal(int x)
{
    ll ret=0;
    while(x>0)
    {
        ret+=sum[x];
        if(ret>=mod)ret-=mod;
        x-=lowbit(x);
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&p[i][0],&p[i][1]);
        num[cnt++]=p[i][0];
        num[cnt++]=p[i][1];
    }
    int id=0,pre;
    sort(num,num+cnt);
    pre=num[0];
    mp[num[0]]=++id;
    for(int i=1;i<cnt;++i)
        if(num[i]==pre) continue;
        else
        {
            mp[num[i]]=++id;
            pre=num[i];
        }
    for(int i=0;i<m;++i)
        bus.push_back(make_pair(mp[p[i][1]],mp[p[i][0]]));
    sort(bus.begin(),bus.end());
    memset(sum,0,sizeof(sum));
    Add(1,1);
    int L,R;
    ll tmp;
    for(int i=0;i<m;++i)
    {
        L=bus[i].second;
        R=bus[i].first;
        tmp=(cal(R-1)-cal(L-1))%mod;
        if(tmp<0) tmp+=mod;
        Add(R,tmp);
    }
    if(!mp[n]||!mp[0]) printf("0\n");
    else
    {
        tmp=cal(id)-cal(id-1);
        tmp=(tmp%mod+mod)%mod;
        printf("%I64d\n",tmp);
    }
    return 0;
}
