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
const int maxn=100+10;
char s1[maxn],s2[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%s",s1);
        scanf("%s",s2);
        int n=strlen(s1);
        int flag=0;
        if(n==2)
        {
            for(int i=0;i<26;++i)
            {
                if(s1[0]==s2[0]&&s1[1]==s2[1]) flag=1;
                swap(s1[0],s1[1]);
                s1[0]++;s1[1]++;
                if(s1[0]>'z') s1[0]='a';
                if(s1[1]>'z') s1[1]='a';
            }
        }
        else
        {
            int x=0,y=0;
            for(int i=0;i<n;++i)
            {
                x+=s1[i];
                y+=s2[i];
            }
            x&=1;y&=1;
            flag=x==y;
        }
        printf("Case #%d: ",tcase);
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
