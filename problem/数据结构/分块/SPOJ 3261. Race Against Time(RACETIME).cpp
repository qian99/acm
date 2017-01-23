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
const int Size=355;
int block[Size+10][Size+10];
int num[maxn];
void Init(int n)
{
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num[i]);
        block[i/Size][i%Size]=num[i];
    }
    for(int i=0;i<=n/Size;++i)
        sort(block[i],block[i]+Size);
}
void Modify(int p,int x)
{
    int y=num[p];
    num[p]=x;
    int bk=p/Size;
    for(int i=0;i<Size;++i)
        if(block[bk][i]==y)
        {
            block[bk][i]=x;
            break;
        }
    sort(block[bk],block[bk]+Size);
}
int Query(int L,int R,int X)
{
    int Lb=L/Size,Rb=R/Size;
    int cnt=0;
    if(Lb==Rb)
    {
        for(int i=L;i<=R;++i)
            cnt+=(num[i]<=X);
    }
    else
    {
        for(int i=L;i<(Lb+1)*Size;++i)
            cnt+=(num[i]<=X);
        for(int i=Rb*Size;i<=R;++i)
            cnt+=(num[i]<=X);
        for(int i=Lb+1;i<Rb;++i)
            cnt+=upper_bound(block[i],block[i]+Size,X)-block[i];
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    char str[5];
    while(~scanf("%d%d",&n,&q))
    {
        Init(n);
        int L,R,X;
        while(q--)
        {
            scanf("%s",str);
            if(str[0]=='M')
            {
                scanf("%d%d",&L,&X);
                Modify(L-1,X);
            }
            else
            {
                scanf("%d%d%d",&L,&R,&X);
                int ans=Query(L-1,R-1,X);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
