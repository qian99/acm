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
const int maxn=100000*3+10;
const int maxx=1000000+10;
int lf[maxn],rn[maxn];
int num[maxn],res[maxn];
bool flag[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(flag,0,sizeof(flag));
        for(int i=1;i<=n;++i)
          scanf("%d",&num[i]);
        lf[1]=1;
        bool fg;
        for(int i=2;i<=n;++i)
        {
            if(num[i]==num[i-1])
            {
                lf[i]=lf[i-1];
                continue;
            }
            int j=i;
            fg=true;
            while(j>1&&(num[j-1]%num[i]==0))
            {
                if(num[j-1]==num[i])
                {
                    lf[i]=lf[j-1];
                    fg=false;
                    break;
                }
                j--;
            }
            if(fg) lf[i]=j;
        }
        rn[n]=n;
        int maxl=0;
        for(int i=n-1;i>=1;--i)
        {
            if(num[i]==num[i+1])
            {
                rn[i]=rn[i+1];
                maxl=max(maxl,rn[i]-lf[i]);
                continue;
            }
            int j=i;
            fg=true;
            while(j<n&&(num[j+1]%num[i]==0))
            {
                if(num[j+1]==num[i])
                {
                    rn[i]=rn[j+1];
                    fg=false;
                    break;
                }
                j++;
            }
            if(fg) rn[i]=j;
            maxl=max(maxl,rn[i]-lf[i]);
        }
        int j=0;
        for(int i=1;i<=n;++i)
        {
            if(rn[i]-lf[i]==maxl&&!flag[lf[i]])
              res[j++]=lf[i],flag[lf[i]]=true;
        }
        printf("%d %d\n",j,maxl);
        sort(res,res+j);
        printf("%d",res[0]);
        for(int i=1;i<j;++i)
          printf(" %d",res[i]);
        printf("\n");
    }
    return 0;
}
