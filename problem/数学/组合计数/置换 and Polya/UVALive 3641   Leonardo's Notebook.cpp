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
const int maxn=26;
char str[maxn+10];
int cnt[maxn+10];
bool vis[maxn+10];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        memset(vis,0,sizeof(vis));
        memset(cnt,0,sizeof(cnt));
        int tmp;
        for(int i=0;i<maxn;++i)
        {
            if(vis[i]) continue;
            tmp=0;
            int j=str[i]-'A';
            while(!vis[j])
            {
                vis[j]=true;
                j=str[j]-'A';
                tmp++;
            }
            cnt[tmp]++;
        }
        bool flag=true;
        for(int i=0;i<maxn;i+=2)
            if(cnt[i]&1) flag=false;
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}
