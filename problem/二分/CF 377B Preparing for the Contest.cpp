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
struct Bug
{
    int compx,id;
    bool operator <(const Bug &a)const
    {
        return compx>a.compx;
    }
}bug[maxn];
struct Stu
{
    int lev,cost,id;
    bool operator <(const Stu &a)const
    {
        return cost>a.cost;
    }
}stu[maxn];
bool cmp(Stu a,Stu b)
{
    return a.lev>b.lev;
}
int n,m,s,res[maxn];
bool test(int t)
{
    priority_queue<Stu>q;
    int i=0,j=0;
    ll tot=0;
    while(i<m)
    {
        while(j<n&&stu[j].lev>=bug[i].compx) q.push(stu[j]),j++;
        if(q.empty()) return false;
        Stu bstu=q.top();q.pop();
        tot+=bstu.cost;
        if(tot>s) return false;
        for(int k=0;k<t;++k)
        {
            if(i+k>=m) return true;
            res[bug[i+k].id]=bstu.id;
        }
        i+=t;
    }
    return true;
}
bool solve()
{
    int l=1,r=m;
    int mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(test(mid))
            r=mid;
        else
            l=mid+1;
    }
    return test(l);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&s);
    for(int i=0;i<m;++i)
    {
        scanf("%d",&bug[i].compx);
        bug[i].id=i;
    }
    for(int i=0;i<n;++i)
    {
        scanf("%d",&stu[i].lev);
        stu[i].id=i;
    }
    for(int i=0;i<n;++i)
        scanf("%d",&stu[i].cost);
    sort(bug,bug+m);
    sort(stu,stu+n,cmp);
    if(solve())
    {
        printf("YES\n");
        for(int i=0;i<m;++i)
        {
            if(i) printf(" ");
            printf("%d",res[i]+1);
        }
        printf("\n");
    }
    else
        printf("NO\n");
    return 0;
}
