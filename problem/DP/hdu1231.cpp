#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=10000+10;
int num[maxn];
int st,ed;
int MaxSum(int n)
{
    int s,t,sum,maxsum;
    st=ed=t=0;
    s=1;
    maxsum=-inf;
    sum=0;
    while(t<=n)
    {
        if(sum<0)
        {
            s=t+1;
            sum=0;
        }
        t++;
        if(t>n) break;
        sum+=num[t];
        if(sum>maxsum)
        {
            maxsum=sum;
            st=s;
            ed=t;
        }
    }
    return maxsum;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        bool flag=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            if(num[i]>=0) flag=true;
        }
        if(flag)
        {
            int ans=MaxSum(n);
            printf("%d %d %d\n",ans,num[st],num[ed]);
        }
        else
          printf("0 %d %d\n",num[1],num[n]);
    }
    return 0;
}
