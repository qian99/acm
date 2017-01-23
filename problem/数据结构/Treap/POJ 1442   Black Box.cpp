#include <iostream>
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
const int maxn=30000+1000;
int ch[maxn][2],val[maxn],counts[maxn],r[maxn],size[maxn],tot,root;
void Newnode(int &rt,int v)
{
    rt=++tot;
    val[rt]=v;
    ch[rt][0]=ch[rt][1]=0;
    counts[rt]=size[rt]=1;
    r[rt]=rand();
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+counts[rt];
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
        Newnode(rt,v);
        return ;
    }
    if(v==val[rt]) counts[rt]++;
    else
    {
        int kind=(v>val[rt]);
        Insert(ch[rt][kind],v);
        if(r[ch[rt][kind]]<r[rt])
            Rotate(rt,kind^1);
    }
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][0]]>=k) return select(ch[rt][0],k);
    if(size[ch[rt][0]]+counts[rt]>=k) return val[rt];
    return select(ch[rt][1],k-size[ch[rt][0]]-counts[rt]);
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    size[0]=counts[0]=val[0]=0;
    tot=root=0;
    Newnode(root,2000000001);
}
int num[maxn],query[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=0;i<m;++i)
            scanf("%d",&num[i]);
        for(int i=0;i<n;++i)
            scanf("%d",&query[i]);
        Init();
        int s=0,cnt=0;
        for(int i=0;i<m;++i)
        {
            Insert(root,num[i]);
            if(s>=n) break;
            while(size[root]-1==query[s])
            {
                printf("%d\n",select(root,++cnt));
                s++;
            }
        }
    }
    return 0;
}
