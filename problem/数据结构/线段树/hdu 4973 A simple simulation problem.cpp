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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 50000+10;
ll maxv[maxn<<2],sum[maxn<<2],mul[maxn<<2],ans;
inline void PushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    maxv[rt] = max(maxv[rt<<1],maxv[rt<<1|1]);
}
void PushDown(int rt)
{
    if(mul[rt] > 1)
    {
        mul[rt<<1] *= mul[rt];
        mul[rt<<1|1] *= mul[rt];
        maxv[rt<<1] = maxv[rt<<1]*mul[rt];
        maxv[rt<<1|1] = maxv[rt<<1|1]*mul[rt];
        sum[rt<<1] = sum[rt<<1]*mul[rt];
        sum[rt<<1|1] = sum[rt<<1|1]*mul[rt];
        mul[rt] = 1;
    }
}
void build(int l,int r,int rt)
{
    mul[rt] = 1;
    if(l == r)
    {
        sum[rt] = maxv[rt] = 1;
        return ;
    }
    int m =(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Qleft(ll k,ll tot,int l,int r,int rt,int type)
{
    if(l == r)
    {
        if(type == 0)
        {
            if(sum[rt] - k + 1 >= tot)
            {
                ans = tot;
                return -1;
            }
            ans = max(ans,sum[rt]-k+1);
            return l + 1;
        }
        else
        {
            if(sum[rt] - k + 1 >= tot)
            {
                sum[rt] += tot;
                maxv[rt] += tot;
                return -1;
            }
            maxv[rt] += sum[rt]-k+1;
            sum[rt] += sum[rt]-k+1;
            return l + 1;
        }
    }
    PushDown(rt);
    int m = (l+r)>>1;
    int res;
    if(sum[rt<<1]>=k) res = Qleft(k,tot,l,m,rt<<1,type);
    else res = Qleft(k - sum[rt<<1],tot,m+1,r,rt<<1|1,type);
    PushUp(rt);
    return res;
}
int Qright(ll k,ll tot,int l,int r,int rt,int type)
{
    if(l == r)
    {
        if(type == 0)
        {
            if(tot <= k)
            {
                ans = tot;
                return -1;
            }
            ans = max(ans,k);
            return r - 1;
        }
        else
        {
            if(tot<=k)
            {
                sum[rt] += tot;
                maxv[rt] += tot;
                return -1;
            }
            sum[rt] += k;
            maxv[rt] += k;
            return r - 1;
        }
    }
    PushDown(rt);
    int m = (l+r)>>1;
    int res ;
    if(sum[rt<<1]>=k) res = Qright(k,tot,l,m,rt<<1,type);
    else res = Qright(k - sum[rt<<1],tot,m+1,r,rt<<1|1,type);
    PushUp(rt);
    return res;
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R)
    {
        return maxv[rt];
    }
    PushDown(rt);
    int m = (l + r)>>1;
    ll res = 0;
    if(m >= L) res = max(res,Query(L,R,l,m,rt<<1));
    if(m < R) res = max(res ,Query(L,R,m+1,r,rt<<1|1));
    return res;
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R)
    {
        mul[rt] *= 2;
        sum[rt] *= 2;
        maxv[rt] *= 2;
        return ;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(m >= L) Update(L,R ,l,m,rt<<1);
    if(m < R) Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n,m,tcase = 0;
    char str[10];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        build(1,n,1);
        ll l,r;
        int L,R;
        printf("Case #%d:\n",++tcase);
        while(m--)
        {
            scanf("%s%I64d%I64d",str,&l,&r);
            if(str[0] == 'D')
            {
                R = Qright(r,r-l+1,1,n,1,1);
                if(R != -1) L = Qleft(l,r-l+1,1,n,1,1);
                if(L != -1 && R != -1 && L <= R)
                {
                    Update(L,R,1,n,1);
                }
            }
            else
            {
                ans = 0;
                R = Qright(r,r-l+1,1,n,1,0);
                if(R != -1) L = Qleft(l,r-l+1,1,n,1,0);
                if(L != - 1&& R != - 1 && L <= R)
                {
                    ans = max(ans,Query(L,R,1,n,1));
                }
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}
