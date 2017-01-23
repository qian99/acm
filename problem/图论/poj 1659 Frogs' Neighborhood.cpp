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
int maze[15][15];
int n;
struct Node
{
    int degree;
    int num;
    bool operator < (const Node &a) const
    {
        return degree>a.degree;
    }
};
Node node[15];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(maze,0,sizeof(maze));
        for(int i=0;i<n;++i)
        {
            scanf("%d",&node[i].degree);
            node[i].num=i;
        }
        sort(node,node+n);
        bool flag=true;
        while(node[0].degree)
        {
            int i=1;
            while(node[0].degree--)
            {
                if(!node[i].degree)
                {
                    flag=false;
                    break;
                }
                node[i].degree--;
                maze[node[0].num][node[i].num]=1;
                maze[node[i].num][node[0].num]=1;
                i++;
            }
            sort(node,node+n);
        }
        if(flag)
        {
            printf("YES\n");
            for(int i=0;i<n;++i)
            {
                printf("%d",maze[i][0]);
                for(int j=1;j<n;++j)
                  printf(" %d",maze[i][j]);
                printf("\n");
            }
        }
        else printf("NO\n");
        if(t) printf("\n");
    }
    return 0;
}
