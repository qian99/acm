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
    int tcase=0,n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        scanf("%s",str);
        getnext(n);
        printf("Test case #%d\n",tcase);
        int tmp;
        for(int i=1;i<=n;++i)
        {
            if(!next[i]) continue;
            tmp=i-next[i];
            if(i%tmp==0)
                printf("%d %d\n",i,i/tmp);
        }
        printf("\n");
    }
    return 0;
}

