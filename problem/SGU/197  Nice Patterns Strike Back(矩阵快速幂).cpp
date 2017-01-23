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
const int maxn=200+10;
ll matrix[35][35],m2[35][35];
char str[maxn];
int st[maxn];
int mu[maxn<<3];
int N,n,p,m;
inline bool isame(int s,int p,int s2,int p2)
{
    return (s&(1<<p))==(s2&(1<<p2));
}
bool check(int i,int j)
{
    for(int x=0;x<n-1;++x)
    {
        if(isame(i,x,j,x)&&isame(i,x+1,j,x+1)&&isame(i,x,i>>1,x))
          return false;
    }
    return true;
}
void mulmatrix(ll a[35][35],ll b[35][35])
{
    ll tmp[35][35];
    memset(tmp,0,sizeof(tmp));
    for(int i=0;i<N;++i)
    {
        for(int k=0;k<N;++k)
          for(int j=0;j<N;++j)
            tmp[i][k]=(tmp[i][k]+a[i][j]*b[j][k])%p;
    }
    for(int i=0;i<N;++i)
      for(int j=0;j<N;++j)
        a[i][j]=tmp[i][j];
}
int div2(int &len)
{
    int z=0,tmp;
    for(int i=len-1;i>=0;--i)
    {
        tmp=(st[i]+z*10)&1;
        st[i]=(st[i]+z*10)/2;
        z=tmp;
    }
    while(len>0&&st[len-1]==0) len--;
    if(len==1&&st[0]==0) len=0;
    return z;
}
void decrease()
{
    int x;
    for(int i=0;i<m;++i)
     if(mu[i]) {x=i;break;}
    if(mu[x]==0) {mu[0]=-1;return ;}
    mu[x]=0;
    if(x==m-1) m--;
    for(int i=0;i<x;++i) mu[i]=1;
}
void convert()
{
    int len=strlen(str);
    for(int i=0;i<len;++i)
      st[i]=str[len-i-1]-'0';
    m=0;
    while(len)
      mu[m++]=div2(len);
    decrease();
    decrease();
}
void solve()
{
    for(int i=0;i<m;++i)
    {
        if(mu[i]) mulmatrix(matrix,m2);
        mulmatrix(m2,m2);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    convert();
    scanf("%d%d",&n,&p);
    N=1<<n;
    if(mu[0]==-1)
    {
        printf("%d\n",N%p);
        return 0;
    }
    memset(matrix,0,sizeof(matrix));
    for(int i=0;i<N;++i)
      for(int j=0;j<N;++j)
        if(check(i,j)) m2[i][j]=matrix[i][j]=1;
    solve();
    ll sum=0;
    for(int i=0;i<N;++i)
      for(int j=0;j<N;++j)
        sum=(sum+matrix[i][j])%p;
    printf("%lld\n",sum);
    return 0;
}
