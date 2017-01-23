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
int a[maxn],pos[maxn],ans[maxn<<3][2],cnt;
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
            for(int j=i+i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
void Swap(int i,int j)
{
    ans[cnt][0]=i;
    ans[cnt++][1]=j;
    swap(pos[a[i]],pos[a[j]]);
    swap(a[i],a[j]);
}
int f(int p,int len)
{
    int l=0,r=pcnt;
    while(r-l>1)
    {
        int m=(l+r)>>1;
        if(primes[m]<=len) l=m;
        else r=m;
    }
    int k=p-primes[l]+1;
    return k;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        pos[a[i]]=i;
    }
    cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==i) continue;
        int j=pos[i];
        if(!flag[j-i+1]) Swap(i,j);
        else
        {
            int k;
            while(true)
            {
                k=f(j,j-i+1);
                Swap(k,j);
                j=k;
                if(j==i) break;
            }
        }
    }
    printf("%d\n",cnt);
    for(int i=0;i<cnt;++i)
        printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}