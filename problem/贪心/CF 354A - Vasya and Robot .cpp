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
const int maxn=100000+10;
int w[maxn],lsum[maxn],rsum[maxn];
int main()
{
   //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,l,r,ql,qr;
    while(cin>>n>>l>>r>>ql>>qr)
    {
        for(int i=1;i<=n;++i)
          cin>>w[i];
        if(n==1)
        {
            int res=min(w[1]*l,w[1]*r);
            cout<<res<<endl;
            continue;
        }
        lsum[0]=rsum[n+1]=0;
        for(int i=n;i>=1;--i)
          rsum[i]=rsum[i+1]+w[i]*r;
        for(int i=1;i<=n;++i)
          lsum[i]=lsum[i-1]+w[i]*l;
        int res,tmp,x,y;
        x=min(rsum[1]+(n-1)*qr,rsum[2]+(n-2)*qr+w[1]*l);
        y=min(lsum[n]+(n-1)*ql,lsum[n-1]+(n-2)*ql+w[n]*r);
        res=min(x,y);
        for(int i=2;i<n;++i)
        {
            tmp=lsum[i-1]-lsum[0]+rsum[i+1]-rsum[n+1];
            x=i-1;y=n-i;
            if(x==y)
              res=min(res,tmp+min(w[i]*l,w[i]*r));
            else if(x<y)
            {
                int z=y-x;
                tmp+=(z-1)*qr+min(w[i]*l,w[i]*r+qr);
                res=min(res,tmp);
            }
            else
            {
                int z=x-y;
                tmp+=(z-1)*ql+min(w[i]*r,w[i]*l+ql);
                res=min(res,tmp);
            }
        }
        cout<<res<<endl;
    }
    return 0;
}
