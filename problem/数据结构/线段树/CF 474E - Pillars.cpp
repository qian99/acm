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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 300000 + 10;
ll h[maxn],val[maxn];
map<ll,int>mp;
int dp[maxn],next[maxn];
int maxv[maxn<<2],pos[maxn<<2];
void PushUp(int rt)
{
    if(maxv[rt<<1|1] >= maxv[rt<<1])
    {
        maxv[rt] = maxv[rt<<1|1];
        pos[rt] = pos[rt<<1|1];
    }
    else
    {
        maxv[rt] = maxv[rt<<1];
        pos[rt] = pos[rt<<1];
    }
}
void build(int l,int r,int rt)
{
    maxv[rt] = 0;
    pos[rt] = 0;
    if(l == r) return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v,int id)
{
    if(l == r)
    {
        maxv[rt] = v;
        pos[rt] = id;
        return ;
    }
    int m = (l + r)>>1;
    if(m >= p) Update(p,l,m,rt<<1,v,id);
    else Update(p,m+1,r,rt<<1|1,v,id);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int & maxlen)
{
    if(l >= L && r <= R)
    {
        maxlen = maxv[rt];
        return pos[rt];
    }
    int m = (l + r)>>1;
    if(m >= R) return Query(L,R,l,m,rt<<1,maxlen);
    else if(m < L) return Query(L,R,m+1,r,rt<<1|1,maxlen);
    else
    {
        int p1,p2,m1,m2;
        p1 = Query(L,R,l,m,rt<<1,m1);
        p2 = Query(L,R,m+1,r,rt<<1|1,m2);
        if(m2 >= m1)
        {
            m1 = m2;
            p1 = p2;
        }
        maxlen = m1;
        return p1;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,d;
    scanf("%d%d",&n,&d);
    for(int i = 1;i <= n;++i)
        scanf("%I64d\n",&h[i]);
    int N = 0;
    for(int i = 1;i <= n;++i)
    {
        val[++N] = h[i];
        val[++N] = h[i] - d;
        val[++N] = h[i] + d;
    }
    sort(val + 1,val + N + 1);
    N = unique(val + 1,val + N + 1) - (val + 1);
    for(int i = 1;i <= N;++i)
        mp[val[i]] = i;
    build(1,N,1);
    next[n] = -1;
    dp[n] = 1;
    int mlen = 1,mpos = n,tmp,L,R,p;
    Update(mp[h[n]],1,N,1,1,n);
    for(int i = n - 1;i >= 1;--i)
    {
        L = mp[h[i] - d];
        R = mp[h[i] + d];
        dp[i] = -1;next[i] = -1;
        if(1 <= L)
        {
            p = Query(1,L,1,N,1,tmp);
            if(tmp == 0)
            dp[i] = 1,next[i] = -1;
            else
                dp[i] = tmp + 1,next[i] = p;
        }
        if(R <= N)
        {
            p = Query(R,N,1,N,1,tmp);
            if(tmp && tmp + 1 > dp[i])
            {
                dp[i] = tmp + 1;
                next[i] = p;
            }
        }
        Update(mp[h[i]],1,N,1,dp[i],i);
        if(dp[i] > mlen)
        {
            mlen = dp[i];
            mpos = i;
        }
    }
    printf("%d\n",mlen);
    for(int i = 0;i < mlen;++i)
    {
        printf("%d ",mpos);
        mpos = next[mpos];
    }
    puts("");
    return 0;
}