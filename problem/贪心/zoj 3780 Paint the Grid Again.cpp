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
const int maxn=500+10;
char mat[maxn][maxn];
int cntx[maxn],cnty[maxn],n,rx,ry;
int ans[maxn*maxn][2],tot;
bool cal()
{
    int x=-1,y=-1;
    for(int i=n;i>=1;--i)
        if(rx==cntx[i]&&cntx[i]) {x=i;break;}
        else if(ry==cnty[i]&&cnty[i]) {y=i;break;}
    if(x!=-1)
    {
        ans[tot][0]=0;
        ans[tot++][1]=x;
        cntx[x]=-2;
        ry--;
        return true;
    }
    if(y!=-1)
    {
        ans[tot][0]=1;
        ans[tot++][1]=y;
        cnty[y]=-2;
        rx--;
        return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%s",mat[i]+1);
        memset(cntx,0,sizeof(cntx));
        memset(cnty,0,sizeof(cnty));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(mat[i][j]=='X') cntx[i]++;
                else cnty[j]++;
        rx=ry=n;
        tot=0;
        while(cal());
        bool flag=true;
        for(int i=1;i<=n;++i)
            if(cntx[i]>0||cnty[i]>0) flag=false;
        if(flag)
        {
            for(int i=tot-1;i>=0;--i)
            {
                if(i!=tot-1) printf(" ");
                if(ans[i][0]==0) printf("R");
                else printf("C");
                printf("%d",ans[i][1]);
            }
            printf("\n");
        }
        else printf("No solution\n");
    }
    return 0;
}

