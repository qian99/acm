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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;

const int maxn=10000+10;
int g[maxn];
map<int,int>p;

int main()
{
    int m,n;
    while(~scanf("%d%d",&m,&n))
    {
        int u=sqrt((double)m);
        int w=0;
        for(int i=1;i<=u;++i)
        {
            if(m%i==0)
            {
                g[w++]=i;
                if(i!=m/i)
                g[w++]=m/i;
            }
        }
        sort(g,g+w);
        p.clear();
        int temp,tmp;
        for(int i=1;i<w;++i)
        {
            temp=g[i]/2+1;
            for(int j=1;j<i;++j)
            {
                if(g[i]%g[j]==0)
                {
                    tmp=min((g[j]/2+1)*p[g[i]/g[j]],(g[i]/g[j]/2+1)*p[g[j]]);
                    temp=min(temp,tmp);
                }
            }
            p[g[i]]=temp;
        }
        if(p[m]<=n)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        printf("%d\n",p[m]);
    }
    return 0;
}
