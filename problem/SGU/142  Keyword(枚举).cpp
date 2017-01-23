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
const int maxn=1100000+10;
const int N=500000+10;
bool flag[maxn];
int p[35];
char str[N];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,i;
    for(i=0;i<31;++i) p[i]=1<<i;
    scanf("%d",&n);
    scanf("%s",str);
    for(i=1;i<=n;++i)
    {
        int val=0,cnt=0;
        memset(flag,0,sizeof(flag));
        for(int j=0;j<i;++j)
        {
            val*=2;
            val+=(str[j]=='a')?0:1;
        }
        flag[val]=true;
        cnt++;
        for(int j=i;j<n;++j)
        {
            val*=2;
            val+=(str[j]=='a')?0:1;
            val&=(p[i]-1);
            if(!flag[val])
            {
                flag[val]=true;
                cnt++;
            }
        }
        if(cnt!=p[i]) break;
    }
    printf("%d\n",i);
    int x;
    for(int j=0;j<p[i];++j)
    {
        if(!flag[j])
        {
            x=j;
            break;
        }
    }
    for(int j=i-1;j>=0;--j)
    {
        if(x&p[j]) printf("b");
        else printf("a");
    }
    printf("\n");
    return 0;
}
