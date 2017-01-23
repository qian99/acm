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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000+10;
int a[maxn],cntA[maxn],cntB[maxn],num[maxn];
map<int,int>mp;
int C[maxn];
inline int lowbit(int x)
{
    return x&-x;
}
int sum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int x,int v)
{
    while(x<maxn)
    {
        C[x]+=v;
        x+=lowbit(x);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    for(int i = 1;i <= n;++i)
    {
        if(mp.find(a[i]) == mp.end())
            cntA[i] = mp[a[i]] = 1;
        else cntA[i] = ++mp[a[i]];
    }
    mp.clear();
    for(int i = n;i >= 1;--i)
    {
        if(mp.find(a[i]) == mp.end())
            num[i-1] = cntB[i] = mp[a[i]] = 1;
        else num[i-1] = cntB[i] = ++mp[a[i]];
    }
    sort(num,num + n);
    int N = unique(num,num+n)- num;
    ll ans = 0;
    int pos;
    pos = pos = lower_bound(num,num+N,cntB[n]) - num;
    add(pos+1,1);
    for(int i = n-1;i >= 1;--i)
    {
        pos = lower_bound(num,num+N,cntA[i]) - num;
        if(pos > 0) ans +=sum(pos);
        pos = lower_bound(num,num+N,cntB[i]) - num;
        pos++;
        add(pos,1);
    }
    printf("%I64d\n",ans);
    return 0;
}