#include <iostream>
#include<memory.h>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=500001;
int sz,ans,tree[500001][26],val[500001],f[500001],last[500001];
char s[51];
bool flag[maxn];
void init()
{
    sz=1;
    memset(tree[0],0,sizeof(tree[0]));
    memset(val,0,sizeof(val));
    memset(flag,0,sizeof(flag));
}
void insert(char *s,int rank)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;i++)
    {
        int c=s[i]-'a';
        if(!tree[u][c]){
           memset(tree[sz],0,sizeof(tree[sz]));
           val[sz]=0;
           tree[u][c]=sz++;
        }
        u=tree[u][c];
    }
    val[u]+=rank;
}
void getFail()
{
    queue<int>q;
    f[0]=0;
    for(int c=0;c<26;c++)
    {
        int u=tree[0][c];
        if(u) {f[u]=0;q.push(u);last[u]=0;}
    }
    while(!q.empty())
    {
        int r=q.front();
        q.pop();
        for(int c=0;c<26;c++)
        {
            int u=tree[r][c];
            if(!u) continue;
            q.push(u);
            int v=f[r];
            while(v&&!tree[v][c]) v=f[v];
            f[u]=tree[v][c];
            last[u]=val[f[u]]?f[u]:last[f[u]];
        }
    }
}
void print(int j)
{
    if(j) {
       if(!flag[j])
       {
           flag[j]=1;
           ans+=val[j];
       }
       print(last[j]);
    }

}
void find(char *T)
{
    int n=strlen(T);
    int j=0;
    for(int i=0;i<n;i++){
       int c=T[i]-'a';
       while(j&&!tree[j][c]) j=f[j];
       j=tree[j][c];
       if(val[j]) print(j);
       else if(last[j]) print(last[j]);
    }
}
char str[1000001];
int main()
{
    //freopen("in.txt.txt","r",stdin);
    int t,n;
    //string str;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s);
            insert(s,1);
        }
        getFail();
        scanf("%s",str);
        find(str);
        printf("%d\n",ans);
    }
    return 0;
}
