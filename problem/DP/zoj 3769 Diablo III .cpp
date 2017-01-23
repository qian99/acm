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
const char equip[15][20]={"Head", "Shoulder", "Neck", "Torso", "Hand", "Wrist", "Waist", "Legs", "Feet","~x _ x~", "Two-Handed", "Shield", "Weapon", "Finger"};
const int maxn=300+10;
const int maxm=50000+10;
int dp[15][maxm];
struct Node
{
    int D,T;
    Node(){}
    Node(int D,int T):D(D),T(T){}
};
vector<Node>vt[15];
char str[20];
inline int getid(char *s)
{
    for(int i=0;i<14;++i)
        if(strcmp(s,equip[i])==0) return i;
    return -1;
}
void solve(int n,int m)
{
    memset(dp,0xff,sizeof(dp));
    for(int i=0;i<14;++i) vt[i].clear();
    int D,T,id,size,size2;
    bool flag;
    for(int i=0;i<n;++i)
    {
        scanf("%s %d %d",str,&D,&T);
        id=getid(str);
        size=vt[id].size();
        flag=true;
        if(id<9)
        for(int j=0;j<size;++j)
        {
            if(vt[id][j].D>D&&vt[id][j].T>T) {flag=false;break;}
            if(vt[id][j].D<D&&vt[id][j].T<T)
            {
                flag=false;
                vt[id][j]=Node(D,T);
                break;
            }
        }
        if(flag) vt[id].push_back(Node(D,T));
    }
    size=vt[13].size();
    if(size==1) vt[9].push_back(vt[13][0]);
    else
    {
        for(int i=0;i<size;++i)
            for(int j=i+1;j<size;++j)
            {
                D=vt[13][i].D+vt[13][j].D;
                T=vt[13][i].T+vt[13][j].T;
                size2=vt[9].size();
                flag=true;
                for(int k=0;k<size2;++k)
                {
                    if(vt[9][k].D>D&&vt[9][k].T>T) {flag=false;break;}
                    if(vt[9][k].D<D&&vt[9][k].T<T)
                    {
                        flag=false;
                        vt[9][k]=Node(D,T);
                        break;
                    }
                }
                if(flag) vt[9].push_back(Node(D,T));
            }
    }
    size=vt[11].size();size2=vt[12].size();
    for(int i=0;i<size;++i) vt[10].push_back(vt[11][i]);
    for(int j=0;j<size2;++j) vt[10].push_back(vt[12][j]);
    for(int i=0;i<size;++i)
        for(int j=0;j<size2;++j)
            vt[10].push_back(Node(vt[11][i].D+vt[12][j].D,vt[11][i].T+vt[12][j].T));
    dp[0][0]=0;
    size=vt[10].size();
    for(int i=0;i<size;++i)
    {
        D=vt[10][i].D;
        T=vt[10][i].T;
        if(T>=m) T=m;
        dp[0][T]=max(dp[0][T],D);
    }
    for(int i=1;i<=10;++i)
    {
        size=vt[i-1].size();
        for(int j=0;j<=m;++j)
        {
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
            if(dp[i-1][j]==-1) continue;
//            dp[i][j]=max(dp[i][j],dp[i-1][j]);
            for(int k=0;k<size;++k)
            {
                D=vt[i-1][k].D;
                T=vt[i-1][k].T;
                if(j+T>m) T-=((j+T)-m);
                dp[i][j+T]=max(dp[i][j+T],dp[i-1][j]+D);
            }
        }
    }
    printf("%d\n",dp[10][m]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        solve(n,m);
    }
    return 0;
}
