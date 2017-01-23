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
int ch[maxn][2],pre[maxn],maxv[maxn],val[maxn],num[maxn];
int size[maxn],tot,root;
void Newnode(int &rt,int fa,int v,int v2)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;
    maxv[rt]=val[rt]=v;
    size[rt]=1;
    num[rt]=v2;
}
void PushUp(int rt)
{
    maxv[rt]=max(maxv[ch[rt][0]],maxv[ch[rt][1]]);
    maxv[rt]=max(maxv[rt],val[rt]);
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    PushUp(y);
}
void Splay(int rt,int goal)
{
    while(pre[rt]!=goal)
    {
        int y=pre[rt];
        if(pre[y]==goal)
        {
            Rotate(rt,ch[y][0]==rt);
        }
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
    PushUp(rt);
    if(goal==0) root=rt;
}
void RotateTo(int k,int goal)
{
    int rt=root;
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
    }
    Splay(rt,goal);
}
void RotateMax(int v,int goal)
{
    int rt=root;
    while(val[rt]!=v)
    {
        if(maxv[ch[rt][0]]==v)
            rt=ch[rt][0];
        else
            rt=ch[rt][1];
    }
    Splay(rt,goal);
}
int getMax(int rt)
{
    while(ch[rt][1])
    {
        rt=ch[rt][1];
    }
    return rt;
}
int DelRoot()
{
    int rt=root;
    if(ch[rt][0]==0)
    {
        root=ch[rt][1];
        pre[ch[rt][1]]=0;
        return num[rt];
    }
    int rm=getMax(ch[rt][0]);
    Splay(rm,rt);
    pre[ch[rt][1]]=rm;
    ch[rm][1]=ch[rt][1];
    pre[rm]=0;
    root=rm;
    PushUp(root);
    return num[rt];
}
bool compair(int ra,int rb)
{
    return (val[ra]<val[rb]&&num[ra]==num[rb])||(num[ra]<num[rb]);
}
void insert(int id,int v)
{
    int rt=root,k;
    int rb;
    Newnode(rb,0,id,v);
    while(true)
    {
        if(compair(rt,rb))
        {
            if(ch[rt][1]) rt=ch[rt][1];
            else
            {
                k=1;
                break;
            }
        }
        else
        {
            if(ch[rt][0]) rt=ch[rt][0];
            else
            {
                k=0;
                break;
            }
        }
    }
    ch[rt][k]=rb;
    pre[rb]=rt;
    PushUp(rt);
    Splay(rt,0);
}
void Init()
{
    pre[0]=ch[0][0]=ch[0][1]=0;
    size[0]=0;
    root=tot=0;
    Newnode(root,0,-inf,-inf);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    char str[10];
    while(t--)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        Init();
        int cnt=0,v,ans;
        while(n--)
        {
            scanf("%s",str);
            if(str[0]=='P')
            {
                scanf("%d",&v);
                insert(cnt+1,v);
                cnt++;
            }
            else if(str[0]=='Q')
            {
                if(cnt<k) RotateTo(cnt,0);
                else RotateTo(k,0);
                printf("%d\n",num[root]);
            }
            else
            {
                RotateMax(cnt,0);
                ans=DelRoot();
                cnt--;
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}

