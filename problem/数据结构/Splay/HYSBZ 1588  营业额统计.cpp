#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int ch[maxn][2],pre[maxn],val[maxn],root,tot;
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;
    val[rt]=v;
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
}
void Splay(int rt,int goal)
{
    while(pre[rt]!=goal)
    {
        int y=pre[rt];
        if(pre[y]==goal)
            Rotate(rt,ch[y][0]==rt);
        else
        {
            int kind=ch[pre[y]][0]==y;
            if(ch[y][kind]==rt)
            {
                Rotate(rt,kind^1);
                Rotate(rt,kind);
            }
            else
            {
                Rotate(y,kind);
                Rotate(rt,kind);
            }
        }
    }
    if(goal==0) root=rt;
}
bool insert(int v)
{
    int rt=root,kind;
    while(true)
    {
        if(val[rt]==v)
        {
            Splay(rt,0);
            return false;
        }
        kind=val[rt]<v?1:0;
        if(ch[rt][kind]==0) break;
        rt=ch[rt][kind];
    }
    NewNode(ch[rt][kind],rt,v);
    Splay(ch[rt][kind],0);
    return true;
}
int getpre(int v)
{
    int rt=ch[root][0];
    if(rt==0) return inf;
    while(ch[rt][1]) rt=ch[rt][1];
    return v-val[rt];
}
int getnext(int v)
{
    int rt=ch[root][1];
    if(rt==0) return inf;
    while(ch[rt][0]) rt=ch[rt][0];
    return val[rt]-v;
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    val[0]=0;tot=root=0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        int ans=0,v;
        for(int i=0;i<n;++i)
        {
            if(scanf("%d",&v)==EOF) v=0;
            if(i==0)
            {
                NewNode(root,0,v);
                ans+=v;
                continue;
            }
            if(!insert(v)) continue;
            ans+=min(getpre(v),getnext(v));
        }
        printf("%d\n",ans);
    }
    return 0;
}

