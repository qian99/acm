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
const int maxn=20+10;
struct Node
{
    int pos,val,sp;
}node[maxn];
bool solve(Node a,Node b)
{
    int L=a.pos,R=a.pos+a.sp;
    int x=b.pos,y=b.pos+b.sp;
    if(L>=0&&R<1000)
    {
        if(x>=0&&y>=0) return (x>=L&&x<=R)||(y>=L&&y<=R)||(x<R&&y>L)||(x>R&&y<L);
        else
        {
            y=(y+1000)%1000;
            return (L>=0&&L<=x)||(R<=999&&R>=y);//(L>=0&&R<=x)||(R<=999&&L>=y)||
        }
    }
    else
    {
        if(y<0) return true;
        R=R%1000;
        return (y>=0&&y<=R)||(x>=L&&x<=999);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,T;
    scanf("%d%d",&n,&T);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&node[i].pos);
        node[i].val=0;
    }
    for(int i=0;i<n;++i)
        scanf("%d",&node[i].sp);
    while(T--)
    {
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(i==j||node[i].sp*node[j].sp>0) continue;
                bool flag;
                if(node[i].sp>0) flag=solve(node[i],node[j]);
                else flag=solve(node[j],node[i]);
                if(flag) node[i].val++;
            }
        }
        for(int i=0;i<n;++i)
          node[i].pos=(node[i].pos+node[i].sp+1000)%1000;
        if(T==0) break;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            if(i!=j)
            {
                if(node[i].sp*node[j].sp<0&&node[i].pos==node[j].pos)
                    node[i].val--;
            }
    }
    for(int i=0;i<n;++i)
    {
        if(i) printf(" ");
        printf("%d",node[i].val);
    }
    printf("\n");
    return 0;
}

