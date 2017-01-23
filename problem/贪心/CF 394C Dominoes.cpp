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
int n,m;
int cnt[4];
int a[maxn][maxn];
char str[5];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        memset(cnt,0,sizeof(cnt));
        int i,j;
        for(i=0;i<n;++i)
        {
            for(j=0;j<m;++j)
            {
                scanf("%s",str);
                int st=((str[0]=='1')<<1)|(str[1]=='1');
                cnt[st]++;
            }
        }
        cnt[1]+=cnt[2];
        for(i=0;i<n;++i)
        {
            for(j=0;j<m;++j)
                if(cnt[3]) a[i][j]=3,cnt[3]--;
                else break;
            if(cnt[3]==0) break;
        }
        if(j!=m)
        {
            int k=j;
            for(;j<m;++j)
            {
                if(cnt[1])
                {
                    a[i][j]=1;
                    cnt[1]--;
                    if(i<n)
                    {
                        if(cnt[1])
                        a[i+1][j]=2,cnt[1]--;
                        else a[i+1][j]=0,cnt[0]--;
                    }
                }
                else
                {
                    a[i][j]=0;
                    cnt[0]--;
                    if(i<n) a[i+1][j]=0;cnt[0]--;
                }
            }
            if(i+1<n)
            for(k=k-1;k>=0;--k)
                if(cnt[0]) a[i+1][k]=0,cnt[0]--;
                else a[i+1][k]=1,cnt[1]--;
            i+=2;
        }
        else i++;
        for(;i<n;++i)
        {
            for(j=0;j<m;++j)
            {
                if(cnt[1])
                {
                    if(i>0)
                    {
                        if(a[i-1][j]&&a[i-1][j]!=3)
                        a[i][j]=a[i-1][j]^3;
                        else a[i][j]=1;
                        cnt[1]--;
                    }
                    else a[i][j]=1,cnt[1]--;
                }
                else a[i][j]=0;
            }
        }
        for(i=0;i<n;++i)
        {
            for(j=0;j<m;++j)
            {
                if(j) printf(" ");
                printf("%d%d",a[i][j]>>1,a[i][j]&1);
            }
            printf("\n");
        }
    }
    return 0;
}