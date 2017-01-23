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
const int maxn = 100000 + 10;
int gcd(int a,int b) { return b == 0 ? a : gcd(b,a%b);}
int minv[maxn<<2],sum[maxn<<2],gval[maxn<<2];
int a[maxn];
void PushUp(int rt)
{
    gval[rt] = gcd(gval[rt<<1],gval[rt<<1|1]);
    if(minv[rt<<1] == minv[rt<<1|1])
    {
        minv[rt] = minv[rt<<1];
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    }
    else if(minv[rt<<1] < minv[rt<<1|1])
    {
        minv[rt] = minv[rt<<1];
        sum[rt] = sum[rt<<1];
    }
    else
    {
        minv[rt] = minv[rt<<1|1];
        sum[rt] = sum[rt<<1|1];
    }
}
void build(int l,int r,int rt)
{
    if(l == r)
    {
        minv[rt] = gval[rt] = a[l];
        sum[rt] = 1;
        return ;
    }
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m + 1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int & mval,int & cnt)
{
    if(l >= L && r <= R)
    {
        mval = minv[rt];
        cnt = sum[rt];
        return gval[rt];
    }
    int m = (l + r)>>1;
    if(m >= R) return Query(L,R,l,m,rt<<1,mval,cnt);
    else if(m < L) return Query(L,R,m + 1,r,rt<<1|1,mval,cnt);
    else
    {
        int g1,g2,m1,m2,c1,c2;
        g1 = Query(L,R,l,m,rt<<1,m1,c1);
        g2 = Query(L,R,m + 1,r,rt<<1|1,m2,c2);
        if(m1 == m2)
            c1 += c2;
        else if(m1 > m2)
            m1 = m2,c1 = c2;
        mval = m1;
        cnt = c1;
        return gcd(g1,g2);
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
    build(1,n,1);
    int t,L,R,val,mval,cnt;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&L,&R);
        val = Query(L,R,1,n,1,mval,cnt);
        if(mval == val)
            printf("%d\n",R - L + 1 - cnt);
        else
            printf("%d\n",R - L + 1);
    }
    return 0;
}
