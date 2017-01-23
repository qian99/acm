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
typedef long long ll;
const int maxn=50;
struct Point
{
    int x,y;
};
Point Hul[maxn*maxn],Cul[maxn*maxn];
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int hm=0,cm=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            for(int j=0;j<m;++j)
            {
                if(str[j]=='H') Hul[hm++]=(Point){i,j};
                else if(str[j]=='C') Cul[cm++]=(Point){i,j};
            }
        }
        Point hululu,cululu;
        int minlen=inf;
        for(int i=0;i<hm;++i)
        {
            for(int j=0;j<cm;++j)
            {
                int len=abs(Hul[i].x-Cul[j].x)+abs(Hul[i].y-Cul[j].y);
                if(len<minlen)
                {
                    minlen=len;
                    hululu=Hul[i];
                    cululu=Cul[j];
                }
                else if(len==minlen)
                {
                    if(hululu.x==Hul[i].x&&hululu.y==Hul[i].y)
                    {
                        if(cululu.x>Cul[j].x||(cululu.x==Cul[j].x&&cululu.y>Cul[j].y))
                            cululu=Cul[j];
                    }
                    else if(hululu.x>Hul[i].x||(hululu.x==Hul[i].x&&hululu.y>Hul[i].y))
                    {
                        hululu=Hul[i];
                        cululu=Cul[j];
                    }
                }
            }
        }
        printf("%d %d %d %d\n",hululu.x,hululu.y,cululu.x,cululu.y);
    }
    return 0;
}
