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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 800+10;
int mat[maxn][maxn];
struct SegTree
{
    int maxv[maxn<<2][maxn<<2],minv[maxn<<2][maxn<<2];
    int XL,XR,YL,YR,X,Y,val,n;
    int res1,res2;
    void preupdate(int px,int py,int v)
    {
        X = px;  Y = py;
        val = v;
        UpdateX(1,n,1);
    }
    void prequery(int xl,int xr,int yl,int yr)
    {
        XL = xl; XR = xr;
        YL = yl; YR = yr;
        res1 = -inf;
        res2 = inf;
        QueryX(1,n,1);
    }
    void PushUpY(int x,int y)
    {
        maxv[x][y] = max(maxv[x][y<<1],maxv[x][y<<1|1]);
        minv[x][y] = min(minv[x][y<<1],minv[x][y<<1|1]);
    }
    void PushUpX(int x,int y)
    {
        maxv[x][y] = max(maxv[x<<1][y],maxv[x<<1|1][y]);
        minv[x][y] = min(minv[x<<1][y],minv[x<<1|1][y]);
    }
    void buildY(int x,int l,int r,int y)
    {
        if(l == r)
        {
            if(x < 0)
                maxv[-x][y] = minv[-x][y] = mat[X][l];
            else
                PushUpX(x,y);
            return ;
        }
        int m = (l+r)>>1;
        buildY(x,l,m,y<<1);
        buildY(x,m+1,r,y<<1|1);
        PushUpY(abs(x),y);
    }
    void buildX(int l,int r,int x)
    {
        if(l == r)
        {
            X = l;
            buildY(-x,1,n,1);
            return ;
        }
        int m = (l+r)>>1;
        buildX(l,m,x<<1);
        buildX(m+1,r,x<<1|1);
        buildY(x,1,n,1);
    }
    void UpdateY(int x,int l,int r,int y)
    {
        if(l == r)
        {
            if(x < 0)
                minv[-x][y] = maxv[-x][y] = val;
            else PushUpX(x,y);
            return ;
        }
        int m = (l+r)>>1;
        if(m >= Y) UpdateY(x,l,m,y<<1);
        else UpdateY(x,m+1,r,y<<1|1);
        PushUpY(abs(x),y);
    }
    void UpdateX(int l,int r,int x)
    {
        if(l == r)
        {
            UpdateY(-x,1,n,1);
            return ;
        }
        int m = (l+r)>>1;
        if(m >= X) UpdateX(l,m,x<<1);
        else UpdateX(m+1,r,x<<1|1);
        UpdateY(x,1,n,1);
    }
    void QueryY(int x,int l,int r,int y)
    {
        if(l >= YL && r <= YR)
        {
            res1 = max(res1,maxv[x][y]);
            res2 = min(res2,minv[x][y]);
            return ;
        }
        int m = (l + r)>>1;
        if(m >= YL) QueryY(x,l,m,y<<1);
        if(m < YR) QueryY(x,m+1,r,y<<1|1);
    }
    void QueryX(int l,int r,int x)
    {
        if(l >= XL && r <= XR)
        {
            QueryY(x,1,n,1);
            return ;
        }
        int m = (l+r)>>1;
        if(m >= XL) QueryX(l,m,x<<1);
        if(m < XR) QueryX(m+1,r,x<<1|1);
    }
}tree;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d",&n);
        tree.n = n;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                scanf("%d",&mat[i][j]);
        tree.buildX(1,n,1);
        printf("Case #%d:\n",++tcase);
        scanf("%d",&m);
        int x,y,L,ans;
        while(m--)
        {
            scanf("%d%d%d",&x,&y,&L);
            tree.prequery(max(x-L/2,1),min(x+L/2,n),
                          max(y-L/2,1),min(y+L/2,n));
            ans = (tree.res1 + tree.res2)/2;
            tree.preupdate(x,y,ans);
            printf("%d\n",ans);
        }
    }
    return 0;
}
