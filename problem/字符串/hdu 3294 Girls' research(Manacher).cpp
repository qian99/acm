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
const int maxn=200000+10;
const int mod=26;
char str[maxn],s[maxn<<1];
int p[maxn<<1];
void Manacher()
{
    int n=0;
    s[n++]='$';s[n++]='#';
    for(int i=0;str[i];i++)
    {
        s[n++]=str[i];
        s[n++]='#';
    }
    int mx=0,id=0,ans=0;
    p[0]=0;
    for(int i=1;i<n;++i)
    {
        p[i]=1;
        if(mx>i) p[i]=min(p[id*2-i],mx-i);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>mx)
        {
            mx=i+p[i];
            id=i;
        }
        if(p[i]>ans) ans=p[i];
    }
    if(ans-1<2)
    {
        printf("No solution!\n");
        return ;
    }
    int S=-1,T=-1,x;
    for(int i=1;i<n;++i)
        if(p[i]==ans)
        {
            if(s[i]=='#')
            {
                x=(i-1)/2-1;
                S=x-(ans-1)/2+1;
                T=x+(ans-1)/2;
                break;
            }
            else
            {
                x=i/2-1;
                S=x-(ans-1)/2;
                T=x+(ans-1)/2;
                break;
            }
        }
    printf("%d %d\n",S,T);
    for(int i=S;i<=T;++i)
        printf("%c",str[i]);
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char to[5];
    while(~scanf("%s%s",to,str))
    {
        int k=to[0]-'a',tmp;
        for(int i=0;str[i];++i)
        {
            tmp=str[i]-'a'-k;
            if(tmp<0) tmp+=mod;
            str[i]='a'+tmp;
        }
        Manacher();
    }
    return 0;
}
