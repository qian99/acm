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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=4000+10;
const int MAXN=33554431;
int A[maxn],B[maxn],C[maxn],D[maxn];
int num[maxn*maxn];
struct Node
{
    int val,cnt,next;
    Node(int val=0,int cnt=0,int next=0):val(val),cnt(cnt),next(next){}
};
struct HashTable
{
    Node hash[MAXN<<1];
    bool vis[MAXN+10];
    int tot;
    void Init()
    {
        memset(vis,0,sizeof(vis));
        tot=MAXN;
    }
    bool Insert(int v)
    {
        int p=v&MAXN;
        if(!vis[p])
        {
            vis[p]=true;
            hash[p]=Node(v,1,-1);
            return true;
        }
        while(hash[p].next!=-1)
        {
            if(hash[p].val==v)
            {
                hash[p].cnt++;
                return false;
            }
            p=hash[p].next;
        }
        if(hash[p].val==v) {hash[p].cnt++;return false;}
        hash[p].next=++tot;
        hash[tot]=Node(v,1,-1);
        return true;
    }
    int Find(int v)
    {
        int p=v&MAXN;
        if(!vis[p]) return -1;
        while(p!=-1)
        {
            if(hash[p].val==v) return hash[p].cnt;
            p=hash[p].next;
        }
        return -1;
    }
}ha,hb;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    for(int tcase=0;tcase<t;++tcase)
    {
        if(tcase) puts("");
        scanf("%d",&n);
        ha.Init();
        hb.Init();
        for(int i=0;i<n;++i)
            scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
        int tot=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
            {
                if(ha.Insert(A[i]+B[j]))
                    num[tot++]=A[i]+B[j];
            }
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                hb.Insert(C[i]+D[j]);
        ll sum=0,x,y;
        for(int i=0;i<tot;++i)
        {
            x=ha.Find(num[i]);
            y=hb.Find(-num[i]);
            if(y!=-1) sum+=x*y;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
