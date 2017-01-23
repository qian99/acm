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
const int maxn=10000+100;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    pcnt=0;
    memset(flag,0,sizeof(flag));
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(int j=i*2;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    getprimes();
    while(cin>>n)
    {
        if(n==0) break;
        int cnt=0;
        for(int i=0;i<pcnt;++i)
        {
            if(primes[i]*2>=n) break;
            if(!flag[n-primes[i]]) cnt++;
        }
        cout<<cnt<<endl;
    }
    return 0;
}
