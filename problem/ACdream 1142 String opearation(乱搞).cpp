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
const int maxn=110000+100;
char str[maxn],s[1111];
vector<int>cpos[30];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%s",str);
        n=strlen(str);
        for(int i=0;i<30;++i) cpos[i].clear();
        for(int i=0;i<n;++i)
        {
            cpos[str[i]-'a'].push_back(i);
        }
        scanf("%d",&m);
        while(m--)
        {
            int type;
            scanf("%d%s",&type,s);
            int len=strlen(s);
            if(type==1)
            {
                for(int i=0;i<len;++i)
                {
                    str[n+i]=s[i];
                    cpos[s[i]-'a'].push_back(n+i);
                }
                n+=len;
            }
            else
            {
                bool flag=false;
                for(int k=0;k<(int)cpos[s[0]-'a'].size();++k)
                {
                    int start=cpos[s[0]-'a'][k];
                    int now=1,pos=start;
                    for(;now<len;++now)
                    {
                        int tmp=s[now]-'a';
                        int x=upper_bound(cpos[tmp].begin(),cpos[tmp].end(),pos)-cpos[tmp].begin();
                        if(x>=(int)cpos[tmp].size()) break;
                        pos=cpos[tmp][x];
                    }
                    if(now<len)
                    {
                        pos=-1;
                        for(;now<len;++now)
                        {
                            int tmp=s[now]-'a';
                            int x=upper_bound(cpos[tmp].begin(),cpos[tmp].end(),pos)-cpos[tmp].begin();
                            if(x>=(int)cpos[tmp].size()||cpos[tmp][x]>=start) break;
                            pos=cpos[tmp][x];
                        }
                    }
                    if(now>=len) {flag=true;break;}
                }
                if(flag) puts("YES");
                else puts("NO");
            }
        }
    }
    return 0;
}
