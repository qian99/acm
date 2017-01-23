#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100+10;
bool rel[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,k,a,b;
        scanf("%d%d%d",&n,&m,&k);
        memset(rel,0,sizeof(rel));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            rel[a][b]=true;
            rel[b][a]=true;
        }
        bool find=true;
        int ans=0;
        while(find)
        {
            find=false;
            for(int i=0;i<n;++i)
            {
                for(int j=0;j<n;++j)
                {
                    if(i!=j&&!rel[i][j])
                    {
                        int v=0;
                        for(int u=0;u<n;++u)
                        {
                            if(i!=u&&j!=u&&rel[i][u]&&rel[u][j])
                            {
                                v++;
                            }
                        }
                        if(v>=k)
                        {
                            find=true;
                            rel[i][j]=rel[j][i]=true;
                            ans++;
                        }
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
