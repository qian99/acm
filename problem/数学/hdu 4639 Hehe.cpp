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
const int maxn=10000+1000;
const int mod=10007;
char str[maxn];
int fibo[maxn];
void getfibo()
{
    fibo[0]=fibo[1]=1;
    for(int i=2;i<maxn;++i)
      fibo[i]=(fibo[i-1]+fibo[i-2])%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getfibo();
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%s",str);
        int n=strlen(str);
        int ans=1;
        int i=0;
        while(i<n)
        {
            if(str[i]=='h'&&str[i+1]=='e')
            {
                int sum=0;
                while(str[i]=='h'&&str[i+1]=='e'&&i<n)
                {
                    sum++;
                    i+=2;
                }
                ans*=fibo[sum];
                ans%=mod;
            }
            else i++;
        }
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}
