#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)

using namespace std;
const int maxn=10000+10;
struct Students
{
    string Name;
    double point;
};
Students student[555];
int flag[maxn];
int problems[maxn];
string ff[5];
const int ffpts[5]={0,36,27,18};
void primes()
{
    memset(flag,0,sizeof(flag));
    for(int i=2;i<=maxn;++i)
    {
        if(!flag[i])
        {
            int j=2;
            while(i*j<=maxn)
            {
                flag[i*j]=true;
                j++;
            }
        }
    }
}
bool cmp(Students a,Students b)
{
    if(a.point==b.point) return a.Name<b.Name;
    return a.point>b.point;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","r",stdout);
    int t;
    primes();
    cin>>t;
    while(t--)
    {
         map<string,int>mp;
        int n,m,R,S,Q,P,C;
        string str1,str2,str3;
        memset(problems,0xff,sizeof(problems));
        cin>>n>>m;
        cin>>R;
        int temp;
        for(int i=0;i<R;++i)
        {
            cin>>temp;
            problems[temp]=1;
        }
        cin>>S;
        for(int i=0;i<S;++i)
        {
            cin>>temp;
            problems[temp]=0;
        }
        cin>>Q;
        string ff[5];
        for(int i=0;i<Q;++i)
        {
            cin>>str1>>temp;
            if(temp==1) mp[str1]=36;
            if(temp==2) mp[str1]=27;
            if(temp==3) mp[str1]=18;
        }
        double pts;
        int as[3];
        for(int i=0;i<n;++i)
        {
            cin>>str1>>str2>>str3;
            //cout<<str1<<str2<<str3<<endl;
            cin>>P>>C;
            //cout<<P<<C<<endl;
            pts=0;
            student[i].Name=str1;
            if(str3=="F") pts+=33;
            for(int j=0;j<P;++j)
            {
                cin>>temp;
                //cout<<temp<<" ";
                //if(!flag[temp]) {pts+=1;continue;}
                if(problems[temp]==1) pts+=2.5;
                else if(problems[temp]==0) pts+=1.5;
                else if(!flag[temp]) pts+=1;
                else pts+=0.3;
            }
            as[0]=as[1]=as[2]=0;
            for(int k=0;k<C;++k)
            {
                cin>>temp;
                if(temp>as[0])
                {
                    as[0]=temp;
                    sort(as,as+3);
                }
            }
            if(C>=3)
            {
                double u=(double)(as[0]-1200)/100*1.5;
                pts+=max(0.0,u);
            }
            pts+=mp[str2];
            student[i].point=pts;
        }
        sort(student,student+n,cmp);
        for(int i=0;i<m;++i)
        {
            cout<<student[i].Name<<" ";
            printf("%.3lf\n",student[i].point);
        }
    }
    return 0;
}
