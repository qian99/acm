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
typedef unsigned long long ll;
const int maxn=160000+10;
const int N=10000000;
const int M=156250;
ll flag[maxn],p[65];
int sum[maxn];
int getnum(int x)
{
    int sum=0;
    while(x)
    {
        sum+=(x%10);
        x/=10;
    }
    return sum;
}
int getb(ll x)
{
    int cnt=0;
    while(x)
    {
        x&=(x-1);
        cnt++;
    }
    return cnt;
}
int f(int x)
{
    int l=1,r=M;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(sum[m]<x)
          l=m+1;
        else r=m;
    }
    return l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(ll w=0;w<64;++w) p[w]=(ll)1<<w;
    memset(flag,0xff,sizeof(flag));
    int tmp,z;
    for(int i=0;i<=N;i+=10)
    {
        tmp=getnum(i);
        for(int j=0;j<10;++j)
        {
            z=i+tmp+j+j;
            if(i+tmp+j+j<=N)
            {
                z=i+tmp+j+j;
                flag[z/64]&=(p[z%64]^(p[64]-1));
            }
        }
    }
    sum[0]=0;
    for(int i=1;i<=M;++i)
      sum[i]+=sum[i-1]+getb(flag[i-1]);
    int n,k;
    ll x;
    while(~scanf("%d%d",&n,&k))
    {
        int ans=0;n+=1;
        ans=sum[n/64];
        if(n%64)
        {
            x=flag[n/64];
            int tmp=n%64;
            while(x&&tmp)
            {
                if(x&1) ans++;
                tmp--;
                x>>=1;
            }
        }
        printf("%d\n",ans);
        int num,pos;
        for(int i=0;i<k;++i)
        {
            scanf("%d",&num);
            pos=f(num);
            ans=(pos-1)*64;
            num-=sum[pos-1];
            x=flag[pos-1];
            if(i) printf(" ");
            while(x&&num)
            {
                if(x&1) {num--;}
                if(!num) break;
                ans++;
                x>>=1;
            }
            printf("%d",ans);
        }
        printf("\n");
    }
    return 0;
}
