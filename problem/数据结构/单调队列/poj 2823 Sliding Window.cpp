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
struct Node
{
    int val,pos;
};
Node q1[maxn],q2[maxn];
int sq1,tq1,sq2,tq2,n,k;
int ans1[maxn],ans2[maxn];
inline void inq1(int v,int p)
{
    while(sq1!=tq1&&v>=q1[tq1-1].val) tq1--;
    q1[tq1].pos=p;q1[tq1++].val=v;
}
inline void out1(int p)
{
    if(q1[sq1].pos<=p-k) sq1++;
}
inline void inq2(int v,int p)
{
    while(sq2!=tq2&&v<=q2[tq2-1].val) tq2--;
    q2[tq2].pos=p;q2[tq2++].val=v;
}
inline void out2(int p)
{
    if(q2[sq2].pos<=p-k) sq2++;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&k))
    {
        sq1=sq2=tq1=tq2=0;
        int tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            inq1(tmp,i);
            if(i>=k-1)
            {
                out1(i);
                ans1[i]=q1[sq1].val;
            }
            inq2(tmp,i);
            if(i>=k-1)
            {
                out2(i);
                ans2[i]=q2[sq2].val;
            }
        }
        for(int i=k-1;i<n;++i)
        {
            if(i!=k-1) printf(" ");
            printf("%d",ans2[i]);
        }
        printf("\n");
        for(int i=k-1;i<n;++i)
        {
            if(i!=k-1) printf(" ");
            printf("%d",ans1[i]);
        }
        printf("\n");
    }
    return 0;
}
