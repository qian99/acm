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
typedef unsigned long long Ull;
const int mx=233;
const int maxn=400000+10;
Ull p[maxn],hash[maxn][2];
int ch[maxn][2],flip[maxn],pre[maxn],val[maxn],size[maxn],root,tot;
char str[maxn];
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=flip[rt]=0;
    size[rt]=1;
    pre[rt]=fa;
    hash[rt][0]=hash[rt][1]=val[rt]=v;
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    int len=size[ch[rt][0]];
    hash[rt][0]=hash[ch[rt][0]][0]+val[rt]*p[len]+hash[ch[rt][1]][0]*p[len+1];
    len=size[ch[rt][1]];
    hash[rt][1]=hash[ch[rt][1]][1]+val[rt]*p[len]+hash[ch[rt][0]][1]*p[len+1];
}
inline void fson(int rt)
{
    if(!rt) return ;
    swap(ch[rt][0],ch[rt][1]);
    swap(hash[rt][0],hash[rt][1]);
    flip[rt]^=1;
}
void PushDown(int rt)
{
    if(flip[rt])
    {
        fson(ch[rt][0]);
        fson(ch[rt][1]);
        flip[rt]=0;
    }
}
void traval(int x)
{
    if(x)
    {
        PushDown(x);
        traval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父节点 %2d size=%2d ,val=%2d, filp=%2d\n",x,ch[x][0],ch[x][1],pre[x],size[x],val[x],flip[x]);
        traval(ch[x][1]);
    }
}
void Debug()
{
    printf("%d\n",root);
    traval(root);
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    PushDown(y);PushDown(x);
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
void Insert(int k,int c)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    int rt=ch[root][1];
    NewNode(ch[rt][0],rt,c);
    PushUp(rt);
    PushUp(root);
}
void Delete(int p)
{
    RotateTo(p-1,0);
    RotateTo(p+1,root);
    ch[ch[root][1]][0]=0;
    PushUp(ch[root][1]);
    PushUp(root);
}
void Reverse(int L,int R)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    fson(ch[ch[root][1]][0]);
    PushUp(ch[root][1]);
    PushUp(root);
}
bool check(int x,int y,int len)
{
    Ull xval,yval;
    RotateTo(x-1,0);
    if(size[ch[root][1]]-1<len) return 0;
    RotateTo(x+len,root);
    int rt=ch[ch[root][1]][0];
    xval=hash[rt][flip[rt]];
    RotateTo(y-1,0);
    if(size[ch[root][1]]-1<len) return 0;
    RotateTo(y+len,root);
    rt=ch[ch[root][1]][0];
    yval=hash[rt][flip[rt]];
    return xval==yval;
}
int Lcp(int x,int y)
{
    int L=1,R=size[root]-1;
    if(!check(x,y,1)) return 0;
    while(R-L>1)
    {
        int mid=(L+R)>>1;
        if(check(x,y,mid)) L=mid;
        else R=mid;
    }
    return L;
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,str[m]-'0');
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init(int n)
{
    ch[0][0]=ch[0][1]=size[0]=0;
    hash[0][0]=hash[0][1]=0;
    flip[0]=pre[0]=val[0]=0;
    root=tot=0;
    NewNode(root,0,0);
    NewNode(ch[root][1],root,0);
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*mx;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        scanf("%s",str);
        Init(n);
//        Debug();
        int type,p1,p2,c;
        while(m--)
        {
            scanf("%d%d",&type,&p1);
            if(type==1)
            {
                scanf("%d",&c);
                Insert(p1,c);
//                Debug();
            }
            else if(type==2)
            {
                Delete(p1);
            }
            else if(type==3)
            {
                scanf("%d",&p2);
                Reverse(p1,p2);
                //Debug();
            }
            else
            {
                scanf("%d",&p2);
                int ans=Lcp(p1,p2);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
