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
const int maxn=20000;
struct Zone
{
    int id,Qlevel,num;
    bool operator <(const Zone &a) const
    {
        return Qlevel>a.Qlevel;
    }
}zone[110];
struct Student
{
    int id,Plevel,w;
    bool operator <(const Student &a) const
    {
        return w>a.w;
    }
}stu[maxn];
int res[maxn];
void solve(int k,int n)
{
    memset(res,0,sizeof(res));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<k;++j)
        {
            if(stu[i].Plevel>zone[j].Qlevel&&zone[j].num>0)
            {
                res[stu[i].id]=zone[j].id;
                zone[j].num--;
                break;
            }
        }
    }
    for(int i=0;i<n;++i)
    {
        if(res[stu[i].id]) continue;
        for(int j=0;j<k;++j)
        {
            if(zone[j].num>0)
            {
                res[stu[i].id]=zone[j].id;
                zone[j].num--;
                break;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(i!=1) printf(" ");
        printf("%d",res[i]);
    }
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k,n=0;
    scanf("%d",&k);
    for(int i=0;i<k;++i)
    {
        scanf("%d",&zone[i].num);
        n+=zone[i].num;
        zone[i].id=i+1;
    }
    for(int i=0;i<k;++i)
       scanf("%d",&zone[i].Qlevel);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&stu[i].Plevel);
        stu[i].id=i+1;
    }
    for(int i=0;i<n;++i)
       scanf("%d",&stu[i].w);
    sort(zone,zone+k);
    sort(stu,stu+n);
    solve(k,n);
    return 0;
}
