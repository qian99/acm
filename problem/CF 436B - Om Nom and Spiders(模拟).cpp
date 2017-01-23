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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
const int dirx[4]={0,0,-1,1};
const int diry[4]={-1,1,0,0};
char str[maxn][maxn];
int cnt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;++i)
    {
        scanf("%s",str[i]+1);
        for(int j=1;j<=m;++j)
        {
            if(str[i][j]=='U')
            {
                if((i-2)&1) cnt[j]++;
            }
            else if(str[i][j]=='L')
            {
                int k=i-2;
//                if(j-k>=1) cnt[j-k]++;
                if(j-k-1>=1) cnt[j-k-1]++;
            }
            else if(str[i][j]=='R')
            {
                int k=i-2;
//                if(j+k<=m) cnt[j+k]++;
                if(j+k+1<=m) cnt[j+k+1]++;
            }
        }
    }
    printf("%d",cnt[1]);
    for(int i=2;i<=m;++i)
        printf(" %d",cnt[i]);
    printf("\n");
    return 0;
}