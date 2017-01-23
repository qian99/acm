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
const int maxn=200000+10;
const int mod=10007;
char str[maxn];
int next[maxn];
void getnext()
{
    int n=strlen(str);
    next[0]=next[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=next[i];
        while(j&&str[i]!=str[j]) j=next[j];
        next[i+1]=(str[i]==str[j])?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        scanf("%s",str);
        getnext();
        int sum=0;
        for(int i=0;i<=n;++i)
        {
            if(next[i])
                sum++;
        }
        sum=(sum+n)%mod;
        printf("%d\n",sum);
    }
    return 0;
}

