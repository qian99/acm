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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int ch[maxn][2],pre[maxn],size[maxn],val[maxn];
int root,tot,addv[maxn],flip[maxn],num[maxn];
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;
    size[rt]=1;
    val[rt]=v;
    addv[rt]=flip[rt]=0;
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
inline void PushDown(int rt)
{
    if(flip[rt])
    {
        flip[ch[rt][0]]^=1;
        flip[ch[rt][1]]^=1;
        swap(ch[rt][0],ch[rt][1]);
        flip[rt]=0;
    }
    if(addv[rt])
    {
        addv[ch[rt][0]]+=addv[rt];
        addv[ch[rt][1]]+=addv[rt];
        val[ch[rt][0]]+=addv[rt];
        val[ch[rt][1]]+=addv[rt];
        addv[rt]=0;
    }
}
void Rotate(int &x,int kind)
{
    int y=pre[x];
    PushDown(x);PushDown(y);
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    PushUp(y);
}
void Splay(int rt,int goal)
{
    PushDown(rt);
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
    PushUp(rt);
    if(goal==0) root=rt;
}
void RotateTo(int k,int goal)
{
    int rt=root;
    PushDown(rt);
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
        PushDown(rt);
    }
    Splay(rt,goal);
}
void Add(int L,int R,int v)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    addv[ch[ch[root][1]][0]]+=v;
    val[ch[ch[root][1]][0]]+=v;
}
void Cut(int L,int R)
{
    RotateTo(L+1,0);
    RotateTo(0,root);
    int rt=ch[ch[root][0]][1];
    ch[ch[root][0]][1]=0;
    PushUp(ch[root][0]);
    PushUp(root);
    RotateTo(R-L,0);
    ch[ch[root][1]][0]=rt;
    pre[rt]=ch[root][1];
    PushUp(ch[root][1]);
    PushUp(root);
}
void Reverse(int L,int R)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    int rt=ch[ch[root][1]][0];
    flip[ch[rt][0]]^=1;
    flip[ch[rt][1]]^=1;
    swap(ch[rt][0],ch[rt][1]);
}
void Insert(int pos,int v)
{
    RotateTo(pos,0);
    RotateTo(pos+1,root);
    NewNode(ch[ch[root][1]][0],ch[root][1],v);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Delete(int pos)
{
    RotateTo(pos-1,0);
    RotateTo(pos+1,root);
    ch[ch[root][1]][0]=0;
    PushUp(ch[root][1]);
    PushUp(root);
}
int Query(int pos)
{
    RotateTo(pos,0);
    return val[root];
}
void build(int L,int R,int &rt,int fa)
{
    if(L>R) return ;
    int mid=(L+R)>>1;
    NewNode(rt,fa,num[mid]);
    build(L,mid-1,ch[rt][0],rt);
    build(mid+1,R,ch[rt][1],rt);
    PushUp(rt);
}
void Init(int n)
{
    for(int i=1;i<=n;++i)
        scanf("%d",&num[i]);
    ch[0][0]=ch[0][1]=pre[0]=0;
    size[0]=val[0]=flip[0]=addv[0]=0;
    root=tot=0;
    NewNode(root,0,0);
    NewNode(ch[root][1],root,0);
    build(1,n,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k1,k2;
    int tcase=0;
    char str[20];
    while(~scanf("%d%d%d%d",&n,&m,&k1,&k2))
    {
        if(n==0&&m==0&&k1==0&&k2==0) break;
        printf("Case #%d:\n",++tcase);
        Init(n);
        int now=1,x,L,R;
        while(m--)
        {
            scanf("%s",str);
            if(str[0]=='a')
            {
                scanf("%d",&x);
                L=now,R=now+k2-1;
                if(R<=n) Add(L,R,x);
                else
                {
                    Add(L,n,x);
                    Add(1,k2-(n-L+1),x);
                }
            }
            else if(str[0]=='r')
            {
                L=now,R=now+k1-1;
                if(R<=n) Reverse(L,R);
                else
                {
                    Cut(R-n,n);
                    Reverse(n-k1+1,n);
                    now=n-k1+1;
                }
            }
            else if(str[0]=='i')
            {
                scanf("%d",&x);
                Insert(now,x);
                n++;
            }
            else if(str[0]=='d')
            {
                Delete(now);
                if(now==n) now=1;
                n--;
            }
            else if(str[0]=='m')
            {
                scanf("%d",&x);
                if(x==1) now--;
                else now++;
                if(now==0) now=n;
                else if(now==n+1) now=1;
            }
            else
            {
                printf("%d\n",Query(now));
            }
        }
    }
    return 0;
}
