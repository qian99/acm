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
const int maxn=60;
struct Matrix
{
    ll mat[maxn][maxn];
    int n;
    void clear() {memset(mat,0xff,sizeof(mat));}
}mx;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    c.n=a.n;
    ll tmp;
    for(int k=0;k<c.n;++k)
        for(int i=0;i<c.n;++i)
            for(int j=0;j<c.n;++j)
            {
                if((a.mat[i][k]==-1)||(b.mat[k][j]==-1)) continue;
                tmp=a.mat[i][k]+b.mat[k][j];
                if(c.mat[i][j]==-1) c.mat[i][j]=tmp;
                else if(c.mat[i][j]>tmp) c.mat[i][j]=tmp;
            }
    return c;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    int n,m,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        int u,v,c;
        mx.clear();
        mx.n=n;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            u--;v--;
            //if(u==v) continue;
            if(mx.mat[u][v]==-1) mx.mat[u][v]=c;
            else if(mx.mat[u][v]>c) mx.mat[u][v]=c;
        }
        Matrix x=mx;
        k--;
        while(k)
        {
            if(k&1) x=x*mx;
            mx=mx*mx;
            k>>=1;
        }
        ll ans=x.mat[0][n-1];
        printf("%lld\n",ans);
    }
    return 0;
}
