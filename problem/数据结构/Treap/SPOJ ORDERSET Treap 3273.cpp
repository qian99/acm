#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500000+10;
int ch[maxn][2],val[maxn],r[maxn],size[maxn],tot,root;
void NewNode(int &rt,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    val[rt]=v;r[rt]=rand();
    size[rt]=1;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
void Rotate(int &x,int kind)
{
    int y=ch[x][kind^1];
    ch[x][kind^1]=ch[y][kind];
    ch[y][kind]=x;
    PushUp(x);PushUp(y);
    x=y;
}
void Insert(int &rt,int v)
{
    if(rt==0)
    {
        NewNode(rt,v);
        return ;
    }
    if(val[rt]==v) return;
    int kind=(v>val[rt]);
    Insert(ch[rt][kind],v);
    if(r[ch[rt][kind]]<r[rt])
        Rotate(rt,kind^1);
    PushUp(rt);
}
void remove(int &rt,int v)
{
    if(val[rt]==v)
    {
        if(!ch[rt][0]&&!ch[rt][1])
        {rt=0;return;}
        else
        {
            int kind=r[ch[rt][0]]<r[ch[rt][1]];
            Rotate(rt,kind);
            remove(rt,v);
        }
    }
    else if(!ch[rt][0]&&!ch[rt][1]) return ;
    else remove(ch[rt][v>val[rt]],v);
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][0]]>=k) return select(ch[rt][0],k);
    if(size[ch[rt][0]]+1>=k) return val[rt];
    return select(ch[rt][1],k-(size[ch[rt][0]]+1));
}
int getcounts(int rt,int v)
{
    if(rt==0) return 0;
    if(val[rt]==v) return size[ch[rt][0]];
    if(val[rt]<v) return size[ch[rt][0]]+1+getcounts(ch[rt][1],v);
    return getcounts(ch[rt][0],v);
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    val[0]=0;size[0]=0;
    root=tot=0;
    r[0]=(1LL<<31)-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int q,x;
    char str[5];
    while(~scanf("%d",&q))
    {
        Init();
        while(q--)
        {
            scanf("%s%d",str,&x);
            if(str[0]=='I')
                Insert(root,x);
            else if(str[0]=='D')
                remove(root,x);
            else if(str[0]=='K')
            {
                if(size[root]<x)
                    printf("invalid\n");
                else
                    printf("%d\n",select(root,x));
            }
            else
                printf("%d\n",getcounts(root,x));
        }
    }
    return 0;
}
