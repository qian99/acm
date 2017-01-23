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
int num[5];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;;
    cin>>t;
    int a,b,c;
    while(t--)
    {
        tcase++;
        cin>>num[0]>>num[1]>>num[2];
        cout<<"Case #"<<tcase<<":"<<endl;
        if(num[0]==num[1]&&num[1]==num[2])
        {
            cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
            continue;
        }
        sort(num,num+3);
        if(num[0]==num[1])
        {
            cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
            cout<<num[0]<<" "<<num[2]<<" "<<num[1]<<endl;
            cout<<num[2]<<" "<<num[1]<<" "<<num[0]<<endl;
            continue;
        }
        if(num[1]==num[2])
        {
            cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
            cout<<num[1]<<" "<<num[0]<<" "<<num[2]<<endl;
            cout<<num[2]<<" "<<num[1]<<" "<<num[0]<<endl;
            continue;
        }
        cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;
        cout<<num[0]<<" "<<num[2]<<" "<<num[1]<<endl;
        cout<<num[1]<<" "<<num[0]<<" "<<num[2]<<endl;
        cout<<num[1]<<" "<<num[2]<<" "<<num[0]<<endl;
        cout<<num[2]<<" "<<num[0]<<" "<<num[1]<<endl;
        cout<<num[2]<<" "<<num[1]<<" "<<num[0]<<endl;
    }
    return 0;
}
