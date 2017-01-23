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
const int maxn=100000+10;
int primes[maxn],pcnt;
bool flag[maxn],vis[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=(ll)i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
int ans[maxn][2],S[maxn],T[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int n;
    cin>>n;
    memset(vis,0,sizeof(vis));
    int cnt=0,tcnt=0,tot;
    for(int i=pcnt-1;i>0;--i)
    {
        if(primes[i]*2>n) continue;
        tot=0;
        for(int j=primes[i];j<=n;j+=primes[i])
        {
            if(vis[j]) continue;
            S[tot++]=j;
            vis[j]=true;
        }
        if(tot&1)
        {
            T[tcnt++]=S[1];
            ans[cnt][0]=S[0];
            ans[cnt++][1]=S[2];
            for(int j=3;j<tot;j+=2)
            {
                ans[cnt][0]=S[j];
                ans[cnt++][1]=S[j+1];
            }
        }
        else
        {
            for(int j=0;j<tot;j+=2)
            {
                ans[cnt][0]=S[j];
                ans[cnt++][1]=S[j+1];
            }
        }
    }
    for(int j=2;j<=n;j+=2)
        if(!vis[j]) T[tcnt++]=j;
    if(tcnt&1) tcnt--;
    for(int i=0;i<tcnt;i+=2)
    {
        ans[cnt][0]=T[i];
        ans[cnt++][1]=T[i+1];
    }
    cout<<cnt<<endl;
    for(int i=0;i<cnt;++i)
        cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
    return 0;
}
