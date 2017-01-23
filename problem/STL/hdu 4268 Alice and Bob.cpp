#include <iostream>
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
const int maxn=100000+10;
struct Node
{
    int x,y;
    bool operator < (const Node & a) const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
};
Node a[maxn],b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
          scanf("%d%d",&a[i].x,&a[i].y);
        for(int i=0;i<n;++i)
          scanf("%d%d",&b[i].x,&b[i].y);
        sort(a,a+n);
        sort(b,b+n);
        multiset<int>s;
        multiset<int>::iterator it;
        int k=0,ans=0;
        for(int j=0;j<n;++j)
        {
            while(k<n&&a[j].x>=b[k].x) s.insert(b[k++].y);
            it=s.upper_bound(a[j].y);
            if(it!=s.begin()) ans++,s.erase(--it);
        }
        printf("%d\n",ans);
    }
    return 0;
}
