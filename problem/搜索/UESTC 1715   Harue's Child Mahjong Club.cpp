#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<queue>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
const string title[35]={"1N","2N","3N","4N","5N","6N","7N","8N","9N",
                        "1S","2S","3S","4S","5S","6S","7S","8S","9S",
                        "1B","2B","3B","4B","5B","6B","7B","8B","9B",
                        "EH","SH","WH","NH","rH","wH","gH"};
int Tp[50],Ap[50],Mp[50],Hp[50];
void readit(int *a,int n)
{
    string str;
    for(int i=0;i<n;++i)
    {
        cin>>str;
        for(int j=0;j<34;++j)
        {
            if(str==title[j])
            {
                a[j]++;
                break;
            }
        }
    }
}
bool dfs(int *a,int step)
{
    for(int i=0;i<34;++i)
    {
        if(a[i]>=3)
        {
            a[i]-=3;
            if(step+3==14) return true;
            if(dfs(a,step+3)) return true;
            a[i]+=3;
        }
    }
    for(int i=0;i<27;++i)
    {
        if(i%9<=6&&a[i]>=1&&a[i+1]>=1&&a[i+2]>=1)
        {
            a[i]--;a[i+1]--;a[i+2]--;
            if(step+3==14) return true;
            if(dfs(a,step+3)) return true;
            a[i]++;a[i+1]++;a[i+2]++;
        }
    }
    return false;
}
bool check(int *a)
{
    for(int i=0;i<34;++i)
    {
        if(a[i]>=2)
        {
            a[i]-=2;
            if(dfs(a,2)) return true;
            a[i]+=2;
        }
    }
    return false;
}
bool special(int *a)
{
    bool flag=a[0]>=1&&a[8]>=1&&a[9]>=1&&a[17]>=1&&a[18]>=1&&a[26]>=1;
    if(flag)
    {
        bool f=true,ff=false;
        for(int i=27;i<34;++i)
        {
            if(a[i]>=1)
            {
                if(a[i]>=2) ff=true;
            }
            else
            {
                f=false;
                break;
            }
        }
        if(f&&ff) return true;
    }
    int u=0;
    for(int i=0;i<=34;++i)
    {
        if(a[i]>=2) u++;
    }
    if(u>=7) return true;
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    while(t--)
    {
        tcase++;
        memset(Tp,0,sizeof(Tp));
        memset(Ap,0,sizeof(Ap));
        memset(Mp,0,sizeof(Mp));
        memset(Hp,0,sizeof(Hp));
        for(int i=0;i<3;++i)
        {
            readit(Tp,4);
            readit(Ap,4);
            readit(Mp,4);
            readit(Hp,4);
        }
        readit(Tp,1);
        readit(Ap,1);
        readit(Mp,1);
        readit(Hp,1);
        int rnd=0,ww=0;
        for(int i=0;i<21;++i)
        {
            if(ww==0) rnd++;
            readit(Tp,1);
            readit(Ap,1);
            readit(Mp,1);
            readit(Hp,1);
            if(ww==0&&(check(Tp)||special(Tp))) ww=1;
            if(ww==0&&(check(Ap)||special(Ap))) ww=2;
            if(ww==0&&(check(Mp)||special(Mp))) ww=3;
            if(ww==0&&(check(Hp)||special(Hp))) ww=4;
        }
        if(ww==0)
        {
            cout<<"For round "<<tcase<<", a Draw Hand occurs."<<endl;
        }
        else if(ww==1)
        {
            cout<<"For round "<<tcase<<", Takakamo Shizuno wins at turn "<<rnd<<"."<<endl;
        }
        else if(ww==2)
        {
            cout<<"For round "<<tcase<<", Atarashi Ako wins at turn "<<rnd<<"."<<endl;
        }
        else if(ww==3)
        {
            cout<<"For round "<<tcase<<", Matsumi Kuro wins at turn "<<rnd<<"."<<endl;
        }
        else
        {
            cout<<"For round "<<tcase<<", Haramura Nodoka wins at turn "<<rnd<<"."<<endl;
        }
    }
    return 0;
}
