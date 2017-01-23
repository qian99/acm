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
const int maxn=10000+10;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};
struct DLX
{
    int U[maxn],D[maxn],L[maxn],R[maxn];
    int cnt[maxn],col[maxn],row[maxn],head[maxn],tot,size;
    bool vis[55];
    void Init(int n)
    {
        for(int i=0;i<=n;++i)
        {
            L[i]=i-1;R[i]=i+1;
            U[i]=D[i]=i;cnt[i]=0;
        }
        L[0]=n;R[n]=0;size=n+1;
        tot=inf;
        memset(head,0xff,sizeof(head));
    }
    void AddLink(int r,int c)
    {
        U[size]=U[c];D[size]=c;
        D[U[c]]=size;U[c]=size;
        if(head[r]==-1) head[r]=L[size]=R[size]=size;
        else
        {
            int h=head[r];
            L[size]=L[h];R[size]=h;
            R[L[h]]=size;L[h]=size;
        }
        cnt[c]++;row[size]=r;col[size++]=c;
    }
    void remove(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
        {
            L[R[i]]=L[i];
            R[L[i]]=R[i];
        }
    }
    void restore(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    int h()
    {
        memset(vis,0,sizeof(vis));
        int res=0;
        for(int i=R[0];i;i=R[i])
        {
            if(vis[i]) continue;
            res++;
            for(int j=U[i];j!=i;j=U[j])
                for(int k=R[j];k!=j;k=R[k])
                    vis[col[k]]=true;
        }
        return res;
    }
    void Dancing(int x)
    {
        if(x+h()>=tot) return ;
        if(R[0]==0)
        {
            tot=min(tot,x);
            return ;
        }
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(cnt[c]>cnt[i]) c=i;
        for(int i=U[c];i!=c;i=U[i])
        {
            remove(i);
            for(int j=R[i];j!=i;j=R[j]) remove(j);
            Dancing(x+1);
            for(int j=L[i];j!=i;j=L[j]) restore(j);
            restore(i);
        }
    }
}dlx;
char mat[20][20];
int id[20][20];
int n,m;
inline bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
int findwall(int x,int y,int d)
{
    int dx,dy;
    while(true)
    {
        dx=x+dirx[d];
        dy=y+diry[d];
        if(!check(dx,dy)||mat[dx][dy]=='*') return -1;
        if(mat[dx][dy]=='#') return id[dx][dy];
        x=dx;y=dy;
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        int N=0,M=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",mat[i]);
            for(int j=0;j<m;++j)
                if(mat[i][j]=='#') id[i][j]=++N;
                else if(mat[i][j]=='.') id[i][j]=++M;
        }
        dlx.Init(N);
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            if(mat[i][j]=='.')
            {
                for(int k=0;k<4;++k)
                {
                    int p=findwall(i,j,k);
                    if(p!=-1) dlx.AddLink(id[i][j],p);
                }
            }
        dlx.Dancing(0);
        printf("%d\n",dlx.tot);
    }
    return 0;
}
