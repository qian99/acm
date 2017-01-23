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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
pair<int ,int >p[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        int cnt=0,tmp;
        while(n--)
        {
            scanf("%d",&tmp);
            p[cnt].first=-tmp,p[cnt].second=cnt;
            if(tmp==0)
            {
                sort(p,p+cnt);
                for(int i=0;i<cnt;++i)
                {
                    if(i==p[0].second) printf("pushStack\n");
                    else if(i==p[1].second) printf("pushQueue\n");
                    else if(i==p[2].second) printf("pushFront\n");
                    else printf("pushBack\n");
                }
                cnt=min(cnt,3);
                printf("%d",cnt);
                if(cnt>0) printf(" popStack");
                if(cnt>1) printf(" popQueue");
                if(cnt>2) printf(" popFront");
                printf("\n");
                cnt=0;
            }
            else cnt++;
        }
        for(int i=0;i<cnt;++i)
          printf("pushQueue\n");
    }
    return 0;
}
