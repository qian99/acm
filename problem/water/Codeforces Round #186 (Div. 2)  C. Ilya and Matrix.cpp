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
const int maxn=2000000+10;
int num[maxn];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
        {
            scanf("%d",&num[i]);
        }
        sort(num,num+n,cmp);
        int m=1;
        int p=n;
        while(p/4!=0)
        {
            m++;
            p/=4;
        }
        __int64 z=1;
        __int64 sum=0;
        for(int i=0;i<n;++i)
        {
            if(i<z)
            {
                sum+=(__int64)num[i]*m;
            }
            else
            {
                z*=4;
                m--;
                sum+=(__int64)num[i]*m;
            }
        }
        cout<<sum<<endl;
    }
    return 0;
}