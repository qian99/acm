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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
int num[maxn],mod[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int c,n;
    while(~scanf("%d%d",&c,&n))
    {
        if(c==0&&n==0) break;
        memset(mod,0xff,sizeof(mod));
        bool flag=false;
        for(int i=0;i<n;++i)
            scanf("%d",&num[i]);
        ll sum=0;
        int m;
        for(int i=0;i<n;++i)
        {
            sum+=num[i];
            m=sum%c;
            if(m==0)
            {
                flag=true;
                printf("1");
                for(int j=1;j<=i;++j)
                    printf(" %d",j+1);
                printf("\n");
                break;
            }
            if(mod[m]!=-1)
            {
                flag=true;
                for(int j=mod[m]+1;j<=i;++j)
                {
                    if(j!=mod[m]+1) printf(" ");
                    printf("%d",j+1);
                }
                printf("\n");
                break;
            }
            else mod[m]=i;
        }
        if(!flag) printf("no sweets\n");
    }
    return 0;
}
