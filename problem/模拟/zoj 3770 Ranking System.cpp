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
const int maxn=2000+10;
struct Date
{
    int year,month,day;
    bool operator <(const Date & a) const
    {
        if(year!=a.year) return year<a.year;
        if(month!=month) return month<a.month;
        return day<a.day;
    }
    bool operator ==(const Date &a) const
    {
        return year==a.year&&month==a.month&&day==a.day;
    }
};
struct Node
{
    int id,score,num,lev;
    Date date;
    void read()
    {
        scanf("%d",&id);
        scanf("%d/%d/%d",&date.year,&date.month,&date.day);
        scanf("%d",&score);
    }
    bool operator <(const Node &a) const
    {
        if(score!=a.score) return score>a.score;
        if(!(date==a.date)) return date<a.date;
        return id<a.id;
    }
}node[maxn];
bool cmp(Node a,Node b)
{
    return a.num<b.num;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int cnt=0;
        for(int i=0;i<n;++i)
        {
            node[i].read();
            node[i].num=i;
            if(node[i].score>0) cnt++;
        }
        sort(node,node+n);
        int tot=0.03*cnt;
        int j=0,k;
        for(;j<tot;++j)
            node[j].lev=6;
        tot=0.07*cnt;
        k=j+tot;
        for(;j<k;++j)
            node[j].lev=5;
        tot=0.2*cnt;
        k=j+tot;
        for(;j<k;++j)
            node[j].lev=4;
        tot=0.3*cnt;
        k=j+tot;
        for(;j<k;++j)
            node[j].lev=3;
        for(;j<n;++j)
            if(node[j].score>0) node[j].lev=2;
            else node[j].lev=1;
        sort(node,node+n,cmp);
        for(int i=0;i<n;++i)
            printf("LV%d\n",node[i].lev);
    }
    return 0;
}

