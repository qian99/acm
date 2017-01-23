#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        bool flag = false;
        int num;
        for(int i = 0;i < n;++i)
            scanf("%d",&num);
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&num);
            if(num == 1) flag = true;
        }
        while(m--)
        {
            scanf("%d",&num);
            if(num <= 0) printf("NO\n");
            else if(flag) printf("YES\n");
            else if(num & 1) printf("NO\n");
            else printf("YES\n");
        }
    }
    return 0;
}
