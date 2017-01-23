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
const int maxn=3000000+10;
const int maxm=100000+10;
const int lev=19;
int ch[maxn][2],val[maxn],size;
int root[maxn];
int Newnode(int v)
{
    size++;
    ch[size][0]=ch[size][1]=0;
    val[size]=v;
    return size;
}
int insert(int x,int v,int dep)
{
    int rt=Newnode(val[x]+1);
    if(dep==-1) return rt;
    int k=(v>>dep)&1;
    ch[rt][k^1]=ch[x][k^1];
    ch[rt][k]=insert(ch[x][k],v,dep-1);
    return rt;
}
int query(int x,int y,int v,int r)
{
    int res=0;
    for(int i=lev;i>=0;--i)
    {
        int d=(r>>i)&1,k=(v>>i)&1;
        if(d)
            res+=val[ch[y][k]]-val[ch[x][k]];
        x=ch[x][k^d];y=ch[y][k^d];
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,N,M,W,Fa,Fc,X,L,R,A,B,C;
    scanf("%d",&T);
    while(T--)
    {
        W=0;
        scanf("%d%d",&N,&M);
        memset(root,0,sizeof(root));
        size=0;
        root[1]=insert(root[0],M,lev);
        for(int i=1;i<=N;++i)
        {
            scanf("%d%d%d%d%d%d%d%d",&Fa,&Fc,&X,&L,&R,&A,&B,&C);
            int F=((ll)Fa*W+Fc)%i;
            int ans=query(root[F],root[i],X,R+1)-query(root[F],root[i],X,L);
            printf("%d\n",ans);
            W=ans;
            root[i+1]=insert(root[i],((ll)W*A+B)%C,lev);
        }
    }
    return 0;
}
