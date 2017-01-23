#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500+10;
int mat[maxn][maxn][2],p[maxn];
bool vis[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                scanf("%d%d",&mat[i][j][0],&mat[i][j][1]);
        bool flag ;
        int fst;
        for(int i = 0;i < n;++i)
        {
            flag = true;
            for(int j = 0; j < n;++j)
                if(mat[i][j][0] != mat[i][j][1])
                    flag = false;
            if(flag)
            {
                fst = i;
                break;
            }
        }
        if(n == 2)
        {
            p[0] = mat[0][0][0];
            p[1] = 1 - mat[0][0][0];
        }
        else
        {
            p[0] = mat[fst][0][0];
            for(int i = 0; i < n;++i)
            {
                if(i == fst) continue;
                memset(vis,0,sizeof(vis));
                int cnt = 0;
                for(int j = 0;j < n;++j)
                {
                    if(!vis[mat[i][j][0]])
                    {
                        vis[mat[i][j][0]] = true;
                        cnt++;
                    }
                }
                p[cnt] = i;
            }
        }
        printf("Case #%d:",++tcase);
        for(int i = 0;i < n;++i)
            printf(" %d",p[i]);
        printf("\n");
    }
    return 0;
}
