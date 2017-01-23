//我虔诚的阅读了RP导论
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
const int maxn=500+10;
bool vis[maxn][maxn];
int num1[maxn],num2[maxn];

int main()
{
    //printf("%.3lf\n",0.55555);
    //freopen("in.txt","w",stdin);
    //freopen("out.txt","r",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        int sum=0;
        scanf("%d%d",&n,&m);
        memset(vis,0,sizeof(vis));
        for(int i=0;i<m;++i)
            scanf("%d",&num1[i]);
        for(int i=0;i<m;++i)
            scanf("%d",&num2[i]);
        for(int i=0;i<m;++i)
        {
            if(!vis[num1[i]][num2[i]])
            {
                vis[num1[i]][num2[i]]=vis[num2[i]][num1[i]]=true;
                sum++;
            }
        }
        double ans=(double)sum/n;
        printf("%.3lf\n",ans);
    }
    return 0;
}
