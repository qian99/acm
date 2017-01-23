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
const int mod=1000000;
int ch[maxn][2],pre[maxn],val[maxn],root,tot;
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;val[rt]=v;
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
void Insert(int v)
{
    if(root==0)
    {
        NewNode(root,0,v);
        return ;
    }
    int rt=root,kind;
    while(true)
    {
        kind=val[rt]<v?1:0;
        if(ch[rt][kind]==0) break;
        rt=ch[rt][kind];
    }
    NewNode(ch[rt][kind],rt,v);
}
void DelRoot()
{
    int rt=root;
    if(!ch[rt][0]&&!ch[rt][1]) {root=0;return;}
    if(ch[rt][0]==0)
    {
        root=ch[rt][1];
        pre[root]=0;
        return ;
    }
    int rc=ch[rt][0];
    while(ch[rc][1])
        rc=ch[rc][1];
    Splay(rc,rt);
    ch[rc][1]=ch[rt][1];
    pre[ch[rt][1]]=rc;
    pre[rc]=0;
    root=rc;
}
int getminv(int v)
{
    int rt=root,kind;
    while(true)
    {
        kind=val[rt]<v?1:0;
        if(ch[rt][kind]==0) break;
        rt=ch[rt][kind];
    }
    Splay(rt,0);
    int x,y;
    if(kind==0)
    {
        y=rt;
        x=ch[rt][0];
        while(ch[x][1]) x=ch[x][1];
    }
    else
    {
        x=rt;
        y=ch[rt][1];
        while(ch[y][0]) y=ch[y][0];
    }
    if(x!=0&&(y==0||(v-val[x]<=val[y]-v)))
    {
        Splay(x,0);
        DelRoot();
        return v-val[x];
    }
    Splay(y,0);
    DelRoot();
    return val[y]-v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        int nowt,type,v;
        ch[0][0]=ch[0][1]=0;
        val[0]=0;root=tot=0;
        int sum=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&type,&v);
            if(root==0)
            {
                NewNode(root,0,v);
                nowt=type;
                continue;
            }
            else if(type==nowt)
                Insert(v);
            else
                sum=(sum+getminv(v))%mod;
        }
        printf("%d\n",sum);
    }
    return 0;
}

