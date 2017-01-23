#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
char num1[maxn],num2[maxn];
int res[maxn];
int cntA[15],cntB[15];
int getNum(int x,int flag)
{
    int sum=0;
    for(int i=x-flag;i>=flag;--i)
    {
        if(cntA[i]>0&&cntB[x-i]>0)
        {
            cntA[i]--;cntB[x-i]--;
            sum++;
            if(flag) return sum;
        }
    }
    for(int j=9;j>=0;--j)
    {
        if(x-j>=0) break;
        if(cntA[10+x-j]>0&&cntB[j]>0)
        {
            cntA[10+x-j]--;cntB[j]--;
            sum++;
            if(flag) return sum;
        }
    }
    for(int j=9;j>=0;--j)
    {
        if(x-j>=0) break;
        if(cntB[10+x-j]>0&&cntA[j]>0)
        {
            cntB[10+x-j]--;cntA[j]--;
            sum++;
            if(flag) return sum;
        }
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%s",num1);
        scanf("%s",num2);
        int na=strlen(num1);
        int nb=strlen(num2);
        memset(cntA,0,sizeof(cntA));
        memset(cntB,0,sizeof(cntB));
        for(int i=0;i<na;++i)
          if(na>nb) cntA[num1[i]-'0']++;
          else cntB[num1[i]-'0']++;
        for(int i=0;i<nb;++i)
          if(na>nb) cntB[num1[i]-'0']++;
          else cntA[num2[i]-'0']++;
        if(na<nb) swap(na,nb);
        int maxa=9,maxb=9,maxsum=9;
        int m=0;
        while(na>nb)
        {
            while(cntA[maxa]==0&&maxa>=0) maxa--;
            res[m++]=maxa;
            cntA[maxa]--;
        }
        while(cntB[maxb]==0&&maxb>=0) maxb--;
        if(m==0)
        {
            while(!getNum(maxsum,1)&&maxsum>0)
              maxsum--;
            res[m++]=maxsum;
            na--;
        }
        maxsum=9;
        while(na>0)
        {
            int tmp=getNum(maxsum,0);
            while(!tmp)
            {
                maxsum--;
                tmp=getNum(maxsum,0);
            }
            for(int i=0;i<tmp;++i)
              res[m++]=maxsum;
            na-=tmp;
        }
        int s=0;
        while(res[s]==0&&s+1<m) s++;
        printf("Case #%d: ",tcase);
        for(;s<m;++s) printf("%d",res[s]);
        printf("\n");
    }
    return 0;
}
