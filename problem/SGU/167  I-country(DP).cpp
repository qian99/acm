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
struct Node
{
    int i,j,k,sx,sy,l,val;
    Node(){}
    Node(int a,int b,int c,int d,int e,int f,int g)
    {i=a;j=b;k=c;sx=d;sy=e;l=f;val=g;}
}node;
int a[20][20],sum[20][20],dp[16][16][16][2][2][230];
int pre[16][16][16][2][2][230][2];
int n,m,K;
void cal(int i,int j,int k,int sx,int sy,int l)
{
    int x=1,y=m;
    if(sx==1) x=j;
    if(sy==1) y=k;
    int sl,sr,tmp;
    for(int a=x;a<=k;++a)
        for(int b=max(a,j);b<=y;++b)
        {
            if(b-a+1+l>K) continue;
            if(a>j) sl=1; else sl=sx;
            if(b<k) sr=1; else sr=sy;
            tmp=dp[i][j][k][sx][sy][l]+sum[i+1][b]-sum[i+1][a-1];
            if(dp[i+1][a][b][sl][sr][b-a+l+1]<=tmp)
            {
                dp[i+1][a][b][sl][sr][b-a+l+1]=tmp;
                pre[i+1][a][b][sl][sr][b-a+l+1][0]=j;
                pre[i+1][a][b][sl][sr][b-a+l+1][1]=k;
                if(b-a+l+1==K&&tmp>node.val)
                    node=Node(i+1,a,b,sl,sr,b-a+l+1,tmp);
            }
        }
}
void getpath(int x,int l,int r,int sx,int sy,int cnt,int val)
{
    if(cnt==0) return ;
    int L=pre[x][l][r][sx][sy][cnt][0];
    int R=pre[x][l][r][sx][sy][cnt][1];
    if(L!=-1&&R!=-1&&x!=1)
    for(int i=0;i<=sx;++i)
        for(int j=0;j<=sy;++j)
        {
            if(dp[x-1][L][R][i][j][cnt-(r-l+1)]+sum[x][r]-sum[x][l-1]==val)
            {
                getpath(x-1,L,R,i,j,cnt-(r-l+1),val-sum[x][r]+sum[x][l-1]);
                break;
            }
        }
    for(int y=l;y<=r;++y)
        printf("%d %d\n",x,y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&K))
    {
        for(int i=1;i<=n;++i)
        {
            sum[i][0]=0;
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&a[i][j]);
                sum[i][j]=sum[i][j-1]+a[i][j];
            }
        }
        memset(dp[1],0xff,sizeof(dp[1]));
        node.val=-1;
        for(int i=1;i<=m;++i)
            for(int j=i;j<=m;++j)
                if(j-i+1<=K)
                {
                    dp[1][i][j][0][0][j-i+1]=sum[1][j]-sum[1][i-1];
                    pre[1][i][j][0][0][j-i+1][0]=pre[1][i][j][0][0][j-i+1][1]=-1;
                    if(j-i+1==K&&sum[1][j]-sum[1][i-1]>node.val)
                        node=Node(1,i,j,0,0,j-i+1,sum[1][j]-sum[1][i-1]);
                }
        for(int i=1;i<n;++i)
        {
            memset(dp[i+1],0xff,sizeof(dp[i+1]));
            for(int j=1;j<=m;++j)
                for(int k=j;k<=m;++k)
                    if(k-j+1<=K)
                    {
                        dp[i+1][j][k][0][0][k-j+1]=sum[i+1][k]-sum[i+1][j-1];
                        pre[i+1][j][k][0][0][k-j+1][0]=pre[i+1][j][k][0][0][k-j+1][1]=-1;
                        if(k-j+1==K&&sum[i+1][k]-sum[i+1][j-1]>node.val)
                            node=Node(i+1,j,k,0,0,k-j+1,sum[i+1][k]-sum[i+1][j-1]);
                    }
            for(int j=1;j<=m;++j)
             for(int k=j;k<=m;++k)
              for(int l=k-j+1;l<K;++l)
              {
                if(dp[i][j][k][0][0][l]!=-1) cal(i,j,k,0,0,l);
                if(dp[i][j][k][1][0][l]!=-1) cal(i,j,k,1,0,l);
                if(dp[i][j][k][0][1][l]!=-1) cal(i,j,k,0,1,l);
                if(dp[i][j][k][1][1][l]!=-1) cal(i,j,k,1,1,l);
              }
        }
        if(K)
        {
            printf("Oil : %d\n",node.val);
            getpath(node.i,node.j,node.k,node.sx,node.sy,K,node.val);
        }
        else printf("Oil : 0\n");
    }
    return 0;
}

