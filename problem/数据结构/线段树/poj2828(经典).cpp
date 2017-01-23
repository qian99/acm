#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=200000+10;
int space[maxn<<2],num[maxn][2],res[maxn];
int id;
void Pushup(int rt)
{
    space[rt]=space[rt<<1]+space[rt<<1|1];
}
void build(int l,int r,int rt)
{
    space[rt]=r-l+1;
    if(l==r) return;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt)
{
    space[rt]--;
    if(l==r)
    {
        id=l;
        return;
    }
    int m=(l+r)>>1;
    if(space[rt<<1]>=p)
    {
        Update(p,l,m,rt<<1);
    }
    else
    {
        p-=space[rt<<1];
        Update(p,m+1,r,rt<<1|1);
    }

}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        build(1,n,1);
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&num[i][1],&num[i][0]);
            num[i][1]++;
        }
        //int maxnnum=0;
        for(int i=n-1;i>=0;--i)
        {
            Update(num[i][1],1,n,1);
            res[id-1]=num[i][0];
        }
        printf("%d",res[0]);
        for(int i=1;i<n;++i)
        {
            printf(" %d",res[i]);
        }
        printf("\n");
    }
    return 0;
}

