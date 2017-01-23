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
const int maxn=500000+10;
struct Node
{
    int x,y;
    Node (){};
    Node (int xx,int yy){x=xx;y=yy;}
};
Node S[maxn],T[maxn];
bool cmp1(Node a,Node b)
{
    return (a.x==b.x&&a.y<b.y)||(a.x<b.x);
}
bool cmp2(Node a,Node b)
{
    return (a.y==b.y&&a.x<b.x)||(a.y<b.y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m1,m2;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        bool flag=true;
        m1=m2=0;
        int xx,yy;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&xx,&yy);
            if(xx<yy) S[m1++]=Node(xx,yy);
            else T[m2++]=Node(xx,yy);
        }
        if(m1!=m2) flag=false;
        else
        {
            sort(S,S+m1,cmp1);
            sort(T,T+m1,cmp2);
            for(int i=0;i<m1;++i)
                if(S[i].x!=T[i].y||S[i].y!=T[i].x)
                {flag=false;break;}
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

