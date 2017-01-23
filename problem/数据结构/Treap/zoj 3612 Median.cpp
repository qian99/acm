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
const int maxn=10000+10;
int ch[maxn][2],val[maxn],counts[maxn],r[maxn],size[maxn],tot,root;
void NewNode(int &rt,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    val[rt]=v;
    counts[rt]=size[rt]=1;
    r[rt]=rand();
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+counts[rt];
}
void Rotate(int &rt,int kind)
{
    int y=ch[rt][kind^1];
    ch[rt][kind^1]=ch[y][kind];
    ch[y][kind]=rt;
    PushUp(rt);PushUp(y);
    rt=y;
}
void Insert(int &rt,int v)
{
    if(rt==0)
    {
        NewNode(rt,v);
        return ;
    }
    if(v==val[rt]) counts[rt]++;
    else
    {
        int kind=(v>val[rt]);
        Insert(ch[rt][kind],v);
        if(r[ch[rt][kind]]<r[rt])
            Rotate(rt,kind^1);
    }
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][0]]>=k) return select(ch[rt][0],k);
    if(size[ch[rt][0]]+counts[rt]>=k) return val[rt];
    return select(ch[rt][1],k-(size[ch[rt][0]]+counts[rt]));
}
bool remove(int &rt,int v)
{
    if(rt==0) return false;
    if(val[rt]==v)
    {
        if(counts[rt]>1)
            counts[rt]--;
        else if(!ch[rt][0]&&!ch[rt][1])
        {rt=0;return true;}
        else
        {
            int kind=r[ch[rt][0]]<r[ch[rt][1]];
            Rotate(rt,kind);
            remove(rt,v);
        }
        PushUp(rt);
        return true;
    }
    else
    {
        bool flag=remove(ch[rt][v>val[rt]],v);
        PushUp(rt);
        return flag;
    }
    return true;
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    size[0]=counts[0]=val[0]=0;
    tot=root=0;
    r[0]=(1LL<<31)-1;
}
char str[20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        Init();
        int cnt=0,v;
        while(n--)
        {
            scanf("%s",str);
            scanf("%d",&v);
            if(str[0]=='r')
            {
                if(!remove(root,v))
                    printf("Wrong!\n");
                else
                {
                    cnt--;
                    if(cnt&1)
                        printf("%d\n",select(root,cnt/2+1));
                    else if(cnt!=0)
                    {
                        ll tmp=((ll)select(root,cnt/2)+select(root,cnt/2+1));
                        if(tmp&1) printf("%.1lf\n",tmp/2.0);
                        else printf("%lld\n",tmp/2);
                    }
                    else printf("Empty!\n");
                }
            }
            else
            {
                Insert(root,v);
                cnt++;
                if(cnt&1)
                    printf("%d\n",select(root,cnt/2+1));
                else
                {
                    ll tmp=((ll)select(root,cnt/2)+select(root,cnt/2+1));
                    if(tmp&1) printf("%.1lf\n",tmp/2.0);
                    else printf("%lld\n",tmp/2);
                }
                   // printf("%.1lf\n",(select(root,cnt/2)+select(root,cnt/2+1))/2.0);
            }
        }
    }
    return 0;
}
