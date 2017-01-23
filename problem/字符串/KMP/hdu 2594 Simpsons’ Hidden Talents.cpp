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
const int maxn=50000+10;
char s1[maxn],s2[maxn];
int next[maxn];
int kmp()
{
    int n=strlen(s1);
    int m=strlen(s2);
    int j=0;
    for(int i=0;i<m;++i)
    {
        while(j&&s2[i]!=s1[j]) j=next[j];
        if(s2[i]==s1[j]) j++;
        if(i==m-1) return j;
        if(j==n) j=next[j];
    }
    return 0;
}
void getnext()
{
    int n=strlen(s1);
    next[0]=next[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=next[i];
        while(j&&s1[j]!=s1[i]) j=next[j];
        next[i+1]=(s1[i]==s1[j])?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",s1))
    {
        scanf("%s",s2);
        getnext();
        int ans=kmp();
        if(ans)
        {
            for(int i=0;i<ans;++i)
                printf("%c",s1[i]);
            printf(" ");
        }
        printf("%d\n",ans);
    }
    return 0;
}

