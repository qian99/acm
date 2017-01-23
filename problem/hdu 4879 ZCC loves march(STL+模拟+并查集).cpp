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
const int maxn=500000+10;
const int mod=1000000000+7;
map<pair<ll,ll> ,int>mp;
map<ll,ll>mpx,mpy;
set<int>sx[maxn],sy[maxn];
set<int>:: iterator it;
int Size[maxn],parents[maxn],id[maxn],tot;
int xcnt,ycnt;
ll pt[maxn][2];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[a]=b;
        Size[b]+=Size[a];
    }
}
int getxline(ll x)
{
    if(mpx.find(x)!=mpx.end()) return mpx[x];
    return mpx[x]=++xcnt;
}
int getyline(ll y)
{
    if(mpy.find(y)!=mpy.end()) return mpy[y];
    return mpy[y]=++ycnt;
}
void Init()
{
    mp.clear();
    mpx.clear();
    mpy.clear();
    xcnt=ycnt=tot=0;
}
inline ll Dis(ll x1,ll y1,ll x2, ll y2)
{
    x1%=mod;x2%=mod;y1%=mod;y2%=mod;
    return ((x1-x2)*(x1-x2)%mod+(y1-y2)*(y1-y2)%mod)%mod;
}
//将第i个军队添加到(x,y)点
void AddNode(int i,ll x,ll y)
{
    pair<ll,ll>pii=make_pair(x,y);
    int dx,dy;
    if(mp.find(pii)!=mp.end())
    {
        id[i]=mp[pii];
        Size[Find(id[i])]++;
    }
    else
    {
        id[i]=mp[pii]=++tot;
        parents[tot]=tot;
        Size[tot]=1;
        pt[id[i]][0]=x;
        pt[id[i]][1]=y;
    }
    dx=getxline(x);
    dy=getyline(y);
    sx[dx].insert(id[i]);
    sy[dy].insert(id[i]);
}
//将第i个军队从block k 删除
void DelNode(int i)
{
    int block=Find(id[i]);
    Size[block]--;
    if(Size[block]==0)
    {
        ll x,y;
        int dx,dy;
        x=pt[block][0];
        y=pt[block][1];
        dx=getxline(x);
        dy=getyline(y);
        sx[dx].erase(block);
        sy[dy].erase(block);
        mp.erase(make_pair(x,y));
    }
}
//将第i块,移动到第i块
void MoveBlock(int i,int j)
{
    pair<ll,ll>pii=make_pair(pt[i][0],pt[i][1]);
    mp.erase(pii);
    Uion(i,j);
}
ll Query(int i)
{
    int block=Find(id[i]);
    ll x,y,ans=0;
    int dx,dy;
    x=pt[block][0];
    y=pt[block][1];
    dx=getxline(x);
    dy=getyline(y);
    for(it=sx[dx].begin();it!=sx[dx].end();)
    {
        if((*it)==block) {it++;continue;}
        int rm=(*it);
        ans=(ans+Dis(pt[rm][0],pt[rm][1],x,y)*Size[rm]%mod)%mod;
        sx[dx].erase(it++);
        sy[dy].erase(rm);
        MoveBlock(rm,block);
    }
    for(it=sy[dy].begin();it!=sy[dy].end();)
    {
        if((*it)==block) {it++;continue;}
        int rm=(*it);
        ans=(ans+Dis(pt[rm][0],pt[rm][1],x,y)*Size[rm]%mod)%mod;
        sy[dy].erase(it++);
        sy[dx].erase(rm);
        MoveBlock(rm,block);
    }
    return ans;
}
void Update(int i,ll d,char c)
{
    int block=Find(id[i]);
    ll x=pt[block][0];
    ll y=pt[block][1];
    ll nx=x,ny=y;
    if(c=='U') nx-=d;
    else if(c=='D') nx+=d;
    else if(c=='L') ny-=d;
    else ny+=d;
    DelNode(i);
    AddNode(i,nx,ny);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    ll m,x,y,ans;
    char str[10];
    while(~scanf("%d%I64d\n",&n,&m))
    {
        ll lastans=0;
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d%I64d",&x,&y);
            AddNode(i,x,y);
        }
        int t;
        scanf("%d",&t);
        while(t--)
        {
            scanf("%s",str);
            scanf("%I64d",&x);
            x^=lastans;
            if(str[0]=='Q')
            {
                ans=Query(x);
                printf("%I64d\n",ans);
                lastans=ans;
            }
            else
            {
                scanf("%I64d\n",&y);
                Update(x,y,str[0]);
            }
        }
        for(int i=0;i<=xcnt;++i) sx[i].clear();
        for(int i=0;i<=ycnt;++i) sy[i].clear();
    }
    return 0;
}
