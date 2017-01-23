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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=55;
char a[maxn][maxn],b[maxn][maxn];
char convert[maxn];
void Init()
{
    for(int i=0;i<26;++i)
        convert[i]='A'+i;
    for(int i=0;i<26;++i)
        convert[i+26]='a'+i;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    bool flag=false;
    Init();
    while(~scanf("%d",&n))
    {
        if(flag) puts("");
        flag=true;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
            {
                a[i][j]=convert[i];
                b[i][j]=convert[j];
            }
        printf("2 %d %d\n",n,n);
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
                putchar(a[i][j]);
            printf("\n");
        }
        printf("\n");
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
                putchar(b[i][j]);
            printf("\n");
        }
    }
    return 0;
}
