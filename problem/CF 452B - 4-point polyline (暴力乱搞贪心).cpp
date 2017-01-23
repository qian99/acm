#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    if(n==0)
    {
        printf("0 1\n");
        printf("0 %d\n",m);
        printf("0 0\n");
        printf("0 %d\n",m-1);
    }
    else if(m==0)
    {
        printf("1 0\n");
        printf("%d 0\n",n);
        printf("0 0\n");
        printf("%d 0\n",n-1);
    }
    else
    {
        if(n>m)
        {
            double v1=sqrt(n*n+m*m)*2+n;
            double v2=sqrt(n*n+m*m);
            int x1,y1,x2,y2;
            double maxlen=0,tmp;
            for(int i=0;i<=n;++i)
                for(int j=0;j<=m;++j)
                {
                    if(i==0&&j==0) continue;
                    if(i==n&&j==m) continue;
                    tmp=sqrt(i*i+j*j);
                    if(tmp>maxlen)
                    {
                        maxlen=tmp;
                        x1=i;
                        y1=j;
                    }
                }
            v2+=maxlen;
            maxlen=0;
            for(int i=0;i<=n;++i)
                for(int j=0;j<=m;++j)
                {
                    if(i==0&&j==0) continue;
                    if(i==n&&j==m) continue;
                    if(i==x1&&j==y1) continue;
                    tmp=sqrt((n-i)*(n-i)+(m-j)*(m-j));
                    if(tmp>maxlen)
                    {
                        maxlen=tmp;
                        x2=i;
                        y2=j;
                    }
                }
            v2+=maxlen;
            if(v1>v2)
            {
                printf("0 0\n");
                printf("%d %d\n",n,m);
                printf("%d %d\n",0,m);
                printf("%d %d\n",n,0);
            }
            else
            {
                printf("%d %d\n",x1,y1);
                printf("%d %d\n",0,0);
                printf("%d %d\n",n,m);
                printf("%d %d\n",x2,y2);
            }
        }
        else
        {
            double v1=sqrt(n*n+m*m)*2+m;
            double v2=sqrt(n*n+m*m);
            int x1,y1,x2,y2;
            double maxlen=0,tmp;
            for(int i=0;i<=n;++i)
                for(int j=0;j<=m;++j)
                {
                    if(i==0&&j==0) continue;
                    if(i==n&&j==m) continue;
                    tmp=sqrt(i*i+j*j);
                    if(tmp>maxlen)
                    {
                        maxlen=tmp;
                        x1=i;
                        y1=j;
                    }
                }
            v2+=maxlen;
            maxlen=0;
            for(int i=0;i<=n;++i)
                for(int j=0;j<=m;++j)
                {
                    if(i==0&&j==0) continue;
                    if(i==n&&j==m) continue;
                    if(i==x1&&j==y1) continue;
                    tmp=sqrt((n-i)*(n-i)+(m-j)*(m-j));
                    if(tmp>maxlen)
                    {
                        maxlen=tmp;
                        x2=i;
                        y2=j;
                    }
                }
            v2+=maxlen;
            if(v1>v2)
            {
                printf("%d %d\n",0,0);
                printf("%d %d\n",n,m);
                printf("%d %d\n",n,0);
                printf("%d %d\n",0,m);
            }
            else
            {
                printf("%d %d\n",x1,y1);
                printf("%d %d\n",0,0);
                printf("%d %d\n",n,m);
                printf("%d %d\n",x2,y2);
            }
        }
    }
    return 0;
}