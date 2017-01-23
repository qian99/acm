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
const int maxn=30000+10;
int lf[maxn<<2],rn[maxn<<2];
char str[maxn];
void PushUp(int rt)
{
    int tmp=min(lf[rt<<1],rn[rt<<1|1]);
    lf[rt]=lf[rt<<1]+lf[rt<<1|1]-tmp;
    rn[rt]=rn[rt<<1]+rn[rt<<1|1]-tmp;
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        lf[rt]=rn[rt]=0;
        if(str[l]=='(') lf[rt]=1;
        else rn[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt)
{
    if(l==r)
    {
        lf[rt]^=1;
        rn[rt]^=1;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1);
    else Update(p,m+1,r,rt<<1|1);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int tcase=1;tcase<=10;++tcase)
    {
        int n;
        scanf("%d",&n);
        scanf("%s",str+1);
        build(1,n,1);
        int q,x;
        scanf("%d",&q);
        printf("Test %d:\n",tcase);
        while(q--)
        {
            scanf("%d",&x);
            if(x>0) Update(x,1,n,1);
            else
            {
                if(lf[1]||rn[1]) puts("NO");
                else puts("YES");
            }
        }
    }
    return 0;
}
