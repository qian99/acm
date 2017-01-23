const int mod=8191;
struct Matrix
{
    ll mat[2][2];
    void Init()
    {
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
};
Matrix operator *(const Matrix & a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
void find(ll d,ll &X,ll &Y)
{
    ll p0=1,p1=0,p;
    ll q0=0,q1=1,q;
    ll a0=sqrt((double)d),a=a0;
    ll g0=0,h0=1,g,h;
    while(true)
    {
        g=-g0+a*h0;
        h=(d-g*g)/h0;
        p=a*p0+p1;
        q=a*q0+q1;
        a=(g+a0)/h;
        if(p*p-d*q*q==1) {X=p;Y=q;return ;}
        p1=p0;p0=p;
        q1=q0;q0=q;
        g0=g;h0=h;
    }
}
ll solve(ll N,ll K)
{
    ll x1,y1;
    find(N,x1,y1);
    if(K==1) return x1;
    K-=1;
    Matrix a,b;
    a.Init();b.clear();
    b.mat[0][0]=b.mat[1][1]=x1;
    b.mat[1][0]=N*y1;b.mat[0][1]=y1;
    while(K)
    {
        if(K&1) a=a*b;
        b=b*b;
        K>>=1;
    }
    return (x1*a.mat[0][0]+y1*a.mat[1][0])%mod;
}