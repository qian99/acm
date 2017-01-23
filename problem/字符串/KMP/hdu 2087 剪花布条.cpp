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
char s1[maxn],s2[maxn];
int next[maxn],ans;
void Kmp()
{
    int n=strlen(s1);
    int m=strlen(s2);
    if(m>n) return ;
    int j=0;
    for(int i=0;i<n;++i)
    {
        while(j&&s1[i]!=s2[j]) j=next[j];
        if(s1[i]==s2[j]) j++;
        if(j==m) {ans++;j=0;}
    }
}
void getnext()
{
    int n=strlen(s2);
    next[0]=next[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=next[i];
        while(j&&s2[i]!=s2[j]) j=next[j];
        next[i+1]=(s2[i]==s2[j])?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",s1))
    {
        if(s1[0]=='#') break;
        scanf("%s",s2);
        ans=0;
        getnext();
        Kmp();
        printf("%d\n",ans);
    }
    return 0;
}

