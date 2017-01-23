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
const int maxn=50000+10;
int n,m,L;
int stone[maxn];
bool test(int mid)
{
    int move=0,step=0;
    int pos=0,tmp;
    while(move<L&&step<m)
    {
        tmp=move+mid;
        step++;
        if(tmp>=L) return true;
        while(tmp>=stone[pos]&&pos<n) move=stone[pos++];
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&L,&n,&m))
    {
        for(int i=0;i<n;++i)
          scanf("%d",&stone[i]);
        sort(stone,stone+n);
        int l=1,r=L,mid;
        while(l<r)
        {
            mid=(l+r)>>1;
            if(test(mid))
                r=mid;
            else l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
