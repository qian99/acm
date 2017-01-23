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
const int maxn = 100000 + 10;
struct Node
{
    int d,price,pos;
    Node(int d = 0,int price = 0,int pos = 0):d(d),price(price),pos(pos){}
    bool operator < (const Node & a) const
    {
        return d < a.d;
    }
}node[maxn];
int P[maxn],T[maxn];
int sum[maxn<<2];
double val[maxn<<2][3];
void PushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    for(int i = 0;i < 3 ;++i)
    {
        val[rt][i] = val[rt<<1][i] + val[rt<<1|1][(i+sum[rt<<1])%3];
    }
}
void build(int l,int r,int rt)
{
    sum[rt] = 0;
    val[rt][0] = val[rt][1] = val[rt][2] = 0;
    if(l == r) return ;
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l == r)
    {
        sum[rt] = 1;
        for(int i = 0;i < 3;++i)
            val[rt][i] = (i+1.0)*v;
        return ;
    }
    int m = (l+r)>>1;
    if(m >= p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%d",&node[i].price);
        for(int i = 1;i <= n;++i)
            scanf("%d",&node[i].d);
        sort(node + 1,node + n + 1);
        T[0] = 0;
        for(int i = n;i >= 1;--i)
        {
            node[i].pos = i;
            node[i].d = node[i].d - node[i-1].d;
        }
        sort(node + 1, node + n + 1);
        build(1,n,1);
        double minw = 0,maxavg = 0;
        double avg = 0;
        for(int i = 1;i <= n;)
        {
            int j = i;
            while(j <= n && node[j].d == node[i].d)
            {
                Update(node[j].pos,1,n,1,node[j].price);
                j++;
            }
            avg = val[1][0]/sum[1];
            if(avg > maxavg)
            {
                minw = node[i].d;
                maxavg = avg;
            }
            i = j;
        }
        printf("%.6lf %.6lf\n",minw,maxavg);
    }
    return 0;
}
