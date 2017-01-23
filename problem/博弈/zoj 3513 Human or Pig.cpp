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
const int maxn=40000+10;
char res[maxn];
int n,m;
inline int getp(int x,int y) { return (x-1)*m+y-1;}
char cal(int x,int y)
{
    if(x==y) return res[getp(x,y)]='P';
    if(x%y==0||y%x==0) return res[getp(x,y)]='H';
    if(x>y)
    {
        for(int i=1;x-y*i>0;i++)
            if(res[getp(x-i*y,y)]=='P') return res[getp(x,y)]='H';
    }
    else
    {
        for(int i=1;y-x*i>0;i++)
            if(res[getp(x,y-x*i)]=='P') return res[getp(x,y)]='H';
    }
    return res[getp(x,y)]='P';
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        printf("Case #%d:\n",++tcase);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
                printf("%c",cal(i,j));
            printf("\n");
        }
    }
    return 0;
}
