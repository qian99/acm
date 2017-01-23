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
const int maxn=500+10;
int a[maxn][maxn];
int maxv[maxn<<2][maxn<<2],minv[maxn<<2][maxn<<2];
int vmax,vmin,xL,xR,yL,yR,val,N,M;
void buildY(int xr,int x,int l,int r,int rt)
{
    if(l==r)
    {
        if(x>0) maxv[xr][rt]=minv[xr][rt]=a[x][l];
        else
        {
            maxv[xr][rt]=max(maxv[xr<<1][rt],maxv[xr<<1|1][rt]);
            minv[xr][rt]=min(minv[xr<<1][rt],minv[xr<<1|1][rt]);
        }
        return ;
    }
    int m=(l+r)>>1;
    buildY(xr,x,l,m,rt<<1);
    buildY(xr,x,m+1,r,rt<<1|1);
    maxv[xr][rt]=max(maxv[xr][rt<<1],maxv[xr][rt<<1|1]);
    minv[xr][rt]=min(minv[xr][rt<<1],minv[xr][rt<<1|1]);
}
void buildX(int l,int r,int rt)
{
    if(l==r)
    {
        buildY(rt,l,1,M,1);
        return ;
    }
    int m=(l+r)>>1;
    buildX(l,m,rt<<1);
    buildX(m+1,r,rt<<1|1);
    buildY(rt,-1,1,M,1);
}
void QueryY(int xr,int l,int r,int rt)
{
    if(l>=yL&&r<=yR)
    {
        vmax=max(vmax,maxv[xr][rt]);
        vmin=min(vmin,minv[xr][rt]);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=yL) QueryY(xr,l,m,rt<<1);
    if(m<yR) QueryY(xr,m+1,r,rt<<1|1);
}
void QueryX(int l,int r,int rt)
{
    if(l>=xL&&r<=xR)
    {
        QueryY(rt,1,M,1);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=xL) QueryX(l,m,rt<<1);
    if(m<xR) QueryX(m+1,r,rt<<1|1);
}
void UpdateY(int xr,int x,int l,int r,int rt)
{
    if(l==r)
    {
        if(x>0)
        {
            maxv[xr][rt]=minv[xr][rt]=val;
        }
        else
        {
            maxv[xr][rt]=max(maxv[xr<<1][rt],maxv[xr<<1|1][rt]);
            minv[xr][rt]=min(minv[xr<<1][rt],minv[xr<<1|1][rt]);
        }
        return ;
    }
    int m=(l+r)>>1;
    if(m>=yL) UpdateY(xr,x,l,m,rt<<1);
    else UpdateY(xr,x,m+1,r,rt<<1|1);
    maxv[xr][rt]=max(maxv[xr][rt<<1],maxv[xr][rt<<1|1]);
    minv[xr][rt]=min(minv[xr][rt<<1],minv[xr][rt<<1|1]);
}
void UpdateX(int l,int r,int rt)
{
    if(l==r)
    {
        UpdateY(rt,l,1,M,1);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=xL) UpdateX(l,m,rt<<1);
    else UpdateX(m+1,r,rt<<1|1);
    UpdateY(rt,-1,1,M,1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[5];
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            scanf("%d",&a[i][j]);
    buildX(1,N,1);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%s",str);
        if(str[0]=='q')
        {
            scanf("%d%d%d%d",&xL,&yL,&xR,&yR);
            vmax=-inf;vmin=inf;
            QueryX(1,N,1);
            printf("%d %d\n",vmax,vmin);
        }
        else
        {
            scanf("%d%d%d",&xL,&yL,&val);
            UpdateX(1,N,1);
        }
    }
    return 0;
}
