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
const int maxn=10000+10;
int E[maxn],ans;
queue<int>q;
void cal(int n,int cost,int k)
{
    int t=0,cnt=0,tot=0;
    for(int i=1;i<=k*3000;++i)
    {
        if(t>=k) break;
        while(!q.empty())
        {
            int v=q.front();
            if(i-v<cost) break;
            q.pop();
            ans=max(v+cost,ans);
            E[tot++]=v+cost;
            cnt--;
        }
        while(t<k&&E[t]<=i&&cnt+1<=n)
        {
            q.push(i);
            t++;cnt++;
        }
    }
    while(!q.empty())
    {
        int v=q.front();q.pop();
        ans=max(v+cost,ans);
        E[tot++]=v+cost;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k,n1,n2,n3,t1,t2,t3;
    scanf("%d%d%d%d%d%d%d",&k,&n1,&n2,&n3,&t1,&t2,&t3);
    ans=0;
    for(int i=0;i<k;++i)
        E[i]=(i/n1+1)*t1;
    cal(n2,t2,k);
    cal(n3,t3,k);
    printf("%d\n",ans);
    return 0;
}
