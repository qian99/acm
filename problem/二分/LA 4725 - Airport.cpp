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
const int maxn=5000+10;
int wt[maxn],et[maxn],n;
bool check(int lim)
{
    int cnt=0,a=0,b=0,l,r;
    for(int i=0;i<n;++i)
    {
        a+=wt[i];
        b+=et[i];
        l=max(a-lim,0);
        r=max(b-lim,0);
        if(l+r>cnt) return false;
        if(a==0&&b>0) b--;
        else if(b==0&&a>0) a--;
        else if(a&&b&&a+b>cnt) cnt++;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int L=1,R=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&wt[i],&et[i]);
            R+=max(wt[i],et[i]);
        }
        R=5000*20;
        while(L<R)
        {
            int m=(L+R)>>1;
            if(check(m)) R=m;
            else L=m+1;
        }
        printf("%d\n",L-1);
    }
    return 0;
}

