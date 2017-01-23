/*
* this code is made by qian99
* Problem: 1073
* Verdict: Accepted
* Submission Date: 2014-05-09 22:58:53
* Time: 60 MS
* Memory: 1684 KB
*/
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
const int maxn=1000+10;
int a[maxn],n;
int Finds(int val)
{
    int res=-1;
    if(n>0) res=n-1;
    for(int i=n-1;i>=0;--i)
    {
        if(a[i]>=val) res=i;
        else break;
    }
    if(res!=-1)
    {
        int tmp=a[res];
        for(int i=res;i<n;++i)
            a[i]=a[i+1];
        res=tmp;
        n--;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        int A,B,C,D;
        scanf("%d%d%d%d",&A,&B,&C,&D);
        for(int i=0;i<n;++i)
            scanf("%d",&a[i]);
        bool flag=true;
        sort(a,a+n);
        while(A>0&&flag)
        {
            int tmp=Finds(A);
            if(tmp==-1) flag=false;
            else A=max(0,A-tmp);
        }
        while(B>0&&flag)
        {
            int tmp=Finds(B);
            if(tmp==-1) flag=false;
            else B=max(0,B-tmp);
        }
        while(C>0&&flag)
        {
            int tmp=Finds(C);
            if(tmp==-1) flag=false;
            else C=max(0,C-tmp);
        }
        while(D>0&&flag)
        {
            int tmp=Finds(D);
            if(tmp==-1) flag=false;
            else D=max(0,D-tmp);
        }
        if(flag)
        {
            printf("YES ");
            int sum=0;
            for(int i=0;i<n;++i) sum+=a[i];
            printf("%d\n",sum);
        }
        else printf("NO\n");
    }
    return 0;
}
