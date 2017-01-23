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
struct Body
{
    int la,lb;
    bool operator <(const Body &a ) const
    {
        return la+lb<a.la+a.lb;
    }
};
double cal(double a,double b,double c)
{
    double p=(a+b+c)/2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
Body b[5];
bool vis[3][2];
int x[3],y[3];
double res,tmp;
void finds(int u)
{
    bool flag=true;
    for(int i=0;i<3;++i)
    {
        if(!vis[i][0]) {flag=false;break;}
        if(!vis[i][1]) {flag=false;break;}
    }
    if(x[0]==0||x[1]==0||x[2]==0) flag=false;
    if(flag)
    {
        y[0]=x[0];y[1]=x[1];y[2]=x[2];
        sort(y,y+3);
        if(y[0]+y[1]>y[2])
        {
            tmp=cal(y[0],y[1],y[2]);
            res=max(tmp,res);
        }
        return ;
    }
    if(u>=3) return ;
    for(int i=0;i<3;++i)
    {
        if(!vis[i][0])
        {
            vis[i][0]=vis[i][1]=true;
            x[u]+=b[i].la;
            x[(u+1)%3]+=b[i].lb;
            finds(u+1);
            x[u]-=b[i].la;
            x[(u+1)%3]-=b[i].lb;

            x[u]+=b[i].lb;
            x[(u+1)%3]+=b[i].la;
            finds(u+1);
            x[u]-=b[i].lb;
            x[(u+1)%3]-=b[i].la;

            x[u]+=b[i].la+b[i].lb;
            finds(u);
            finds(u+1);
            x[u]-=(b[i].la+b[i].lb);
            vis[i][0]=vis[i][1]=false;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&b[0].la,&b[0].lb))
    {
        scanf("%d%d",&b[1].la,&b[1].lb);
        scanf("%d%d",&b[2].la,&b[2].lb);
        sort(b,b+3);
        res=0;
        memset(vis,0,sizeof(vis));
        memset(x,0,sizeof(x));
        finds(0);
        printf("%.9lf\n",res);
    }
    return 0;
}

