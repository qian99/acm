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
const int maxn=100000+10;
char str[maxn];
int sum[11][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,w;
    scanf("%d%d%d",&n,&k,&w);
    scanf("%s",str);
    for(int i=0;i<k;++i)
    {
        sum[i][0]=0;
        int c=i-1;
        if(c==-1) c=k-1;
        for(int j=1;j<=n;++j)
        {
            if(j%k==c)
            {
                if(str[j-1]=='1') sum[i][j]=sum[i][j-1];
                else sum[i][j]=sum[i][j-1]+1;
            }
            else
            {
                if(str[j-1]=='0') sum[i][j]=sum[i][j-1];
                else sum[i][j]=sum[i][j-1]+1;
            }
        }
    }
    int l,r;
    while(w--)
    {
        scanf("%d%d",&l,&r);
        int ans=sum[l%k][r]-sum[l%k][l-1];
        printf("%d\n",ans);
    }
    return 0;
}