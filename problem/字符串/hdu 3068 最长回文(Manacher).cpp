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
const int maxn=110000+10;
char str[maxn],s[maxn<<1];
int p[maxn<<1];
int Manacher()
{
    int n=0;
    s[n++]='$';s[n++]='#';
    for(int i=0;str[i];i++)
    {
        s[n++]=str[i];
        s[n++]='#';
    }
    int mx=0,id=0,ans=0;
    p[0]=0;
    for(int i=1;i<n;++i)
    {
        p[i]=1;
        if(mx>i) p[i]=min(p[id*2-i],mx-i);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>mx)
        {
            mx=i+p[i];
            id=i;
        }
        if(p[i]>ans) ans=p[i];
    }
    return ans-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",str))
    {
        printf("%d\n",Manacher());
    }
    return 0;
}
