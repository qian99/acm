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
const int maxn=100+10;
int a[maxn][maxn],id[maxn],to[maxn][2],n;
void Init()
{
    n=30+2+29*2;
    memset(a,0,sizeof(a));
    int cnt=3;
    for(int i=0;i<30;++i)
        id[i]=cnt++;
    a[1][cnt-1]=a[cnt-1][1]=1;
    for(int i=0;i<29;++i)
        a[id[i]][id[i+1]]=a[id[i+1]][id[i]]=1;
    a[2][cnt]=a[cnt][2]=1;
    a[2][cnt+1]=a[cnt+1][2]=1;
    int x,y;
    for(int i=0;i<29;++i)
    {
        x=cnt+i*2;y=cnt+(i+1)*2;
        a[x][y]=a[y][x]=1;
        a[x][y+1]=a[y+1][x]=1;
        a[x+1][y]=a[y][x+1]=1;
        a[x+1][y+1]=a[y+1][x+1]=1;
        to[i+1][0]=x;to[i+1][1]=x+1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k;
    while(~scanf("%d",&k))
    {
        Init();
        if(k&1) a[id[0]][2]=a[2][id[0]]=1;
        for(int i=1;i<30;++i)
        {
            if(k&(1<<i))
            {
                a[id[i]][to[i][0]]=a[to[i][0]][id[i]]=1;
                a[id[i]][to[i][1]]=a[to[i][1]][id[i]]=1;
            }
        }
        printf("%d\n",n);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
                if(a[i][j]) putchar('Y');
                else putchar('N');
            puts("");
        }
    }
    return 0;
}
