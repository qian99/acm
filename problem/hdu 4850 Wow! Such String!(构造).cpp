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
const int maxn=500000+10;
int s[maxn];
int tot;
bool vis[26][26][26][26];
void Init()
{
    tot=0;
    for(int i=0;i<26;++i)
        for(int j=0;j<4;++j)
            s[tot++]=i;
    for(int i=3;i<tot;++i)
        vis[s[i-3]][s[i-2]][s[i-1]][s[i]]=true;
    bool flag=true;
    while(flag)
    {
        flag=false;
        for(int i=0;i<26;++i)
        {
            if(!vis[s[tot-3]][s[tot-2]][s[tot-1]][i])
            {
                vis[s[tot-3]][s[tot-2]][s[tot-1]][i]=true;
                s[tot++]=i;
                flag=true;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n;
    while(~scanf("%d",&n))
    {
        if(n>tot) printf("Impossible\n");
        else
        {
            for(int i=0;i<n;++i)
                putchar(s[i]+'a');
            printf("\n");
        }
    }
    return 0;
}
