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
const int maxn = 500000 + 10;
struct Node
{
    int a,b;
    Node(int a = 0,int b = 0):a(a),b(b){}
    bool operator < (const Node & x) const
    {
        return a > x.a;
    }
};
int num[maxn],a[maxn],b[maxn],pre[maxn],last[maxn],ans[maxn],tot;
int minv[maxn<<2],mpos[maxn<<2];
priority_queue<Node>q;
inline void PushUp(int rt)
{
    if(minv[rt<<1] < minv[rt<<1|1])
    {
        minv[rt] = minv[rt<<1];
        mpos[rt] = mpos[rt<<1];
    }
    else
    {
        minv[rt] = minv[rt<<1|1];
        mpos[rt] = mpos[rt<<1|1];
    }
}
void build(int l,int r,int rt)
{
    minv[rt] = inf;
    mpos[rt] = l;
    if(l == r)
        return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l == r)
    {
        minv[rt] = v;
        return ;
    }
    int m = (l + r)>>1;
    if(m >= p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int & p)
{
    if(l >= L && r <= R)
    {
        p = mpos[rt];
        return minv[rt];
    }
    int m = (l + r)>>1;
    if(m >= R) return Query(L,R,l,m,rt<<1,p);
    else if(m < L) return Query(L,R,m+1,r,rt<<1|1,p);
    else
    {
        int r1,r2,p1,p2;
        r1 = Query(L,R,l,m,rt<<1,p1);
        r2 = Query(L,R,m+1,r,rt<<1|1,p2);
        if(r2 < r1)
            r1 = r2,p1 = p2;
        p = p1;
        return r1;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&a[i]);
        num[i] = b[i] = a[i];
    }
    sort(b + 1,b + n + 1);
    int N = unique(b + 1, b + n + 1) - (b+1);
    for(int i = 1;i <= n;++i)
        a[i] = lower_bound(b + 1,b + N + 1,a[i]) - b;
    memset(last,0xff,sizeof(last));
    for(int i = 1;i <= n;++i)
    {
        if(last[a[i]] == -1)
            pre[i] = 0;
        else
            pre[i] = last[a[i]];
        last[a[i]] = i;
    }
    build(1,n,1);
    tot = 0;
    Node node;
    int s = 1;
    for(int i = 1;i <= n;++i)
    {
        while(!q.empty())
        {
            node = q.top();
            if(node.a < s)
            {
                Update(node.b,1,n,1,inf);
                q.pop();
            }
            else
                break;
        }
        int cnt = 0;
        int j = i;
        while(j >= s)
        {
            j = pre[j];
            cnt++;
        }
        if(cnt > 3)
        {
            ans[tot++] = num[i];
            ans[tot++] = num[i];
            ans[tot++] = num[i];
            ans[tot++] = num[i];
            s = i + 1;
        }
        else
        {
            j = pre[i];
            while(j > s)
            {
                int pnow,plast;
                if(j + 1 <= i - 1)
                {
                    plast = Query(j + 1,i - 1,1,n,1,pnow);
                    if(plast < j)
                    {
                        ans[tot++] = num[plast];
                        ans[tot++] = num[j];
                        ans[tot++] = num[pnow];
                        ans[tot++] = num[i];
                        s = i + 1;
                        break;
                    }
                }
                j = pre[j];
            }
        }
        Update(i,1,n,1,pre[i]);
        q.push(Node(pre[i],i));
    }
    printf("%d\n",tot);
    for(int i = 0;i < tot;++i)
    {
        if(i) putchar(' ');
        printf("%d",ans[i]);
    }
    puts("");
    return 0;
}
