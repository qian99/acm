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
const int mod=1000000007;
struct Matrix
{
    ll mat[4][4];
    void Init()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<4;++k)
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
void ptmat(Matrix a)
{
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
           cout<<a.mat[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
ll cal(int n,int sk,int ek)
{
    if(n==0) return 1;
    if(n==1)
    {
        if(sk==-1&&ek==-1) return 4;
        if(sk==-1) return 3;
        else if(ek==-1) return 3;
        else if(sk==ek) return 3;
        return 2;
    }
    if(sk==-1&&ek==-1) n-=2;
    else if(sk==-1||ek==-1) n--;
    Matrix x,y;
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            y.mat[i][j]=x.mat[i][j]=(i!=j);
    while(n)
    {
        if(n&1) x=x*y;
        y=y*y;
        n>>=1;
    }
    ll ans=0;
    if(sk==-1&&ek==-1)
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
             ans=(ans+x.mat[i][j])%mod;
    }
    else if(sk==-1)
    {
        for(int i=0;i<4;++i)
            ans=(ans+x.mat[i][ek])%mod;
    }
    else if(ek==-1)
    {
        for(int i=0;i<4;++i)
            ans=(ans+x.mat[sk][i])%mod;
    }
    else
    {
        ans=x.mat[sk][ek];
    }
    return ans;
}
inline int idx(char c)
{
    return c-'A';
}
pair<int,int> A[20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char str[5];
    while(~scanf("%d%d",&n,&m))
    {
        int x,id;
        for(int i=0;i<m;++i)
        {
            scanf("%d%s",&x,str);
            A[i]=make_pair(x,idx(str[0]));
        }
        sort(A,A+m);
        ll ans=1;
        int last=-1,len;
        for(int i=0;i<m;++i)
        {
            x=A[i].first;id=A[i].second;
            if(i==0) len=x-1;
            else len=x-A[i-1].first-1;
            ans=ans*cal(len,last,id)%mod;
            last=id;
        }
        if(m==0||A[m-1].first!=n)
        {
            if(m==0) len=n,last=-1;
            else len=n-A[m-1].first,last=A[m-1].second;
            ans=ans*cal(len,last,-1)%mod;
        }
        for(int i=1;i<m;++i)
            if(A[i].first==A[i-1].first+1&&A[i].second==A[i-1].second)
                ans=0;
        printf("%lld\n",ans);
    }
    return 0;
}
