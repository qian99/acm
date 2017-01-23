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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
char str[10][10]={
    "a",
    "ab",
    "aab",
    "aabb",
    "aaaba",
    "aaabab",
    "aaababb",
    "aaababbb"
};
char strp[10]="babbaa";
char strk[10][10]={
    "a",
    "aa",
    "bab",
    "babb",
    "babba"
};
char ans[maxn];
void solve(int M,int N)
{
    if(M==1)
    {
        for(int i=0;i<N;++i)
            ans[i]='a';
        ans[N]='\0';
        return;
    }
    else if(M==2)
    {
        if(N<=8)
        {
            for(int i=0;i<N;++i)
                ans[i]=str[N-1][i];
            ans[N]='\0';
        }
        else
        {
            int i=0;
            for(;i<4;++i) ans[i]='a';
            while(i+6<=N)
            {
                for(int j=0;j<6;++j)
                    ans[i+j]=strp[j];
                i+=6;
            }
            for(int j=0;j<N-i;++j)
                ans[i+j]=strk[N-i-1][j];
            ans[N]='\0';
        }
        return ;
    }
    else
    {
        for(int i=0;i<N;++i)
            ans[i]='a'+(i%3);
        ans[N]='\0';
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int M,N,t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&M,&N);
        solve(M,N);
        printf("Case #%d: %s\n",++tcase,ans);
    }
    return 0;
}
