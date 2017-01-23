#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;

int min(int a,int b);
int max(int a,int b);
const int maxn=100000+10;
struct Anum
{
    int x,t;
    bool operator < (const Anum &a)const
    {
        return a.t>t;
    }
};
int num[maxn];
int r[maxn];
int main()
{
    int n,m;
    while(~scanf("%d",&n))
    {
        priority_queue<Anum>q;
        memset(num,0,sizeof(num));
        for(int i=0;i<n;++i)
        {
            scanf("%d",&num[i]);
        }
        sort(num,num+n);
        int p=1;
        Anum temp;
        for(int i=1;i<=n;++i)
        {
            if(num[i]==num[i-1])
            {
                p++;
            }
            else
            {
                temp.t=p;
                temp.x=num[i-1];
                q.push(temp);
                p=1;
            }
        }
        Anum s[3];
        int m=0;
        while(q.size()>=3)
        {
            for(int i=0;i<3;++i)
            {
                s[i]=q.top();
                r[m++]=s[i].x;
                s[i].t--;
                q.pop();
            }
            sort(r+m-3,r+m);
            for(int i=0;i<3;++i)
            {
                if(s[i].t>0)
                {
                    q.push(s[i]);
                }
            }
        }
        m/=3;
        printf("%d\n",m);
        for(int i=0;i<m;++i)
        {
            printf("%d %d %d\n",r[i*3+2],r[i*3+1],r[i*3]);
        }
    }
    return 0;
}
int min(int a,int b)
{
    return a<b?a:b;
}
int max(int a,int b)
{
    return a>b?a:b;
}
