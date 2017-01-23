
 this code is made by qian99
 Problem 1070
 Verdict Accepted
 Submission Date 2014-05-09 222145
 Time 1696 MS
 Memory 14684 KB

#includeiostream
#includecstdio
#includecstring
#includestring
#includealgorithm
#includemap
#includequeue
#includestack
#includecmath
#includevector
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int Size=255;
vectorintfac[maxn];
struct Query
{
    int L,R,X,id;
    Query(){}
    Query(int L,int R,int X,int id)L(L),R(R),X(X),id(id){}
    bool operator (const Query &a) const
    {
        if(LSize!=a.LSize) return La.L;
        return Ra.R;
    }
}querys[maxn];
int a[maxn],cnt[maxn],ans[maxn],n,m;
inline void Add(int x)
{
    cnt[a[x]]++;
}
inline void Dec(int x)
{
    cnt[a[x]]--;
}
void solve()
{
    int l=1,r=0,x;
    for(int i=0;im;++i)
    {
        while(querys[i].Ll) Add(--l);
        while(querys[i].Rr) Dec(r--);
        while(querys[i].Ll) Dec(l++);
        while(querys[i].Rr) Add(++r);
        x=querys[i].X;
        ans[querys[i].id]=0;
        for(int j=0;j(int)fac[x].size();++j)
            ans[querys[i].id]+=cnt[fac[x][j]];
    }
}
int main()
{
    freopen(in.txt,r,stdin);
    freopen(out.txt,w,stdout);
    for(int i=1;imaxn;++i)
        for(int j=i;jmaxn;j+=i)
            fac[j].push_back(i);
    while(~scanf(%d,&n))
    {
        for(int i=1;i=n;++i)
            scanf(%d,&a[i]);
        scanf(%d,&m);
        int L,R,X;
        for(int i=0;im;++i)
        {
            scanf(%d%d%d,&L,&R,&X);
            querys[i]=Query(L,R,X,i);
        }
        memset(cnt,0,sizeof(cnt));
        sort(querys,querys+m);
        solve();
        for(int i=0;im;++i)
            printf(%dn,ans[i]);
    }
    return 0;
}
