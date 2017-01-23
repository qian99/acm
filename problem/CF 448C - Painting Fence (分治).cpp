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
const int maxn=5000+10;
int a[maxn];
int cal(int L,int R)
{
    if(L==R) return a[L]!=0;
    if(L>R) return 0;
    int minv=inf,pos,cnt=0;
    for(int i=L;i<=R;++i)
    {
        if(a[i]<minv)
        {
            minv=a[i];
            pos=i;
        }
        if(a[i]) cnt++;
    }
    for(int i=L;i<=R;++i)
        a[i]-=minv;
    if(minv>=cnt) return cnt;
    return min(cnt,cal(L,pos-1)+cal(pos+1,R)+minv);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(a[i]>n) a[i]=n+1;
    }
    int ans=cal(1,n);
    printf("%d\n",ans);
    return 0;
}