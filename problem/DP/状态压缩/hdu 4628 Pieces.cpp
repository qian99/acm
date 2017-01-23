#include <iostream>
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
typedef long long LL;
const int maxn=50;
char str[maxn];
int dp[70000],state[70000];
bool vis[20];
int N,top,total,times;
bool isok(int x)
{
    int num[20];
    int i=0,j=N-1;
    while(x)
    {
        if(x&1)
        num[i++]=j;
        j--;
        x=x>>1;
    }
    int a=0,b=i-1;
    while(a<b)
    {
        if(str[num[a]]!=str[num[b]])
          return false;
        a++;
        b--;
    }
    return true;
}
void Init()
{
    top=0;
    total=1<<N;
    for(int i=1;i<total;++i)
    {
        if(isok(i)) state[top++]=i;
    }
}
bool check(int x,int y)
{
    return !(x&y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>str;
        N=strlen(str);
        Init();
        for(int i=1;i<total;++i) dp[i]=inf;
        dp[0]=0;
        for(int i=0;i<top;++i)
        {
            for(int j=total-1;j>=state[i];--j)
            {
                if(check(state[i],j-state[i]))
                   dp[j]=min(dp[j],dp[j-state[i]]+1);
            }
        }
        cout<<dp[total-1]<<endl;
    }
    return 0;
}

