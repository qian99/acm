#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2097151;
struct HashTable
{
    int val,cnt,next;
    HashTable(){}
    HashTable(int val,int cnt,int next):val(val),cnt(cnt),next(next){}
}hash[maxn<<2];
bool vis[maxn+10];
int tot;
int Insert(int x)
{
    int v=x&maxn;
    if(!vis[v])
    {
        vis[v]=true;
        hash[v]=HashTable(x,1,-1);
        return 1;
    }
    int p=v;
    while(hash[p].next!=-1)
    {
        if(hash[p].val==x)
        {
            hash[p].cnt++;
            return hash[p].cnt;
        }
        p=hash[p].next;
    }
    if(hash[p].val==x)
    {
        hash[p].cnt++;
        return hash[p].cnt;
    }
    hash[p].next=++tot;
    hash[tot]=HashTable(x,1,-1);
    return 1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(vis,0,sizeof(vis));
        tot=maxn;
        int m=(n+1)/2,val,res;
        bool flag=false;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&val);
            if(flag) continue;
            if(Insert(val)>=m) flag=true,res=val;
        }
        printf("%d\n",res);
    }
    return 0;
}
