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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
double p[7],px[6][6][6][6][6];
bool vis[6][6][6][6][6];
int pt[6][6][6][6][6][14];
double dp[1<<14];
void cal(int aa[5],double P)
{
    int a[5],b[6],sum=0;
    for(int i=0;i<5;++i) a[i]=aa[i],sum+=a[i]+1;
    sort(a,a+5);
    memset(b,0,sizeof(b));
    if(vis[a[0]][a[1]][a[2]][a[3]][a[4]])
    {
        px[a[0]][a[1]][a[2]][a[3]][a[4]]+=P;
        return ;
    }
    vis[a[0]][a[1]][a[2]][a[3]][a[4]]=true;
    px[a[0]][a[1]][a[2]][a[3]][a[4]]=P;
    int* val=pt[a[0]][a[1]][a[2]][a[3]][a[4]];
    memset(pt[a[0]][a[1]][a[2]][a[3]][a[4]],0,sizeof(pt[a[0]][a[1]][a[2]][a[3]][a[4]]));
//    memset(val,0,sizeof(int)*14);
    for(int i=0;i<5;++i) b[a[i]]++;
    for(int i=0;i<5;++i) val[a[i]]+=a[i]+1;
//        val[i]=(i+1)*b[i];
    //Small Straigh
    bool flag=true;
    for(int i=0;i<4;++i) if(!b[i]) flag=false;
    if(flag) val[10]=30;
    flag=true;
    for(int i=1;i<5;++i) if(!b[i]) flag=false;
    if(flag) val[10]=30;
    flag=true;
    for(int i=2;i<6;++i) if(!b[i]) flag=false;
    if(flag) val[10]=30;
    //Large Straight
    flag=true;
    for(int i=0;i<5;++i) if(!b[i]) flag=false;
    if(flag) val[11]=40;
    flag=true;
    for(int i=1;i<6;++i) if(!b[i]) flag=false;
    if(flag) val[11]=40;
    //
    sort(b,b+6);
    reverse(b,b+6);
    //Two-Pairs
    if(b[0]>=2&&b[1]>=2) val[6]=sum;
    //Three-Of-A-Kind
    if(b[0]>=3) val[7]=sum;
    //Four-Of-A-Kind
    if(b[0]>=4) val[8]=sum;
    //Full House
    if(b[0]==3&&b[1]==2) val[9]=25;
    //Yahtzee
    if(b[0]==5) val[12]=50;
    //Chance
    val[13]=sum;
    return ;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        for(int i=0;i<6;++i)
            scanf("%lf",&p[i]);
        memset(vis,0,sizeof(vis));
        int a[5];
        for(a[0]=0;a[0]<6;a[0]++)
        for(a[1]=0;a[1]<6;a[1]++)
        for(a[2]=0;a[2]<6;a[2]++)
        for(a[3]=0;a[3]<6;a[3]++)
        for(a[4]=0;a[4]<6;a[4]++)
        {
            double tp=1;
            for(int i=0;i<5;++i)
                tp*=p[a[i]];
            cal(a,tp);
        }
//        cout<<px[][][][][]
//        for(int i=0;i<14;++i)
//            cout<<pt[0][0][0][0][0][i]<<endl;
        dp[(1<<14)-1]=0.0;
        double tmp;
        for(int i=(1<<14)-2;i>=0;--i)
        {
            dp[i]=0.0;
            for(int a=0;a<6;++a)
            for(int b=a;b<6;++b)
            for(int c=b;c<6;++c)
            for(int d=c;d<6;++d)
            for(int e=d;e<6;++e)
            {
                tmp=0;
                for(int j=0;j<14;++j)
                    if((i&(1<<j))==0)
                        tmp=max(tmp,dp[i|(1<<j)]+pt[a][b][c][d][e][j]);
//                if(px[a][b][c][d][e]!=0)
                dp[i]+=tmp*px[a][b][c][d][e];
            }
        }
        printf("Case #%d: %.6lf\n",tcase,dp[0]);
    }
    return 0;
}
