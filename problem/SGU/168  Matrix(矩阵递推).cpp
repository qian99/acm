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
const int maxn=1000+10;
int A[maxn][maxn],B[maxn][maxn],C[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)
      for(int j=0;j<m;++j)
        scanf("%d",&A[i][j]);
    for(int j=0;j<m;++j)
    {
        C[n-1][j]=A[n-1][j];
        for(int i=n-2;i>=0;--i)
          C[i][j]=min(A[i][j],C[i+1][j]);
    }
    for(int i=0;i<n;++i) B[i][m-1]=C[i][m-1];
    for(int j=m-2;j>=0;--j)
    {
        B[0][j]=min(C[0][j],B[0][j+1]);
        for(int i=1;i<n;++i)
          B[i][j]=min(C[i][j],B[i-1][j+1]);
    }
    for(int i=0;i<n;++i)
    {
        printf("%d",B[i][0]);
        for(int j=1;j<m;++j)
          printf(" %d",B[i][j]);
        printf("\n");
    }
    return 0;
}
