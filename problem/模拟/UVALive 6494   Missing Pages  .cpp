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
    int n,p;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d",&p);
        int k=n;
        int res[10];
        for(int i=1;i<n/2;i+=2)
        {
            if(i==p||p==i+1||p==k||p==k-1)
            {
                res[0]=i;
                res[1]=i+1;
                res[2]=k-1;
                res[3]=k;
                break;
            }
            k-=2;
        }
        bool first=true;
        for(int i=0;i<4;++i)
        {
            if(res[i]==p) continue;
            if(!first) printf(" ");
            first=false;
            printf("%d",res[i]);
        }
        printf("\n");
    }
    return 0;
}
