#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        bool flag=true;
        int m;
        int t=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&m);
            if(m==i)
            {
                t++;
                if(flag) flag=false;
                else printf(" ");
                printf("%d",m);
            }
        }
        if(t==0) printf("No Mistake");
        printf("\n");
    }
    return 0;
}
