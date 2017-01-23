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
const int maxn=1000+10;
int c[maxn],s[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    char str1[10],str2[10];
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        if(n==0&&m==0&&k==0) break;
        for(int i=1;i<=m;++i) {c[i]=n;s[i]=k;}
        int p,x,y;
        scanf("%d",&p);
        while(p--)
        {
            scanf("%s%d%s%d",str1,&x,str2,&y);
            if(str1[0]=='c')
                c[y]--;
            else s[x]--;
        }
        ll sum=0;
        for(int i=1;i<=m;++i)
          sum+=(ll)c[i]*s[i];
        printf("%I64d\n",sum);
    }
    return 0;
}
