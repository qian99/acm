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
const int maxn=100000+10;
const int rp=233;
Ull hash[maxn][2],pw[maxn];
int ch[maxn][2],size[maxn],val[maxn],flip[maxn];
int pre[maxn],p[maxn<<1],root,tot,cnt;
char str[maxn],s[maxn<<1];
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=flip[rt]=0;
    pre[rt]=fa;size[rt]=1;
    hash[rt][0]=hash[rt][1]=val[rt]=v;
}
inline void PushUp(int rt)
{
    int ls=ch[rt][0],rs=ch[rt][1];
    size[rt]=size[ls]+size[rs]+1;
    hash[rt][0]=hash[ls][0]+val[rt]*pw[size[ls]]+hash[rs][0]*pw[(size[ls]+1)];
    hash[rt][1]=hash[rs][1]+val[rt]*pw[size[rs]]+hash[ls][1]*pw[(size[rs]+1)];
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
void Modify(int k,int v)
{
    RotateTo(k-1,0);
    RotateTo(k+1,root);
    int rt=ch[ch[root][1]][0];
    hash[rt][0]=hash[rt][1]=val[rt]=v;
    PushUp(ch[root][1]);
    PushUp(root);
}
void Reverse(int L,int R)
{
    if(L>R) swap(L,R);
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
    if(x>y) swap(x,y);
    int l=1,r=size[root]-1;
    if(!check(x,y,1)) return 0;
    while(r-l>1)
    {
        int m=(l+r)>>1;
        if(check(x,y,m)) l=m;
        else r=m;
    }
    return l;
}
void dfs(int rt)
{
    if(rt)
    {
        PushDown(rt);
        dfs(ch[rt][0]);
        str[cnt++]=val[rt];
        dfs(ch[rt][1]);
    }
}
int Palindrome()
{
    cnt=0;
    dfs(root);
    str[cnt-1]=0;
    int n=0;
    s[n++]='$';s[n++]='#';
    for(int i=1;str[i];++i)
    {
        s[n++]=str[i];
        s[n++]='#';
    }
    int mx=0,id=0,ans=0;
    p[0]=0;
    for(int i=1;i<n;++i)
    {
        p[i]=1;
        if(mx>i) p[i]=min(p[id*2-i],mx-i);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>mx)
        {
            mx=i+p[i];
            id=i;
        }
        if(p[i]>ans) ans=p[i];
    }
    return ans-1;
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,str[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init(int n)
{
    ch[0][0]=ch[0][1]=pre[0]=0;
    hash[0][0]=hash[0][1]=0;
    flip[0]=val[0]=size[0]=0;
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
    pw[0]=1;
    for(int i=1;i<maxn;++i) pw[i]=pw[i-1]*rp;
    int n,m,a,b;
    char qs[15];
    while(~scanf("%s",str))
    {
        n=strlen(str);
        Init(n);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%s",qs);
            if(qs[0]=='P') printf("%d\n",Palindrome());
            else if(qs[0]=='M')
            {
                scanf("%d%s",&a,qs);
                Modify(a,qs[0]);
            }
            else
            {
                scanf("%d%d",&a,&b);
                if(qs[0]=='R') Reverse(a,b);
                else printf("%d\n",Lcp(a,b));
            }
        }
    }
    return 0;
}
