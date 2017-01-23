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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000+10;
int a[maxn],b[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
        scanf("%d",&a[i]);
    sort(a,a+n);
    if(n == 1) puts("-1");
    else if(n == 2)
    {
        int d = a[1] - a[0];
        if(d == 0)
        {
            printf("1\n%d\n",a[0]);
        }
        else if(d & 1)
            printf("2\n%d %d\n",a[0] - d,a[1] + d);
        else
            printf("3\n%d %d %d\n",a[0] - d,a[0] + d/2,a[1] + d);
    }
    else
    {
        for(int i = 0;i < n - 1;++i)
            b[i] = a[i+1] - a[i];
        sort(b,b+n-1);
        int m = unique(b,b+n-1) - b;
        if(m > 2) puts("0\n");
        else if(m == 1)
        {
            if(b[0])
                printf("2\n%d %d\n",a[0]-b[0],a[n-1]+b[0]);
            else printf("1\n%d\n",a[0]);
        }
        else
        {
            if(b[1] == b[0]*2)
            {
                int val ;
                bool flag = false;
                for(int i = 0;i < n-1;++i)
                    if(a[i+1] - a[i] == b[1])
                    {
                        if(!flag)
                        {
                            val = a[i] + b[0];
                            flag = true;
                        }
                        else
                        {
                            flag = false;
                            break;
                        }
                    }
                if(flag) printf("1\n%d\n",val);
                else printf("0\n");
            }
            else puts("0");
        }
    }
    return 0;
}

