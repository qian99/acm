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
const int maxn = 50000+10;
struct Node
{
    int op,x,t,id;
    Node(){}
    Node(int op,int x,int t,int id):op(op),x(x),t(t),id(id){}
}node[maxn];
int val[maxn];
char str[20];
bool cmp1(Node a,Node b)
{
    return a.t < b.t;
}
bool cmp2(Node a,Node b)
{
    return a.id < b.id;
}
int sum[maxn<<2],suff[maxn<<2];
inline void PushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    suff[rt] = max(suff[rt<<1|1],sum[rt<<1|1] + suff[rt<<1]);
}
void build(int l,int r,int rt)
{
    sum[rt] = suff[rt] = 0;
    if(l == r) return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l == r)
    {
        sum[rt] = suff[rt] = v;
        return ;
    }
    int m = (l+r)>>1;
    if(m >= p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int p,int l,int r,int rt,int & v)
{
    if(l == r)
    {
        if(sum[rt] == 1 && v == 0) return val[l];
        v -= sum[rt];
        return -1;
    }
    int m = (l+r)>>1;
    if(m >= p) return Query(p,l,m,rt<<1,v);
    if(r <= p)
    {
        if(suff[rt<<1|1] - v <= 0)
        {
            v -= sum[rt<<1|1];
            return Query(p,l,m,rt<<1,v);
        }
        else return Query(p,m+1,r,rt<<1|1,v);
    }
    if(m < p)
    {
        int res = Query(p,m+1,r,rt<<1|1,v);
        if(res != -1) return res;
    }
    return Query(p,l,m,rt<<1,v);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        for(int i = 1;i <= n;++i)
        {
            node[i].id = i;
            scanf("%s",str);
            if(str[1] == 'u')
            {
                node[i].op = 0;
                scanf("%d%d",&node[i].x,&node[i].t);
            }
            else if(str[1] == 'o')
            {
                node[i].op = 1;
                scanf("%d",&node[i].t);
            }
            else
            {
                node[i].op = 2;
                scanf("%d",&node[i].t);
            }
        }
        sort(node+1,node+n+1,cmp1);
        build(1,n,1);
        for(int i = 1;i <= n;++i)
        {
            node[i].t = i;
            val[i] = node[i].x;
        }
        sort(node+1,node+n+1,cmp2);
        printf("Case #%d:\n",++tcase);
        for(int i = 1;i <= n;++i)
        {
            if(node[i].op == 0)
                Update(node[i].t,1,n,1,1);
            else if(node[i].op == 1)
                Update(node[i].t,1,n,1,-1);
            else
            {
                int tmp = 0;
                printf("%d\n",Query(node[i].t,1,n,1,tmp));
            }
        }
    }
    return 0;
}
