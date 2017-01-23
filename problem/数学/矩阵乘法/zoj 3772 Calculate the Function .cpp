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
const int mod=1000000007;
ll pow_mod(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b%2==1) ret=ret*a%mod;
        a=a*a%mod;
        b/=2;
    }
    return ret%mod;
}
struct Matrix
{
    ll mat[2][2];
    void clear(){memset(mat,0,sizeof(mat));}
    void init() {mat[0][0]=mat[1][1]=1;mat[1][0]=mat[0][1]=0;}
    void getA(ll A) {
        mat[0][0]=mat[0][1]=1;mat[1][0]=A;mat[1][1]=0;}
    void getAA(ll A)
    {
        mat[0][0]=0;mat[1][0]=1;
        mat[0][1]=pow_mod(A%mod,mod-2);mat[1][1]=-pow_mod(A,mod-2);
        mat[1][1]=mat[1][1]%mod+mod;
    }
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix mx[maxn],my[maxn];
int num[maxn],n;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        Matrix x;
        mx[0].init();my[0].init();
        for(int i=1;i<=n;++i)
        {
            x.getA(num[i]);
            mx[i]=mx[i-1]*x;
            x.getAA(num[i]);
            my[i]=x*my[i-1];
        }
        int L,R;
        ll res;
        while(m--)
        {
            scanf("%d%d",&L,&R);
            if(R-L+1==1) res=num[L];
            else if(R-L+1==2) res=num[R];
            else
            {
                x=mx[R];
                x=my[L+1]*x;
                res=num[L+1]*x.mat[0][0]%mod+num[L]*x.mat[1][0]%mod;
                res%=mod;
            }
            printf("%lld\n",res);
        }
    }
    return 0;
}