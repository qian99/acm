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
const int maxn=200+10;
struct Node
{
    int val,type;
    Node(){}
    Node(int val,int type):val(val),type(type){}
    bool operator <(const Node &a)const
    {
        return (val==a.val&&type<a.type)||(val<a.val);
    }
}node[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int x,y,m=0,cnt=0,ans=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&x,&y);
            if(x>y) swap(x,y);
            if(x%2==0) x--;
            if(y%2==0) y--;
            node[m++]=Node(x,0);
            node[m++]=Node(y,1);
        }
        sort(node,node+m);
        for(int i=0;i<m;++i)
        {
            if(node[i].type==0)
                cnt++;
            else cnt--;
            ans=max(cnt,ans);
        }
        printf("%d\n",ans*10);
    }
    return 0;
}
