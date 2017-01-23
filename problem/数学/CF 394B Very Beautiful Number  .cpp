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
const int maxn=1000000+10;
int num[maxn],num2[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,x;
    while(~scanf("%d%d",&n,&x))
    {
        if(n==1)
        {
            if(x==1) printf("1\n");
            else printf("Impossible\n");
            continue;
        }
        bool find=false;
        for(int i=1;i<=9;++i)
        {
            memset(num,0,sizeof(num));
            memset(num2,0,sizeof(num2));
            num[0]=i;
            for(int j=1;j<n;++j)
            {
                num[j]+=num[j-1]*x;
                num[j+1]=num[j]/10;
                num[j]%=10;
            }
            if(num[n-1]==0) continue;
            for(int j=0;j<n;++j)
            {
                num2[j]+=num[j]*x;
                num2[j+1]+=num2[j]/10;
                num2[j]%=10;
            }
            bool flag=true;
            for(int j=1;j<n-1;++j)
            {
                if(num2[j-1]!=num[j]) {flag=false;break;}
            }
            if(flag&&num2[n-1]==i&&!num2[n])
            {
                find=true;
                break;
            }
        }
        if(find)
        {
            for(int i=n-1;i>=0;--i)
            printf("%d",num[i]);
            printf("\n");
        }
        else printf("Impossible\n");
    }
    return 0;
}