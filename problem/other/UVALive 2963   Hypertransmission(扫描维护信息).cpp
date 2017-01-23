#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
struct Point
{
    double x,y,z;
    int type;
    void readit()
    {
        scanf("%lf%lf%lf%d",&x,&y,&z,&type);
    }
}p[maxn];
struct Node
{
    double R;
    int u,v;
    Node (){};
    Node (double r,int uu,int vv) {R=r;u=uu;v=vv;}
    bool operator <(const Node &a) const
    {
        return R<a.R;
    }
}node[maxn*maxn];
int cnt[maxn];
double Len(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
            p[i].readit();
        int m=0;
        for(int i=0;i<n;++i)
           for(int j=i+1;j<n;++j)
            node[m++]=Node(Len(p[i],p[j]),i,j);
        sort(node,node+m);
        for(int i=0;i<n;++i) cnt[i]=1;
        int maxval=0;
        double mxr=0;
        int tmp=0,u,v;
        for(int i=0;i<m;++i)
        {
            int k=i;
            while(i<m&&dcmp(node[i].R-node[k].R)==0)
            {
                u=node[i].u;
                v=node[i].v;
                if(p[u].type==p[v].type)
                {
                    if(cnt[u]==-1) tmp--;
                    if(cnt[v]==-1) tmp--;
                    cnt[u]++;cnt[v]++;
                }
                else
                {
                    if(cnt[u]==0) tmp++;
                    if(cnt[v]==0) tmp++;
                    cnt[u]--;cnt[v]--;
                }
                i++;
            }
            i--;
            if(tmp>=maxval)
            {
                if(tmp==maxval) mxr=min(mxr,node[k].R);
                else mxr=node[k].R;
                maxval=tmp;
            }
        }
        printf("%d\n",maxval);
        printf("%.4lf\n",mxr);
    }
    return 0;
}

