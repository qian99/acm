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
const int mod=20121014;
int num[10];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(num,0,sizeof(num));
        int total=0,res=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&num[i]);
            total+=num[i];
        }
        if(n<=3)
        {
            printf("1024\n");
            continue;
        }
        int sum=5-n;
            for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
            for(int k=j+1;k<n;++k)
            {
                int tmp=num[i]+num[j]+num[k];
                if(tmp%1024==0)
                {
                    if(n==4) res=1024;
                    else if(n==5)
                    {
                        for(int u=0;u<5;++u)
                          for(int v=u+1;v<5;++v)
                          {
                              if(u==i||u==j||u==k) continue;
                              if(v==i||v==j||v==k) continue;
                              sum=num[u]+num[v];
                              while(sum>1024) sum-=1024;
                              res=max(res,sum);
                          }
                    }
                }
                else
                {
                    if(n==4)
                    {
                        for(int u=0;u<n;++u)
                          for(int v=u+1;v<n;++v)
                          {
                              sum=num[u]+num[v];
                              while(sum>1024) sum-=1024;
                              res=max(res,sum);
                          }
                    }
                }
            }
        res%=mod;
        printf("%d\n",res);
    }
    return 0;
}
