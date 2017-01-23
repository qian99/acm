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
const int maxn=100+10;
int dp[maxn][maxn][maxn],pre[maxn][maxn][maxn][3];
char s1[maxn],s2[maxn],vir[maxn];
char ans[maxn];
int next[maxn];
inline void getm(int x,int y,int z,int x1,int y1,int z1,int v)
{
    if(dp[x1][y1][z1]+v>dp[x][y][z])
    {
        dp[x][y][z]=dp[x1][y1][z1]+v;
        pre[x][y][z][0]=x1;
        pre[x][y][z][1]=y1;
        pre[x][y][z][2]=z1;
    }
}
void getFail(char *P,int *f,int n)
{
    f[0]=f[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=f[i];
        while(j>0&&P[i]!=P[j]) j=f[j];
        f[i+1]=P[i]==P[j]?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",s1);
    scanf("%s",s2);
    scanf("%s",vir);
    int n=strlen(s1);
    int m=strlen(s2);
    int t=strlen(vir);
    getFail(vir,next,t);
    memset(dp,0xff,sizeof(dp));
    memset(pre,0xff,sizeof(pre));
    dp[0][0][0]=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            for(int k=0;k<t;++k)
            {
                getm(i+1,j,k,i,j,k,0);
                getm(i,j+1,k,i,j,k,0);
                if(dp[i][j][k]>=0&&s1[i]==s2[j])
                {
                    if(s1[i]==vir[k])
                    {
                        getm(i+1,j+1,k+1,i,j,k,1);
                    }
                    else
                    {
                        int p=next[k];
                        while(p>0&&s1[i]!=vir[p]) p=next[p];
                        getm(i+1,j+1,p+(s1[i]==vir[p]),i,j,k,1);
                    }
                }
            }
    int x,y,z,maxv=-1;
    for(int k=0;k<t;++k)
        if(dp[n][m][k]>maxv)
        {
            maxv=dp[n][m][k];
            z=k;
        }
    if(maxv<=0) printf("0\n");
    else
    {
        x=n;y=m;
        int len=maxv;
        while(pre[x][y][z][0]!=-1)
        {
            int xx,yy,zz;
            xx=pre[x][y][z][0];
            yy=pre[x][y][z][1];
            zz=pre[x][y][z][2];
            if(x-xx==1&&y-yy==1&&s1[x-1]==s2[y-1]) ans[maxv--]=s1[x-1];
            x=xx;y=yy;z=zz;
        }
        for(int i=1;i<=len;++i)
            printf("%c",ans[i]);
        printf("\n");
    }
    return 0;
}
