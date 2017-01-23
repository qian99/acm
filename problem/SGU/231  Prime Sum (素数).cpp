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
const int maxn=1000000+10;
int primes[100000],pcnt;
bool flag[maxn];
vector<int>vt;
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    flag[0]=flag[1]=true;
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
    getprimes();
    int n,val;
    cin>>n;
    for(int i=0;i<pcnt;++i)
    {
        val=2+primes[i];
        if(val<=n&&!flag[val])
        {
            vt.push_back(primes[i]);
        }
    }
    int size=vt.size();
    cout<<size<<endl;
    for(int i=0;i<size;++i)
        cout<<2<<" "<<vt[i]<<endl;
    return 0;
}
