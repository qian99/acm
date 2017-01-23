#include <iostream>
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
char str[101];
int sum[15],mat[15][15];
int n;
bool finds;
bool check(int k)
{
    int aa;
    for(int i=1;i<=k;++i)
    {
        aa=sum[k]-sum[i-1];
        if(mat[i][k]==1&&aa<=0) return false;
        if(mat[i][k]==0&&aa!=0) return false;
        if(mat[i][k]==-1&&aa>=0) return false;
    }
    return true;
}
void dfs(int now)
{
    if(now>n)
    {
        finds=true;
        return;
    }
    for(int i=-10;i<=10;++i)
    {
        sum[now]=sum[now-1]+i;
        if(check(now))
        {
            dfs(now+1);
            if(finds) return;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        scanf("%s",str);
        memset(mat,0,sizeof(mat));
        //int m=(n+1)*n/2;
        int u=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=i;j<=n;++j)
            {
                if(str[u]=='+') mat[i][j]=1;
                else if(str[u]=='-') mat[i][j]=-1;
                else mat[i][j]=0;
                u++;
            }
        }
        sum[0]=0;
        finds=false;
        dfs(1);
        for(int i=1;i<n;++i)
           printf("%d ",sum[i]-sum[i-1]);
        printf("%d\n",sum[n]-sum[n-1]);
    }
    return 0;
}
