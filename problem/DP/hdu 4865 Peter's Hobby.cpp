#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
const int maxn=55;
double p[3][3]={{0.5,0.375,0.125},
                {0.25,0.125,0.625},
                {0.25,0.375,0.375}
                };
double q[3][4]={{0.6,0.2,0.15,0.05},
                {0.25,0.3,0.2,0.25},
                {0.05,0.10,0.35,0.50}
                };
char * weather[3]={(char*)"Sunny",(char*)"Cloudy",(char*)"Rainy"};
double dp[maxn][3];
int x[maxn],pa[maxn][3],ans[maxn];
int getx(char * s)
{
    if(strcmp(s,"Dry")==0) return 0;
    if(strcmp(s,"Dryish")==0) return 1;
    if(strcmp(s,"Damp")==0) return 2;
    return 3;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[10];
    int t,tcase=0,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            x[i]=getx(str);
        }
        for(int i=1;i<=n;++i)
            for(int j=0;j<3;++j)
                dp[i][j]=log(0);
        memset(pa,0,sizeof(pa));
        dp[1][0]=log(0.63)+log(q[0][x[1]]);
        dp[1][1]=log(0.17)+log(q[1][x[1]]);
        dp[1][2]=log(0.20)+log(q[2][x[1]]);
        for(int i=2;i<=n;++i)
        {
            for(int j=0;j<3;++j)
            {
                for(int k=0;k<3;++k)
                {
                    double tmp=dp[i-1][k]+log(p[k][j])+log(q[j][x[i]]);
                    if(tmp>dp[i][j])
                    {
                        dp[i][j]=tmp;
                        pa[i][j]=k;
                    }
                }
            }
        }
        int pos=0;
        for(int i=0;i<3;++i)
            if(dp[n][i]>dp[n][pos]) pos=i;
        ans[n]=pos;
        for(int i=n-1;i>=1;--i)
        {
            pos=pa[i+1][pos];
            ans[i]=pos;
        }
        printf("Case #%d:\n",++tcase);
        for(int i=1;i<=n;++i)
            printf("%s\n",weather[ans[i]]);
    }
    return 0;
}
