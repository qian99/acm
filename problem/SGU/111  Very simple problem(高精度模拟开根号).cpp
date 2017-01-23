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
const int maxn=500+10;
const int N=5;
const int M=1e5;
struct BigInt
{
    int len;
    ll num[maxn];
    void Init(int x,int z)
    {
        memset(num,0,sizeof(num));
        int y=x/N;
        len=y+1;
        y=x%N;
        ll kw=z;
        while(y--) kw*=10;
        num[len-1]=kw;
    }
    void Initstr(char *str)
    {
        memset(num,0,sizeof(num));
        int n=strlen(str);
        len=0;
        ll mk;
        for(int i=n-1;i>=0;i-=N)
        {
            mk=1;
            for(int j=0;j<N;++j)
            {
                if(i<j) break;
                num[len]+=mk*(str[i-j]-'0');
                mk*=10;
            }
            len++;
        }
    }
    BigInt mul(BigInt b)
    {
        BigInt c;
        c.Init(1,0);
        int mx=len;
        ll tmp;
        for(int i=0;i<b.len;++i)
        {
            for(int j=0;j<len;++j)
            {
                tmp=b.num[i]*num[j];
                c.num[i+j]+=tmp%M;
                mx=max(mx,i+j+1);
                if(tmp/M) {c.num[i+j+1]+=tmp/M;mx=max(mx,i+j+2);}
            }
        }
        c.len=mx;
        for(int i=0;i<c.len;++i)
        {
            tmp=c.num[i];
            c.num[i]=tmp%M;
            c.num[i+1]+=tmp/M;
        }
        while(c.num[c.len])
        {
            tmp=c.num[c.len];
            c.num[c.len]=tmp%M;
            c.num[c.len++]+=tmp/M;
        }
        return c;
    }
    void add(BigInt b,BigInt &c)
    {
        c.Init(1,0);
        int n=min(len,b.len);
        for(int i=0;i<n;++i)
          c.num[i]=num[i]+b.num[i];
        c.len=n;
        n=max(len,b.len);
        for(int i=c.len;i<n;++i)
          c.num[i]+=num[i];
        for(int i=c.len;i<n;++i)
          c.num[i]+=b.num[i];
        c.len=n;
        ll tmp;
        for(int i=0;i<n;++i)
        {
            tmp=c.num[i];
            c.num[i]=tmp%M;
            c.num[i+1]+=tmp/M;
        }
        while(c.num[c.len])
        {
            tmp=c.num[c.len];
            c.num[c.len]=tmp%M;
            c.num[c.len++]+=tmp/M;
        }
    }
    bool operator >(const BigInt &b) const
    {
        if(b.len<len) return true;
        if(b.len>len) return false;
        for(int i=len-1;i>=0;--i)
          if(b.num[i]!=num[i]) return num[i]>b.num[i];
        return false;
    }
    BigInt div2()
    {
        BigInt c;
        c.Init(1,0);c.len=len;
        if(num[len-1]==1) c.len--;
        num[len]=0;
        for(int i=c.len-1;i>=1;--i)
        {
            if(num[i+1]&1) c.num[i]=(M+num[i])/2;
            else c.num[i]=num[i]/2;
        }
        if(num[1]&1) c.num[0]=(M+num[0])/2;
        else c.num[0]=num[0]/2;
        return c;
    }
    void increas()
    {
        num[0]++;
        int pos=0;
        while(num[pos]>=M)
        {
            if(pos==len) num[len++]=1;
            num[pos+1]+=num[pos]/M;
            num[pos++]%=M;
        }
    }
    void printnum()
    {
        printf("%lld",num[len-1]);
        int S[10];
        for(int i=len-2;i>=0;--i)
        {
            ll x=num[i];
            int j=0;
            memset(S,0,sizeof(S));
            while(x)
            {
                S[j++]=x%10;
                x/=10;
            }
            for(j=N-1;j>=0;--j)
              printf("%d",S[j]);
        }
        printf("\n");
    }
};
char str[2010];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",str))
    {
        BigInt a,L,R,m,tmp,ans;
        int n=strlen(str);
        a.Initstr(str);
        int p=max(n/2-3,1);
        L.Init(p-1,1);
        p=n/2+2;
        R.Init(p-1,1);
        while(R>L)
        {
            L.add(R,m);
            m=m.div2();
            tmp=m.mul(m);
            if(tmp>a)
            {
                R=m;
            }
            else
            {
                ans=m;
                L=m;
                L.increas();
            }
        }
        ans.printnum();
    }
    return 0;
}
