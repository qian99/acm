#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
int A[maxn],B[maxn];
bool cmp(int a,int b)
{
    return b<a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,t;
    while(~scanf("%d%d",&n,&t))
    {
        for(int i=0;i<n;++i)
          scanf("%d",&A[i]);
        for(int i=0;i<n;++i)
          scanf("%d",&B[i]);
        sort(A,A+n);
        sort(B,B+n,cmp);
        int sum=0,tmp;
        for(int i=0;i<n;++i)
        {
            tmp=A[i]+B[i];
            if(tmp>t)
              sum+=tmp-t;
        }
        printf("%d\n",sum);
    }
    return 0;
}
