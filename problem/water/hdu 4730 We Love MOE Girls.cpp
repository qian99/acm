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
const int maxn=100+10;
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%s",str);
        int n=strlen(str);
        if(n>=4)
        {
            if(str[n-4]=='d'&&str[n-3]=='e'&&str[n-2]=='s'&&str[n-1]=='u')
              n-=4;
        }
        printf("Case #%d: ",tcase);
        for(int i=0;i<n;++i)
          printf("%c",str[i]);
        printf("nanodesu\n");
    }
    return 0;
}
