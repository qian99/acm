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
const int maxn=100000+10;
struct Node
{
    int id,a,b;
    Node(int id=0,int a=0,int b=0):id(id),a(a),b(b){}
    bool operator < (const Node &a) const
    {
        return b < a.b;
    }
}node[maxn];
vector<Node>vt[maxn];
int rank[maxn],used[maxn];
bool cmp(int a,int b)
{
    return vt[a].size() > vt[b].size();
}
int cnt[maxn<<2],sum[maxn<<2];
void PushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l == r)
    {
        cnt[rt] = 1;
        sum[rt] = node[l].b;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt)
{
    if(l == r)
    {
        cnt[rt] = sum[rt] =0;
        return ;
    }
    int m =(l+r)>>1;
    if(m >= p) Update(p,l,m,rt<<1);
    else Update(p,m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int k,int l,int r,int rt)
{
    if(l == r) return sum[rt];
    int m=(l+r)>>1;
    if(cnt[rt<<1] >= k) return Query(k,l,m,rt<<1);
    else return sum[rt<<1] + Query(k-cnt[rt<<1],m+1,r,rt<<1|1);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    int n;
    scanf("%d",&n);
    for(int i =1 ;i <= n;++i)
        scanf("%d%d",&node[i].a,&node[i].b);
    sort(node + 1,node + n +1);
    for(int i =1 ;i <= n;++i)
        node[i].id = i;
    for(int i =1;i <= n;++i)
    {
        vt[node[i].a].push_back(node[i]);
    }
    for(int i = 0;i < maxn ;++i)
        rank[i] = i;
    sort(rank,rank + maxn -1,cmp);
    build(1,n,1);
    int ans = inf,last = 0,has = 0,tmp;
    Node nd;
    for(int i = n;i >= 1;--i)
    {
        for(int j = 0;j < maxn;++j)
        {
            int x = rank[j];
            if((int)vt[x].size() - used[x] >= i)
            {
                nd = vt[x][used[x]];
                last += nd.b;
                Update(nd.id,1,n,1);
                used[x]++;
                has++;
            }
            else break;
        }
        tmp = last;
        if(has < i)
        {
            tmp += Query(i-has,1,n,1);
        }
        ans = min(ans,tmp);
    }
    printf("%d\n",ans);
    return 0;
}