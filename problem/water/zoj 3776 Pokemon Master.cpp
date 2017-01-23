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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int s1=0,s2=0,tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            s1+=tmp;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d",&tmp);
            s2+=tmp;
        }
        if(s1>s2)
            printf("Calem\n");
        else if(s1==s2)
            printf("Draw\n");
        else
            printf("Serena\n");
    }
    return 0;
}

