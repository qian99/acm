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
const int maxn = 100000+10;
int a[maxn],conv[maxn],GS[55],n,m,Q,tot;
pair<int,int>Sp[maxn];
ll ans[maxn];
struct Node
{
    int L,g,id;
    Node(){}
    Node(int L,int g,int id):L(L),g(g),id(id){}
};
vector<Node>querys[maxn];
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
struct SegTree
{
    ll sum[maxn<<2];
    int addv[maxn<<2];
    void build(int l,int r,int rt)
    {
        sum[rt] = addv[rt] = 0;
        if(l == r) return ;
        int m =(l + r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    void PushUp(int rt)
    {
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    }
    void PushDown(int l,int r,int rt)
    {
        if(addv[rt])
        {
            addv[rt<<1] += addv[rt];
            addv[rt<<1|1] += addv[rt];
            int m = (l + r)>>1;
            sum[rt<<1] += (ll)addv[rt]*(m-l+1);
            sum[rt<<1|1] += (ll)addv[rt]*(r-m);
            addv[rt] = 0;
        }
    }
    void Update(int L,int R,int l,int r,int rt)
    {
        if(l >= L && r <= R)
        {
            addv[rt] ++;
            sum[rt] += (r-l+1);
            return ;
        }
        PushDown(l,r,rt);
        int m = (l + r)>>1;
        if(m >= L) Update(L,R,l,m,rt<<1);
        if(m < R) Update(L,R,m+1,r,rt<<1|1);
        PushUp(rt);
    }
    ll Query(int L,int R,int l,int r,int rt)
    {
        if(l >= L && r <= R) return sum[rt];
        PushDown(l,r,rt);
        int m = (l+r)>>1;
        ll res = 0;
        if(m >= L) res += Query(L,R,l,m,rt<<1);
        if(m < R) res += Query(L,R,m+1,r,rt<<1|1);
        return res;
    }
}tree[51];
void solve()
{
    tot = 0;
    for(int i = 0;i < m;++i)
        tree[i].build(1,n,1);
    int tmp,pos,L,R;
    Node node;
    for(int i = 1;i <= n;++i)
    {
        for(int j = 0;j < tot;++j)
        {
            tmp = gcd(Sp[j].first,a[i]);
            Sp[j].first = tmp;
        }
        if(tot > 0 && Sp[tot-1].first == a[i])
            Sp[tot-1].second++;
        else
            Sp[tot++] = make_pair(a[i],1);
        if(tot)
        {
            tmp = 1;
            for(int j = 1;j < tot;++j)
            {
                if(Sp[j].first == Sp[tmp-1].first)
                    Sp[tmp-1].second += Sp[j].second;
                else
                    Sp[tmp++] = Sp[j];
            }
            tot = tmp;
        }
        int cnt = 0;
        for(int j = 0;j < tot;++j)
        {
            tmp = Sp[j].first;
            pos = conv[tmp];
            if(pos != -1)
            {
                L = cnt + 1;
                R = cnt + Sp[j].second;
                tree[pos].Update(L,R,1,n,1);
            }
            cnt += Sp[j].second;
        }
        for(int j = 0; j < (int)querys[i].size();++j)
        {
            node = querys[i][j];
            ans[node.id] = tree[conv[node.g]].Query(node.L,i,1,n,1);
        }

    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&Q))
    {
        memset(conv,0xff,sizeof(conv));
        for(int i = 0;i <= n;++i)
            querys[i].clear();
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        for(int i = 0;i < m;++i)
        {
            scanf("%d",&GS[i]);
            conv[GS[i]] = i;
        }
        int L,R,g;
        for(int i = 1;i <= Q;++i)
        {
            scanf("%d%d%d",&L,&R,&g);
            L++;
            querys[R].push_back(Node(L,g,i));
        }
        solve();
        for(int i = 1;i <= Q;++i)
            printf("%lld\n",ans[i]);
    }
    return 0;
}
