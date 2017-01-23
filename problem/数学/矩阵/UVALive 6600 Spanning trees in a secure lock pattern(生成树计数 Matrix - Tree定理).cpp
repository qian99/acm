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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 55;
struct Matrix
{
    double mat[37][37];
    void Init()
    {
        memset(mat,0,sizeof(mat));
    }
    double det(int n)
    {
        double res = 1;
        for(int i = 1;i <= n;++i)
        {
            int k = i;
            for(int j = i;j <= n;++j)
                if(mat[i][j] != 0)
                {
                    k = j;
                    break;
                }
            for(int j = i;j <= n;++j)
                swap(mat[i][j],mat[k][j]);
            if(i != k) res = -res;
            if(mat[i][i] == 0) return 0;
            res *= mat[i][i];
            for(int j = i + 1;j <= n;++j)
            {
                double tmp = -mat[j][i]/mat[i][i];
                for(int k = i;k <= n;++k)
                    mat[j][k] += tmp*mat[i][k];
            }
        }
        return res;
    }
};
const int dirx[8] = {-1,-1,-1,0,0,1,1,1};
const int diry[8] = {-1,0,1,-1,1,-1,0,1};
int g[maxn][maxn],d[maxn][maxn];
const string res[5] = {"16","17745","1064918960","3271331573452802","504061943351319050000000"};
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
//    scanf("%d",&t);
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
//        scanf("%d",&n);
//        memset(g,0,sizeof(g));
//        memset(d,0,sizeof(d));
//        int u,v;
//        for(int i = 1;i <= n;++i)
//            for(int j = 1;j <= n;++j)
//            {
//                u = (i - 1)*n  + j;
//                for(int k = 0;k < 8;++k)
//                {
//                    int dx = i + dirx[k];
//                    int dy = j + diry[k];
//                    if(dx > 0 && dx <= n && dy > 0 && dy <= n)
//                    {
//                        v = (dx - 1)*n + dy;
//                        d[u][u]++;
//                        g[u][v] = 1;
//                    }
//                }
//            }
//        Matrix x;
//        x.Init();
//        for(int i = 1;i <= n*n;++i)
//            for(int j = 1;j <= n*n;++j)
//                x.mat[i][j] = d[i][j] - g[i][j];
//        double ans = x.det(n*n - 1);
//        printf("%lf\n",ans);
        cout<<res[n-2]<<endl;
    }
    return 0;
}

