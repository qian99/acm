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
const int maxn=100+10;
struct Node
{
    int hp,cards[maxn],tot;
    bool canmove;
    void Init()
    {
        hp=3;tot=0;
    }
    void ajust()
    {
        int cnt=0;
        for(int i=0;i<tot;++i)
            if(cards[i]!=-1) cards[cnt++]=cards[i];
        tot=cnt;
    }
    void getone(int v)
    {
        cards[tot++]=v;
    }
    bool Play(Node & op)
    {
        canmove=false;
        for(int i=0;i<tot;++i)
            if(cards[i]==2)
            {
                for(int j=0;j<op.tot;++j)
                    if(op.cards[j]==3)
                    {
                        cards[i]=op.cards[j]=-1;
                        canmove=true;
                        break;
                    }
                if(cards[i]==-1) continue;
                for(int j=0;j<op.tot;++j)
                    if(op.cards[j]!=-1)
                    {
                        cards[tot++]=op.cards[j];
                        cards[i]=op.cards[j]=-1;
                        canmove=true;
                        break;
                    }
            }
        ajust();
        op.ajust();
        for(int i=0;i<tot;++i)
            if(cards[i]==0)
            {
                for(int j=0;j<op.tot;++j)
                    if(op.cards[j]==1)
                    {
                        cards[i]=op.cards[j]=-1;
                        canmove=true;
                        break;
                    }
                if(cards[i]==-1) break;
                canmove=true;
                op.hp--;
                cards[i]=-1;
                ajust();
                op.ajust();
                if(op.hp<=0) return true;
                break;
            }
        return false;
    }
}player[2];
int Card[maxn];
char str[10];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            if(str[0]=='K') Card[i]=0;
            else if(str[0]=='E') Card[i]=1;
            else if(str[0]=='S') Card[i]=2;
            else Card[i]=3;
        }
        player[0].Init();
        player[1].Init();
        int res=-1,now=0,turns=0;
        for(int i=0;i<4;++i)
            player[0].getone(Card[++now]);
        for(int i=0;i<4;++i)
            player[1].getone(Card[++now]);
        while(now!=n)
        {
            int tmp=min(2,n-now);
            for(int i=1;i<=tmp;++i)
                player[turns].getone(Card[now+i]);
            now+=tmp;
            if(player[turns].Play(player[turns^1]))
            {
                res=turns;
                break;
            }
            turns^=1;
        }
        if(res==-1)
        {
            while(true)
            {
                int a=player[turns].Play(player[turns^1]);
                int b=player[turns^1].Play(player[turns]);
                if(a)
                {
                    res=turns;
                    break;
                }
                else if(b)
                {
                    res=turns^1;
                    break;
                }
                else if((!player[turns].canmove)&&
                        (!player[turns^1].canmove))
                        break;
            }
        }
        printf("Case %d: ",++tcase);
        if(res==-1) printf("Just a tie.\n");
        else if(res==0) printf("The winner is the first.\n");
        else printf("The winner is the second.\n");
    }
    return 0;
}
