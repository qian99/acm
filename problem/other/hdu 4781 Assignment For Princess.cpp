#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn=100;
const int maxm=1000;
struct Edge
{
	int u,v;
};
Edge edges[maxm];
bool vis[maxm];
int flag[maxn][maxn];
int n,m;
inline int add(int x)
{
	x++;
	if(x==n+1) x=1;
	return x;
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
	    scanf("%d%d",&n,&m);
		memset(vis,0,sizeof(vis));
		memset(flag,0xff,sizeof(flag));
		int cnt=0;
		int u,v,i,j;
		for(i=1;i<=n;i+=3)
		{
			if(n-i+1>=2)
			{
				int p=min(n-i+1,3);
				for(j=0;j<p;++j)
				{
					cnt++;
					u=edges[cnt].u=i+j;
					v=edges[cnt].v=i+j+1;
					if(v==n+1) v=edges[cnt].v=1;
					vis[cnt]=true;
					flag[u][v]=flag[v][u]=cnt%3;
				}
			}
			else
			{
				u=edges[cnt+3].u=n;
				v=edges[cnt+3].v=1;
				vis[cnt+3]=true;
				flag[u][v]=flag[v][u]=(cnt+3)%3;
			}
		}
		int sz=1,sp=1,tz=3,tp=5,ps=1;
		int tmp;
		for(i=cnt+1;i<=m;++i)
		{
			if(vis[i]) continue;
			if(i%3==0)
			{
				edges[i].u=sz;
				edges[i].v=tz;
				vis[i]=true;
				flag[sz][tz]=flag[tz][sz]=i%3;
				tmp=0;
				while(true)
				{
					if(add(add(tz))==sz)
					{
						sz=add(sz);
						tz=add(sz);
						tmp=flag[sz][tz];
						tmp+=flag[tz][add(tz)];
						tmp%=3;
						tz=add(tz);
						if(tmp==0&&flag[sz][tz]==-1)
						{
							break;
						}
						continue;
					}
					tmp+=flag[tz][add(tz)];
					tmp%=3;
					tz=add(tz);
					if(tmp==0&&flag[sz][tz]==-1)
						break;
				}
			}
			else
			{
				if((i%3)==ps)
				{
					edges[i].u=sp;
					edges[i].v=tp;
				}
				else
				{
					edges[i].u=tp;
					edges[i].v=sp;
				}
				vis[i]=true;
				flag[sp][tp]=flag[tp][sp]=i%3;
				tmp=ps;
				while(true)
				{
					if(add(add(tp))==sp)
					{
						sp=add(sp);
						tp=add(sp);
						tmp=flag[sp][tp];
						tmp+=flag[tp][add(tp)];
						tmp%=3;
						tp=add(tp);
						if(tmp!=0&&flag[sp][tp]==-1)
						{
							ps=tmp;
							break;
						}
						continue;
					}
					tmp+=flag[tp][add(tp)];
					tmp%=3;
					tp=add(tp);
					if(tmp!=0&&flag[sp][tp]==-1)
					{
						ps=tmp;
						break;
					}
				}
			}
		}
		printf("Case #%d:\n",tcase);
		for(i=1;i<=m;++i)
		{
			printf("%d %d %d\n",edges[i].u,edges[i].v,i);
		}
	}
    return 0;
}
