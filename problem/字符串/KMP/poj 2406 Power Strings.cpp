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
char s[maxn];
int next[maxn];
void getNext(int n)
{
    next[0]=next[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=next[i];
        while(j&&s[i]!=s[j]) j=next[j];
        next[i+1]=(s[i]==s[j])?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",s))
    {
        if(s[0]=='.') break;
        int n=strlen(s);
        getNext(n);
        if(n%(n-next[n])==0)
            printf("%d\n",n/(n-next[n]));
        else printf("1\n");
    }
    return 0;
}

