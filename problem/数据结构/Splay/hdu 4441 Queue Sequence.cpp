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
const int maxn=300000+10;
int ch[maxn][2],pre[maxn],val[maxn],size[maxn];
int pos[maxn][2],pcnt[maxn][2],tot,root;
ll sum[maxn];
priority_queue<int,vector<int>,greater<int> >q;
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;size[rt]=1;
    val[rt]=sum[rt]=v;
    pcnt[rt][v<0]=1;
    pcnt[rt][v>0]=0;
    pos[abs(v)][v<0]=rt;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    sum[rt]=sum[ch[rt][0]]+sum[ch[rt][1]]+val[rt];
    pcnt[rt][0]=pcnt[ch[rt][0]][0]+pcnt[ch[rt][1]][0]+(val[rt]>0);
    pcnt[rt][1]=pcnt[ch[rt][0]][1]+pcnt[ch[rt][1]][1]+(val[rt]<0);
}

void traval(int x)
{
    if(x)
    {
        traval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父节点 %2d size=%2d ,val=%2d\n",x,ch[x][0],ch[x][1],pre[x],size[x],val[x]);
        traval(ch[x][1]);
    }
}
void Debug()
{
    printf("%d\n",root);
    traval(root);
}

void Rotate(int x,int kind)
{
    int y=pre[x];
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    PushUp(y);
}
void Splay(int rt,int goal)
{
    while(pre[rt]!=goal)
    {
        int y=pre[rt];
        if(pre[y]==goal)
            Rotate(rt,ch[y][0]==rt);
        else
        {
            int kind=ch[pre[y]][0]==y;
            if(ch[y][kind]==rt)
            {
                Rotate(rt,kind^1);
                Rotate(rt,kind);
            }
            else
            {
                Rotate(y,kind);
                Rotate(rt,kind);
            }
        }
    }
    PushUp(rt);
    if(goal==0) root=rt;
}
void RotateTo(int k,int goal)
{
    int rt=root;
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
    }
    Splay(rt,goal);
}
void Insert(int k,int v)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    NewNode(ch[ch[root][1]][0],ch[root][1],v);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Del(int rt)
{
    Splay(rt,0);
    if(!ch[rt][0])
    {
        root=ch[rt][1];
        pre[root]=0;
        return ;
    }
    int rp=ch[rt][0];
    while(ch[rp][1]) rp=ch[rp][1];
    Splay(rp,root);
    ch[rp][1]=ch[rt][1];
    pre[ch[rt][1]]=rp;
    pre[rp]=0;
    root=rp;
    PushUp(root);
}
ll Query(int L,int R)
{
    Splay(L,0);
    Splay(R,root);
    return sum[ch[ch[root][1]][0]];
}
int Find(int p)
{
    RotateTo(p+1,0);
    int k=pcnt[ch[root][0]][0];
    int rt=root;
    while(true)
    {
        if(pcnt[ch[rt][0]][1]>=k)
            rt=ch[rt][0];
        else if(pcnt[ch[rt][0]][1]+(val[rt]<0)==k)
            break;
        else
        {
            k-=pcnt[ch[rt][0]][1]+(val[rt]<0);
            rt=ch[rt][1];
        }
    }
    Splay(rt,0);
    return size[ch[root][0]]-1;
}
void Init()
{
    pre[0]=ch[0][0]=ch[0][1]=0;
    size[0]=sum[0]=pcnt[0][0]=pcnt[0][1]=0;
    tot=root=0;
    NewNode(root,0,1);
    NewNode(ch[root][1],root,-1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("hack.out","w",stdout);
    int n,x,tcase=0;
    char str[15];
    while(~scanf("%d",&n))
    {
        printf("Case #%d:\n",++tcase);
        Init();
        while(!q.empty()) q.pop();
        int now=1;
//        Debug();
        while(n--)
        {
            scanf("%s%d",str,&x);
            if(str[0]=='i')
            {
                if(q.empty()) q.push(now++);
                int v=q.top();
                q.pop();
                Insert(x,v);
//                Debug();
                int ps=Find(x);
                Insert(ps,-v);
            }
            else if(str[0]=='r')
            {
                int a=pos[x][0];
                Del(a);
                a=pos[x][1];
                Del(a);
                q.push(x);
            }
            else
            {
                int L=pos[x][0],R=pos[x][1];
                printf("%I64d\n",Query(L,R));
            }
//            Debug();
        }
    }
    return 0;
}
