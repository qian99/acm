const int maxn=30000+1000;
int ch[maxn][2],val[maxn],counts[maxn],r[maxn],size[maxn],tot,root;
void Newnode(int &rt,int v)
{
    rt=++tot;
    val[rt]=v;
    ch[rt][0]=ch[rt][1]=0;
    counts[rt]=size[rt]=1;
    r[rt]=rand();
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+counts[rt];
}
void Rotate(int &x,int kind)
{
    int y=ch[x][kind^1];
    ch[x][kind^1]=ch[y][kind];
    ch[y][kind]=x;
    PushUp(x);PushUp(y);
    x=y;
}
void Insert(int &rt,int v)
{
    if(rt==0)
    {
        Newnode(rt,v);
        return ;
    }
    if(v==val[rt]) counts[rt]++;
    else
    {
        int kind=(v>val[rt]);
        Insert(ch[rt][kind],v);
        if(r[ch[rt][kind]]<r[rt])
            Rotate(rt,kind^1);
    }
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][0]]>=k) return select(ch[rt][0],k);
    if(size[ch[rt][0]]+counts[rt]>=k) return val[rt];
    return select(ch[rt][1],k-size[ch[rt][0]]-counts[rt]);
}
void remove(int &rt,int v)
{
    if(val[rt]==v)
    {
        if(counts[rt]>1)
            counts[rt]--;
        else if(!ch[rt][0]&&!ch[rt][1])
        {rt=0;return ;}
        else
        {
            int kind=r[ch[rt][0]]<r[ch[rt][1]];
            Rotate(rt,kind);
            remove(rt,v);
        }
    }
    else remove(ch[rt][v>val[rt]],v);
    PushUp(rt);
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    size[0]=counts[0]=val[0]=0;
    tot=root=0;
    r[0]=(1LL<<31)-1;
    Newnode(root,2000000001);
}
