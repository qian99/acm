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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n<9) printf("0\n");
        else if(n==9) printf("8\n");
        else if(n==10) printf("72\n");
        else
        {
            n-=10;
            printf("72");
            for(int i=0;i<n;++i)
              printf("0");
            printf("\n");
        }
    }
    return 0;
}
