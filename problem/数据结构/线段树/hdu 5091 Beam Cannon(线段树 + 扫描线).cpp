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
struct Point
{
    int x,y,z;
    Point(int x = 0,int y = 0,int z = 0):x(x),y(y),z(z){}
    bool operator < (const Point & a) const
    {
        if(y == a.y) return x < a.x;
        return y < a.y;
    }
}pt[maxn],S[maxn];
int maxv[maxn<<2],addv[maxn<<2];
bool cmp(Point a,Point b)
{
    return a.x < b.x;
}
inline void PushUp(int rt)
{
    maxv[rt] = max(maxv[rt<<1],maxv[rt<<1|1]);
}
void PushDown(int rt)
{
    if(addv[rt])
    {
        addv[rt<<1] += addv[rt];
        addv[rt<<1|1] += addv[rt];
        maxv[rt<<1] += addv[rt];
        maxv[rt<<1|1] += addv[rt];
        addv[rt] = 0;
    }
}
void build(int l,int r,int rt)
{
    maxv[rt] = addv[rt] = 0;
    if(l == r) return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m + 1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l >= L && r <= R)
    {
        addv[rt] += v;
        maxv[rt] += v;
        return ;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(m >= L) Update(L,R,l,m,rt<<1,v);
    if(m < R) Update(L,R,m + 1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,W,H;
    while(~scanf("%d",&n))
    {
        if(n < 0) break;
        scanf("%d%d",&W,&H);
        int x,y,N = 0;
        for(int i = 0;i < n;++i)
        {
            scanf("%d%d",&x,&y);
            pt[i].x = x + 20001;
            pt[i].y = y + 20001;
            N = max(N,pt[i].x);
         }
         build(1,N,1);
         sort(pt,pt + n);
         for(int i = 0;i < n;++i)
         {
             S[i].z = pt[i].y;
             S[i].x = pt[i].x - W;
             S[i].y = pt[i].x;
             S[i].x = max(S[i].x,1);
             S[i].y = min(S[i].y,N);
         }
         int ans = 0,last = 0;
         for(int i = 0;i < n;++i)
         {
             Update(S[i].x,S[i].y,1,N,1,1);
             while(last <= i && S[i].z - S[last].z > H)
                Update(S[last].x,S[last].y,1,N,1,-1),last++;
             ans = max(ans,maxv[1]);
         }
         printf("%d\n",ans);
    }
    return 0;
}
