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
const int maxn=100000+10;
int num[maxn];
int f(int l,int r,int v)
{
    int m;
    while(l<r)
    {
        m=(l+r)>>1;
        if(num[m]<v)
            l=m+1;
        else
            r=m;
    }
    return l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&num[i]);
    int l=1,r=1;
    for(int i=2;i<=n;++i)
    {
        if(num[i]>num[r])
            num[++r]=num[i];
        else
        {
            int pos=f(l,r,num[i]);
            num[pos]=num[i];
        }
    }
    printf("%d\n",r);
    return 0;
}
