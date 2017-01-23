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
const int maxn=1000000+100;
int a[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(a,0,sizeof(a));
    int cnt=0;
    while(n>0&&m>0)
    {
        if(cnt&1) a[cnt++]=1,m--;
        else a[cnt++]=0,n--;
    }
    if(n==1&&a[cnt-1]==1)
    {
        a[cnt++]=0;
        for(int i=0;i<cnt;++i)
            printf("%d",a[i]);
        printf("\n");
    }
    else if(n>0)
    {
        printf("-1\n");
    }
    else
    {
        for(int i=1;i<cnt&&m>0;i+=2)
        {
            a[i]++;m--;
        }
        int adt=2+(a[cnt-1]==0?2:0);
        if(adt<m)
        {
            printf("-1\n");
        }
        else
        {
            if(m==1) {printf("1");m=0;}
            else if(m!=0){printf("11");m-=2;}
            for(int i=0;i<cnt;++i)
            {
                if(a[i]==0) printf("0");
                else if(a[i]==1) printf("1");
                else printf("11");
            }
            if(m!=0)
            {
                if(m==1) printf("1");
                else if(m==2) printf("11");
            }
            printf("\n");
        }
    }
    return 0;
}