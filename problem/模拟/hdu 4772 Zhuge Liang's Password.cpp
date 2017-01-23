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
const int maxn=30+10;
int a[maxn][maxn],b[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            scanf("%d",&a[i][j]);
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            scanf("%d",&b[i][j]);
        int res=0,rnt=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
              rnt+=(a[i][j]==b[i][j]);
        res=max(res,rnt);
        rnt=0;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            rnt+=(a[i][j]==b[j][n-i-1]);
        res=max(res,rnt);
        rnt=0;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            rnt+=(a[i][j]==b[n-i-1][n-j-1]);
        res=max(res,rnt);
        rnt=0;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            rnt+=(a[i][j]==b[n-j-1][i]);
        res=max(res,rnt);
        printf("%d\n",res);
    }
    return 0;
}
