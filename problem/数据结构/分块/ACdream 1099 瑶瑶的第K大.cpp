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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=5000000+10;
const int Size=10000;
int cnt[Size+10];
int a[maxn],b[Size];
void reads(int & x)
{
    char c;
    bool neg=false;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')
    {
        neg=true;
        while((c=getchar())<'0'||c>'9');
    }
    x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';
    if(neg) x=-x;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;++i)
    {
//        scanf("%d",&a[i]);
        reads(a[i]);
        cnt[a[i]/Size]++;
    }
    int pos=Size;
    for(;pos>=0;--pos)
    {
        if(cnt[pos]<k) k-=cnt[pos];
        else break;
    }
    int tot=0;
    for(int i=0;i<n;++i)
        if(a[i]/Size==pos) b[tot++]=a[i];
    sort(b,b+tot);
    printf("%d\n",b[tot-k]);
    return 0;
}