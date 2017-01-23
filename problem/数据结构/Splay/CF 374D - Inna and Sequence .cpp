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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000+10;
int ch[maxn][2],val[maxn],pre[maxn],size[maxn],root,tot;
int a[maxn];
void NewNode(int & rt,int fa,int v)
{
    rt = ++tot;
    ch[rt][0] = ch[rt][1] = 0;
    pre[rt] = fa;
    size[rt] = 1;
    val[rt] = v;
}
inline void PushUp(int rt)
{
    size[rt] = size[ch[rt][0]] + size[ch[rt][1]] + 1;
}
void Rotate(int x,int kind)
{
    int y = pre[x];
    ch[y][kind^1] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    PushUp(y);
}
void Splay(int rt,int goal)
{
    while(pre[rt] != goal)
    {
        int y = pre[rt];
        if(pre[y] == goal)
            Rotate(rt,ch[y][0]==rt);
        else
        {
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == rt)
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
    if(goal == 0) root = rt;
}
void RotateTo(int k,int goal)
{
    int rt = root;
    while(size[ch[rt][0]] != k)
    {
        if(size[ch[rt][0]] > k)
            rt = ch[rt][0];
        else
        {
            k -= (size[ch[rt][0]] + 1);
            rt = ch[rt][1];
        }
    }
    Splay(rt,goal);
}
void Insert(int k,int v)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    int rt = ch[root][1];
    NewNode(ch[rt][0],rt,v);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Remove(int k)
{
    RotateTo(k-1,0);
    RotateTo(k+1,root);
    ch[ch[root][1]][0] = 0;
    PushUp(ch[root][1]);
    PushUp(root);
}
void build()
{
    ch[0][0] = ch[0][1] = 0;
    size[0] = val[0] = pre[0] = 0;
    root = tot = 0;
    NewNode(root,0,-1);
    NewNode(ch[root][1],root,-1);
    PushUp(ch[root][1]);
    PushUp(root);
}
void travel(int rt)
{
    if(rt == 0) return ;
    travel(ch[rt][0]);
    if(val[rt] != -1)
        printf("%d",val[rt]);
    travel(ch[rt][1]);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,cnt = 0;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < m;++i)
        scanf("%d",&a[i]);
    build();
    int type;
    while(n--)
    {
        scanf("%d",&type);
        if(type == 0 || type == 1)
        {
            Insert(cnt,type);
            cnt++;
        }
        else
        {
            if(cnt == 0) continue;
            if(a[0] > cnt) continue;
            int pos = upper_bound(a,a+m,cnt) - a;
            pos--;
            for(int i = pos;i >= 0;--i)
            {
                Remove(a[i]);
                cnt--;
            }
        }
//        Debug();
    }
    if(cnt == 0) printf("Poor stack!");
    else travel(root);
    puts("");
    return 0;
}
