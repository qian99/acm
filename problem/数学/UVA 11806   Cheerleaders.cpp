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
const int mod=1000000+7;
const int maxn=500+10;
ll C[maxn][maxn];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<maxn;++i)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t,m,n,k,tcase=0;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>m>>n>>k;
        int r,c,tmp;
        ll ans=0;
        for(int i=0;i<16;++i)
        {
            r=m,c=n;
            tmp=0;
            if(i&1) {r--;tmp++;}
            if(i&2) {c--;tmp++;}
            if(i&4) {r--;tmp++;}
            if(i&8) {c--;tmp++;}
            if(tmp&1) ans=(ans-C[r*c][k])%mod;
            else ans=(ans+C[r*c][k])%mod;
        }
        ans=(ans+mod)%mod;
        cout<<"Case "<<tcase<<": ";
        cout<<ans<<endl;
    }
    return 0;
}

