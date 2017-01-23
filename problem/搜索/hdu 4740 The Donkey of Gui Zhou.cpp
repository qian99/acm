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
const int maxn=1000+10;
const int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
bool visa[maxn][maxn],visb[maxn][maxn];
int n;
bool check(int x,int y,int wh)
{
    if(wh) return x>=0&&x<n&&y>=0&&y<n&&!visa[x][y];
    return x>=0&&x<n&&y>=0&&y<n&&!visb[x][y];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int xa,ya,xb,yb,da,db;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(visa,0,sizeof(visa));
        memset(visb,0,sizeof(visb));
        scanf("%d%d%d",&xa,&ya,&da);
        scanf("%d%d%d",&xb,&yb,&db);
        bool flag=false;
        bool fa=true,fb=true;
        int dx,dy;
        while(true)
        {
            if(xa==xb&&ya==yb)
            {
                flag=true;
                break;
            }
            if(!fa&&!fb) break;
            visa[xa][ya]=visb[xb][yb]=true;
            if(fa)
            {
                dx=xa+dir[da][0];
                dy=ya+dir[da][1];
                if(check(dx,dy,1))
                {
                    xa=dx;ya=dy;
                }
                else
                {
                    da=(da+1)%4;
                    dx=xa+dir[da][0];
                    dy=ya+dir[da][1];
                    if(check(dx,dy,1))
                        xa=dx,ya=dy;
                    else fa=false;
                }
            }
            if(fb)
            {
                dx=xb+dir[db][0];
                dy=yb+dir[db][1];
                if(check(dx,dy,0))
                {
                    xb=dx;yb=dy;
                }
                else
                {
                    db=(db-1+4)%4;
                    dx=xb+dir[db][0];
                    dy=yb+dir[db][1];
                    if(check(dx,dy,0))
                        xb=dx,yb=dy;
                    else fb=false;
                }
            }
        }
        if(flag)
          printf("%d %d\n",xa,ya);
        else printf("-1\n");
    }
    return 0;
}
