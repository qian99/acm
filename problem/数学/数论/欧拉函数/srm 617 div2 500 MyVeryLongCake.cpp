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
const int maxn=40000+10;
class MyVeryLongCake
{
    public:
    int primes[maxn],pcnt;
    bool flag[maxn];
    void getprimes()
    {
        memset(flag,0,sizeof(flag));
        pcnt=0;
        for(int i=2;i<maxn;++i)
        {
            if(!flag[i])
            {
                primes[pcnt++]=i;
                for(int j=i*i;j<maxn;j+=i)
                    flag[j]=true;
            }
        }
    }
    int euler_phi(int n)
    {
        int ans=n;
        for(int i=0;primes[i]*primes[i]<=n;++i)
        {
            if(n%primes[i]==0)
            {
                ans=ans-ans/primes[i];
                while(n%primes[i]==0) n/=primes[i];
            }
        }
        if(n>1) ans=ans-ans/n;
        return ans;
    }
    int cut(int n)
    {
        getprimes();
        return n-euler_phi(n);
    }
};
//int main()
//{
//    freopen("in.txt","r",stdin);
//    //freopen("out.txt","w",stdout);
//    MyVeryLongCake tmp;
//    int n;
//    while(cin>>n)
//    {
//        cout<<tmp.cut(n)<<endl;
//    }
//    return 0;
//}
