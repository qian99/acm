#include <iostream>
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
const int maxn=1000000+10;
char P[maxn];
int f[maxn];
int n;
void getFail()
{
    f[0]=f[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=f[i];
        while(j>0&&P[i]!=P[j]) j=f[j];
        f[i+1]=P[i]==P[j]?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        scanf("%s",P);
        getFail();
        printf("Test case #%d\n",tcase);
        for(int i=2;i<=n;++i)
        {
            if(f[i]>0&&i%(i-f[i])==0)
              printf("%d %d\n",i,i/(i-f[i]));
        }
        printf("\n");
    }
    return 0;
}
