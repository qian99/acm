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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 10;
ll mask[maxn<<2],lazy[maxn<<2];
inline void PushUp(int rt)
{
    mask[rt] = mask[rt<<1] | mask[rt<<1|1];
}
inline void PushDown(int rt)
{
    if(lazy[rt])
    {
        lazy[rt<<1] = lazy[rt];
        lazy[rt<<1|1] = lazy[rt];
        mask[rt<<1] = lazy[rt];
        mask[rt<<1|1] = lazy[rt];
        lazy[rt] = 0;
    }
}
void build(int l,int r,int rt)
{
    mask[rt] = 2;lazy[rt] = 0;
    if(l == r) return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int c)
{
    if(l >= L && r <= R)
    {
        mask[rt] = lazy[rt] = 1LL<<c;
        return ;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(m >= L) Update(L,R,l,m,rt<<1,c);
    if(m < R) Update(L,R,m+1,r,rt<<1|1,c);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R)
        return mask[rt];
    PushDown(rt);
    int m = (l + r)>>1;
    ll res = 0;
    if(m >= L) res |= Query(L,R,l,m,rt<<1);
    if(m < R) res |= Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    char str[10];
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        int L,R,c;
        build(1,n,1);
        while(m--)
        {
            scanf("%s",str);
            if(str[0] == 'P')
            {
                scanf("%d%d%d",&L,&R,&c);
                Update(L,R,1,n,1,c - 1);
            }
            else
            {
                scanf("%d%d",&L,&R);
                ll res = Query(L,R,1,n,1);
                bool first = true;
                for(int i = 0;i < 30;++i)
                {
                    if(res & (1LL<<i))
                    {
                        if(!first) printf(" ");
                        first = false;
                        printf("%d",i + 1);
                    }
                }
                puts("");
            }
        }
    }
    return 0;
}
