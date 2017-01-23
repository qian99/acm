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
const int maxn=100+10;
int cnt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,t;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d",&t);
        memset(cnt,0,sizeof(cnt));
        int now=0;
        bool flag;
        while(true)
        {
            for(int i=0;i<t;++i)
            {
                cnt[now]++;
                if(i==t-1) break;
                now++;
                if(now==n) now=0;
            }
            for(int i=now;i<n;++i)
                cnt[i]=cnt[i+1];
            n--;
            if(now==n) now=0;
            if(n==1) break;
            flag=true;
            for(int i=1;i<n;++i)
                if(cnt[i]!=cnt[i-1]) flag=false;
            if(flag) break;
        }
        printf("%d %d\n",n,cnt[0]);
    }
    return 0;
}
