//求 x^2+y^2=z^2  (x<y<z)并且(x,y,z)=1的三元组的个数

bool flag[maxn];
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
void solve(int n)
{
    memset(flag,0,sizeof(flag));
    int m=sqrt((double)n);
    int cnt=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=i+1;j<=m;j+=2)
        {
            if(i*i+j*j>n) break;
            if(gcd(i,j)!=1) continue;
            int x=j*j-i*i,y=2*i*j,z=i*i+j*j;
            cnt++;
            for(int k=1;z*k<=n;k++)
                flag[x*k]=flag[y*k]=flag[z*k]=true;
        }
    }
    cout<<cnt<<" ";
    cnt=0;
    for(int i=1;i<=n;++i)
        if(!flag[i]) cnt++;
    cout<<cnt<<endl;
}