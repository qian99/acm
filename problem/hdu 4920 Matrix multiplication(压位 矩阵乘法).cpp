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
const int maxn=800+10;
int A[maxn][maxn],B[maxn][maxn],C[maxn][maxn],n;
int AA[maxn][maxn],BB[maxn][maxn];
int val[1<<10],mval[1<<10][1<<10];
void Init()
{
    for(int i=0;i<(1<<10);++i)
        for(int j=0;j<(1<<10);++j)
        {
            mval[i][j]=0;
            for(int k=0;k<10;k+=2)
            {
                int tmp1=(i>>k)&3;
                int tmp2=(j>>k)&3;
                mval[i][j]|=(tmp1*tmp2%3)<<k;
            }
        }
    for(int i=0;i<(1<<10);++i)
    {
        val[i]=0;
        for(int j=0;j<10;j+=2)
            val[i]+=(i>>j)&3;
        val[i]%=3;
    }
}
void Mul(int n,int m)
{
    memset(C,0,sizeof(C));
    for(int k=1;k<=m;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            {
                C[i][j]+=val[mval[A[i][k]][B[k][j]]];
            }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int n;
    while(~scanf("%d",&n))
    {
        memset(AA,0,sizeof(AA));
        memset(BB,0,sizeof(BB));
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&AA[i][j]);
                AA[i][j]%=3;
            }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&BB[i][j]);
                BB[i][j]%=3;
            }
        int m=n/5+(n%5==0?0:1);
        for(int i=1;i<=n;++i)
        {
            int now=0;
            for(int j=1;j<=m;++j)
            {
                for(int k=0;k<5;++k)
                {
                    A[i][j]|=AA[i][now+1]<<((now%5)*2);
                    now++;
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            int now=0;
            for(int j=1;j<=m;++j)
            {
                for(int k=0;k<5;++k)
                {
                    B[j][i]|=BB[now+1][i]<<((now%5)*2);
                    now++;
                }
            }
        }
        Mul(n,m);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j>1) printf(" ");
                C[i][j]%=3;
                printf("%d",C[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
