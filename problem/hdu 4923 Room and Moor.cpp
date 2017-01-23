#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int a[maxn],tot;
struct Node
{
    double val;
    int cnt;
    Node(double val=0,int cnt=0):val(val),cnt(cnt){}
}S[maxn];
void ajust()
{
    if(tot<=1) return ;
    if(S[tot-1].val<=S[tot-2].val)
    {
        S[tot-2].val=(S[tot-1].val*S[tot-1].cnt+S[tot-2].val*S[tot-2].cnt)/(S[tot-1].cnt+S[tot-2].cnt);
        S[tot-2].cnt=(S[tot-1].cnt+S[tot-2].cnt);
        tot--;
        ajust();
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        tot=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            S[tot++]=Node(a[i],1);
            ajust();
        }
        double ans=0;
        int now=0;
        for(int j=1;j<=n;++j)
        {
            ans+=(S[now].val-a[j])*(S[now].val-a[j]);
            S[now].cnt--;
            if(S[now].cnt==0) now++;
        }
        printf("%.6lf\n",ans);
    }
    return 0;
}
