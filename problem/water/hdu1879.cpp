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
const int maxn=1000+10;
struct Homework
{
    int deadline,scores;
};
Homework hh[maxn];
bool flag[maxn];
bool cmp(Homework a,Homework b)
{
    return a.scores>b.scores;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    int n;
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
           scanf("%d",&hh[i].deadline);
        for(int i=0;i<n;++i)
           scanf("%d",&hh[i].scores);
        sort(hh,hh+n,cmp);
        int sum=0;
        memset(flag,0,sizeof(flag));
        for(int i=0;i<n;++i)
        {
            int u=hh[i].deadline;
            while(flag[u]&&u>0)
            {
                u--;
            }
            if(u==0)
              sum+=hh[i].scores;
            else
              flag[u]=true;
        }
        printf("%d\n",sum);
    }
    return 0;
}
