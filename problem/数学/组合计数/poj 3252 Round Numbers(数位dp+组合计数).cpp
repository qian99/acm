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
const int maxn=35;
ll C[maxn][maxn];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
}
int num[maxn];
ll dp[maxn][maxn][maxn];
ll f(int pos,int zc,int oc,bool limit)
{
    if(pos==-1) return zc>=oc;
    if(!limit&&dp[pos][zc][oc]!=-1) return dp[pos][zc][oc];
    ll ans=0;
    if(oc&&!limit)
    {
        int tmp=zc-oc;
        tmp=(pos+1)-tmp;
        int x=tmp/2+((tmp&1)?1:0);
        if(tmp<0) x=0;
        for(int i=x;i<=pos+1;++i)
            ans+=C[pos+1][i];
        return dp[pos][zc][oc]=ans;
    }
    int last=limit?num[pos]:1;
    for(int i=0;i<=last;++i)
    {
        ans+=f(pos-1,zc+(oc?(i^1):0),oc+i,limit&&i==last);
    }
    if(!limit) dp[pos][zc][oc]=ans;
    return ans;
}
ll cal(ll x)
{
    memset(dp,0xff,sizeof(dp));
    int len=0;
    while(x)
    {
        num[len++]=(x&1);
        x>>=1;
    }
    return f(len-1,0,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    ll S,T;
    while(cin>>S>>T)
    {
        cout<<cal(T)-cal(S-1)<<endl;
    }
    return 0;
}
