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
int next[maxn];
void getnext(int n)
{
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
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int n=strlen(str);
        getnext(n);
        int ans=n-next[n];
        if(ans==n) ans=n;
        else if(n%ans==0) ans=0;
        else ans=ans-n%ans;
        printf("%d\n",ans);
    }
    return 0;
}

