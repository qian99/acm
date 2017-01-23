/***********三分法求函数极值*************/
void solve()
{
    double L, R, m, mm, mv, mmv;
    while (L + eps < R)
    {
        m = (L + R) / 2;
        mm = (m + R) / 2;
        mv = calc(m);
        mmv = calc(mm);
        if (mv <= mmv) R = mm; //三分法求最大值时改为mv>=mmv
        else L = m;
    }
}
/*************基础***********/
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double angle(Vector v) { return atan2(v.y, v.x); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
/*
向量叉积
若 P × Q > 0 , 则P在Q的顺时针方向。
若 P × Q < 0 , 则P在Q的逆时针方向。
若 P × Q = 0 , 则P与Q共线，但可能同向也可能反向。
*/
Vector vecunit(Vector x){ return x / Length(x);} //单位向量
Vector Normal(Vector x) { return Point(-x.y, x.x) / Length(x);} //垂直法向量
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
double Area2(const Point A, const Point B, const Point C) { return Length(Cross(B-A, C-A)); }

/****************直线与线段**************/

//求直线p+tv和q+tw的交点 Cross(v, w) == 0无交点
Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
{
    Vector u = p-q;
    double t = Cross(w, u) / Cross(v, w);
    return p + v*t;
}

//点p在直线ab的投影
Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B-A;
  return A+v*(Dot(v, P-A) / Dot(v, v));
}

//点到直线距离
double DistanceToLine(Point P, Point A, Point B) {
  Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2)) / Length(v1); // 如果不取绝对值，得到的是有向距离
}
//点在p线段上
bool OnSegment(Point p, Point a1, Point a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0; //线段包含短点时改成<=
}
// 过两点p1, p2的直线一般方程ax+by+c=0
// (x2-x1)(y-y1) = (y2-y1)(x-x1)
void getLineGeneralEquation(const Point& p1, const Point& p2, double& a, double& b, double &c) {
  a = p2.y-p1.y;
  b = p1.x-p2.x;
  c = -a*p1.x - b*p1.y;
}
//点到线段距离
double DistanceToSegment(Point p, Point a, Point b)
{
    if(a == b) return Length(p-a);
    Vector v1 = b-a, v2 = p-a, v3 = p-b;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}
//两线段最近距离
double dis_pair_seg(Point p1, Point p2, Point p3, Point p4)
{
    return min(min(DistanceToSegment(p1, p3, p4), DistanceToSegment(p2, p3, p4)),
     min(DistanceToSegment(p3, p1, p2), DistanceToSegment(p4, p1, p2)));
}
//线段相交判定
bool SegmentItersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
    c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
// 有向直线。它的左边就是对应的半平面
struct Line {
  Point P;    // 直线上任意一点
  Vector v;   // 方向向量
  double ang; // 极角，即从x正半轴旋转到向量v所需要的角（弧度）
  Line() {}
  Line(Point P, Vector v):P(P),v(v){ ang = atan2(v.y, v.x); }
  bool operator < (const Line& L) const {
    return ang < L.ang;
  }
};
//两直线交点
Point GetLineIntersection(Line a, Line b) {
  return GetLineIntersection(a.p, a.v, b.p, b.v);
}

// 点p在有向直线L的左边（线上不算）
bool OnLeft(const Line& L, const Point& p) {
  return Cross(L.v, p-L.P) > 0;
}

// 二直线交点，假定交点惟一存在
Point GetLineIntersection(const Line& a, const Line& b) {
  Vector u = a.P-b.P;
  double t = Cross(b.v, u) / Cross(a.v, b.v);
  return a.P+a.v*t;
}

// 半平面交主过程
vector<Point> HalfplaneIntersection(vector<Line> L) {
  int n = L.size();
  sort(L.begin(), L.end()); // 按极角排序

  int first, last;         // 双端队列的第一个元素和最后一个元素的下标
  vector<Point> p(n);      // p[i]为q[i]和q[i+1]的交点
  vector<Line> q(n);       // 双端队列
  vector<Point> ans;       // 结果

  q[first=last=0] = L[0];  // 双端队列初始化为只有一个半平面L[0]
  for(int i = 1; i < n; i++) {
    while(first < last && !OnLeft(L[i], p[last-1])) last--;
    while(first < last && !OnLeft(L[i], p[first])) first++;
    q[++last] = L[i];
    if(fabs(Cross(q[last].v, q[last-1].v)) < eps) { // 两向量平行且同向，取内侧的一个
      last--;
      if(OnLeft(q[last], L[i].P)) q[last] = L[i];
    }
    if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
  }
  while(first < last && !OnLeft(q[first], p[last-1])) last--; // 删除无用平面
  if(last - first <= 1) return ans; // 空集
  p[last] = GetLineIntersection(q[last], q[first]); // 计算首尾两个半平面的交点

  // 从deque复制到输出中
  for(int i = first; i <= last; i++) ans.push_back(p[i]);
  return ans;
}

/***********多边形**************/
//多边形有向面积
double PolygonArea(vector<Point> p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}

//多边形重心 点集逆时针给出
Point PolyGravity(Point *p, int n) {
    Point tmp, g = Point(0, 0);
    double sumArea = 0, area;
    for (int i=2; i<n; ++i) {
        area = Cross(p[i-1]-p[0], p[i]-p[0]);
        sumArea += area;
        tmp.x = p[0].x + p[i-1].x + p[i].x;
        tmp.y = p[0].y + p[i-1].y + p[i].y;
        g.x += tmp.x * area;
        g.y += tmp.y * area;
    }
    g.x /= (sumArea * 3.0); g.y /= (sumArea * 3.0);
    return g;
}

// 点集凸包
// 如果不希望在凸包的边上有输入点，把两个 <= 改成 <
// 注意：输入点集会被修改
vector<Point> ConvexHull(vector<Point>& p) {
  // 预处理，删除重复点
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}
//判断点是否在多边形内
int isPointInPolygon(Point p, Polygon poly)
{
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        if (OnSegment(p, poly[i], poly[(i + 1) % n])) return -1;    //边界
        int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;  //内部
    return 0;   //外部
}
// 凸包直径返回 点集直径的平方
int diameter2(vector<Point>& points) {
  vector<Point> p = ConvexHull(points);
  int n = p.size();
  if(n == 1) return 0;
  if(n == 2) return Dist2(p[0], p[1]);
  p.push_back(p[0]); // 免得取模
  int ans = 0;
  for(int u = 0, v = 1; u < n; u++) {
    // 一条直线贴住边p[u]-p[u+1]
    for(;;) {
      int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
      if(diff <= 0) {
        ans = max(ans, Dist2(p[u], p[v])); // u和v是对踵点
        if(diff == 0) ans = max(ans, Dist2(p[u], p[v+1])); // diff == 0时u和v+1也是对踵点
        break;
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}
//两凸包最近距离
double RC_Distance(Point *ch1, Point *ch2, int n, int m)
{
    int q=0, p=0;
    REP(i, n) if(ch1[i].y-ch1[p].y < -eps) p=i;
    REP(i, m) if(ch2[i].y-ch2[q].y > eps) q=i;
    ch1[n]=ch1[0];  ch2[m]=ch2[0];

    double tmp, ans=1e100;
    REP(i, n)
    {
        while((tmp = Cross(ch1[p+1]-ch1[p], ch2[q+1]-ch1[p]) - Cross(ch1[p+1]-ch1[p], ch2[q]- ch1[p])) > eps)
            q=(q+1)%m;
        if(tmp < -eps) ans = min(ans,DistanceToSegment(ch2[q],ch1[p],ch1[p+1]));
        else ans = min(ans,dis_pair_seg(ch1[p],ch1[p+1],ch2[q],ch2[q+1]));
        p=(p+1)%n;
    }
    return ans;
}
//凸包最大内接三角形
double RC_Triangle(Point* res,int n)// 凸包最大内接三角形
{
     if(n<3)    return 0;
     double ans=0, tmp;
     res[n] = res[0];
     int j, k;
     REP(i, n)
     {
         j = (i+1)%n;
         k = (j+1)%n;
         while((j != k) && (k != i))
         {
              while(Cross(res[j] - res[i], res[k+1] - res[i]) > Cross(res[j] - res[i], res[k] - res[i])) k= (k+1)%n;
              tmp = Cross(res[j] - res[i], res[k] - res[i]);if(tmp > ans) ans = tmp;
              j = (j+1)%n;
         }
     }
     return ans;
}
//模拟退火求费马点 保存在ptres中
double fermat_point(Point *pt, int n, Point& ptres)
{
    Point u, v;
    double step = 0.0, curlen, explen, minlen;
    int i, j, k, idx;
    bool flag;
    u.x = u.y = v.x = v.y = 0.0;
    REP(i, n)
    {
        step += fabs(pt[i].x) + fabs(pt[i].y);
        u.x += pt[i].x;
        u.y += pt[i].y;
    }
    u.x /= n;
    u.y /= n;
    flag = 0;
    while(step > eps)
    {
        for(k = 0; k < 10; step /= 2, ++k)
            for(i = -1; i <= 1; ++i)
                for(j = -1; j <= 1; ++j)
                {
                    v.x = u.x + step*i;
                    v.y = u.y + step*j;
                    curlen = explen = 0.0;
                        REP(idx, n)
                    {
                        curlen += dist(u, pt[idx]);
                        explen += dist(v, pt[idx]);
                    }
                    if(curlen > explen)
                    {
                        u = v;
                        minlen = explen;
                        flag = 1;
                    }
                }
    }
    ptres = u;
    return flag ? minlen : curlen;
}
//最近点对
bool cmpxy(const Point& a, const Point& b)
{
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
bool cmpy(const int& a, const int& b)
{
    return point[a].y < point[b].y;
}
double Closest_Pair(int left, int right)
{
    double d = INF;
    if(left==right)
        return d;
    if(left + 1 == right)
        return dis(left, right);
    int mid = (left+right)>>1;
    double d1 = Closest_Pair(left,mid);
    double d2 = Closest_Pair(mid+1,right);
    d = min(d1,d2);
    int i,j,k=0;
    //分离出宽度为d的区间
    for(i = left; i <= right; i++)
    {
        if(fabs(point[mid].x-point[i].x) <= d)
            tmpt[k++] = i;
    }
    sort(tmpt,tmpt+k,cmpy);
    //线性扫描
    for(i = 0; i < k; i++)
    {
        for(j = i+1; j < k && point[tmpt[j]].y-point[tmpt[i]].y<d; j++)
        {
            double d3 = dis(tmpt[i],tmpt[j]);
            if(d > d3)
                d = d3;
        }
    }
    return d;
}

/************圆************/
struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c, double r):c(c), r(r){}
    Point point(double a) //根据圆心角求点坐标
    {
        return Point(c.x+cos(a)*r, c.y+sin(a)*r);
    }
};
//求a点到b点(逆时针)在的圆上的圆弧长度
double D(Point a,Point b,int id)
{
    double ang1,ang2;
    Vector v1,v2;
    v1=a-Point(C[id].c.x,C[id].c.y);
    v2=b-Point(C[id].c.x,C[id].c.y);
    ang1=atan2(v1.y,v1.x);
    ang2=atan2(v2.y,v2.x);
    if(ang2<ang1) ang2+=2*pi;
    return C[id].r*(ang2-ang1);
}
//直线与圆交点 返回个数
int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol){
  double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
  double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
  double delta = f*f - 4*e*g; // 判别式
  if(dcmp(delta) < 0) return 0; // 相离
  if(dcmp(delta) == 0) { // 相切
    t1 = t2 = -f / (2 * e); sol.push_back(L.point(t1));
    return 1;
  }
  // 相交
  t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(L.point(t1));
  t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(L.point(t2));
  return 2;
}
//两圆交点 返回个数
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
  double d = Length(C1.c - C2.c);
  if(dcmp(d) == 0) {
    if(dcmp(C1.r - C2.r) == 0) return -1; // 重合，无穷多交点
    return 0;
  }
  if(dcmp(C1.r + C2.r - d) < 0) return 0;
  if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;

  double a = angle(C2.c - C1.c);
  double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
  Point p1 = C1.point(a-da), p2 = C1.point(a+da);

  sol.push_back(p1);
  if(p1 == p2) return 1;
  sol.push_back(p2);
  return 2;
}
//P到圆的切线
//v[i]是第i条切线的向量, 返回切线数
int getTangents(Point p, Circle C, Vector* v)
{
    Vector u = C.c - p;
    double dist = Length(u);
    if (dist < C.r) return 0;
    else if (dcmp(dist - C.r) == 0)
    {
        //P在圆上,只有一条切线
        v[0] = Rotate(u, PI / 2);
        return 1;
    }
    else
    {
        double ang = asin(C.r / dist);
        v[0] = Rotate(u, -ang);
        v[1] = Rotate(u, +ang);
        return 2;
    }
}

//两圆的公切线, -1表示无穷条切线
int getTangents(Circle A, Circle B, Point* a, Point* b)
{
    int cnt = 0;
    if (A.r < B.r) swap(A, B), swap(a, b);
    ///****************************
    int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r + B.r;
    if (d2 < rdiff * rdiff) return 0;   //内含

    ///***************************************
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if (d2 == 0 && A.r == B.r) return -1;    //无线多条切线
    if (d2 == rdiff * rdiff)    //内切, 1条切线
    {
        ///**********************
        a[cnt] = A.point(base); b[cnt] = B.point(base); cnt++;
        return 1;
    }
    //有外公切线
    double ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang); cnt++;
    a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang); cnt++;
    if (d2 == rsum * rsum)  //一条内公切线
    {
        a[cnt] = A.point(base); b[cnt] = B.point(PI + base); cnt++;
    }
    else if (d2 > rsum * rsum)  //两条内公切线
    {
        double ang = acos((A.r + B.r) / sqrt(d2));
        a[cnt] = A.point(base + ang); b[cnt] = B.point(PI + base + ang); cnt++;
        a[cnt] = A.point(base - ang); b[cnt] = B.point(PI + base - ang); cnt++;
    }
    return cnt;
}

//三角形外接圆
Circle CircumscribedCircle(Point p1, Point p2, Point p3) {
  double Bx = p2.x-p1.x, By = p2.y-p1.y;
  double Cx = p3.x-p1.x, Cy = p3.y-p1.y;
  double D = 2*(Bx*Cy-By*Cx);
  double cx = (Cy*(Bx*Bx+By*By) - By*(Cx*Cx+Cy*Cy))/D + p1.x;
  double cy = (Bx*(Cx*Cx+Cy*Cy) - Cx*(Bx*Bx+By*By))/D + p1.y;
  Point p = Point(cx, cy);
  return Circle(p, Length(p1-p));
}

//三角形内切圆
Circle InscribedCircle(Point p1, Point p2, Point p3) {
  double a = Length(p2-p3);
  double b = Length(p3-p1);
  double c = Length(p1-p2);
  Point p = (p1*a+p2*b+p3*c)/(a+b+c);
  return Circle(p, DistanceToLine(p, p1, p2));
}

// 过点p到圆C的切线。v[i]是第i条切线的向量。返回切线条数
int getTangents(Point p, Circle C, Vector* v) {
  Vector u = C.c - p;
  double dist = Length(u);
  if(dist < C.r) return 0;
  else if(dcmp(dist - C.r) == 0) { // p在圆上，只有一条切线
    v[0] = Rotate(u, PI/2);
    return 1;
  } else {
    double ang = asin(C.r / dist);
    v[0] = Rotate(u, -ang);
    v[1] = Rotate(u, +ang);
    return 2;
  }
}

//所有经过点p 半径为r 且与直线L相切的圆心
vector<Point> CircleThroughPointTangentToLineGivenRadius(Point p, Line L, double r) {
  vector<Point> ans;
  double t1, t2;
  getLineCircleIntersection(L.move(-r), Circle(p, r), t1, t2, ans);
  getLineCircleIntersection(L.move(r), Circle(p, r), t1, t2, ans);
  return ans;
}

//半径为r 与a b两直线相切的圆心
vector<Point> CircleTangentToLinesGivenRadius(Line a, Line b, double r) {
  vector<Point> ans;
  Line L1 = a.move(-r), L2 = a.move(r);
  Line L3 = b.move(-r), L4 = b.move(r);
  ans.push_back(GetLineIntersection(L1, L3));
  ans.push_back(GetLineIntersection(L1, L4));
  ans.push_back(GetLineIntersection(L2, L3));
  ans.push_back(GetLineIntersection(L2, L4));
  return ans;
}

//与两圆相切 半径为r的所有圆心
vector<Point> CircleTangentToTwoDisjointCirclesWithRadius(Circle c1, Circle c2, double r) {
  vector<Point> ans;
  Vector v = c2.c - c1.c;
  double dist = Length(v);
  int d = dcmp(dist - c1.r -c2.r - r*2);
  if(d > 0) return ans;
  getCircleCircleIntersection(Circle(c1.c, c1.r+r), Circle(c2.c, c2.r+r), ans);
  return ans;
}

//多边形与圆相交面积
Point GetIntersection(Line a, Line b) //线段交点
{
    Vector u = a.p-b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v*t;
}
bool InCircle(Point x, Circle c) { return dcmp(c.r - Length(c.c - x)) >= 0;}
bool OnCircle(Point x, Circle c) { return dcmp(c.r - Length(c.c - x)) == 0;}
//线段与圆的交点
int getSegCircleIntersection(Line L, Circle C, Point* sol)
{
    Vector nor = normal(L.v);
    Line pl = Line(C.c, nor);
    Point ip = GetIntersection(pl, L);
    double dis = Length(ip - C.c);
    if (dcmp(dis - C.r) > 0) return 0;
    Point dxy = vecunit(L.v) * sqrt(sqr(C.r) - sqr(dis));
    int ret = 0;
    sol[ret] = ip + dxy;
    if (OnSegment(sol[ret], L.p, L.point(1))) ret++;
    sol[ret] = ip - dxy;
    if (OnSegment(sol[ret], L.p, L.point(1))) ret++;
    return ret;
}
double SegCircleArea(Circle C, Point a, Point b) //线段切割圆
{
    double a1 = angle(a - C.c);
    double a2 = angle(b - C.c);
    double da = fabs(a1 - a2);
    if (da > PI) da = PI * 2.0 - da;
    return dcmp(Cross(b - C.c, a - C.c)) * da * sqr(C.r) / 2.0;
}

double PolyCiclrArea(Circle C, Point *p, int n)//多边形与圆相交面积
{
    double ret = 0.0;
    Point sol[2];
    p[n] = p[0];
    REP(i, n)
    {
        double t1, t2;
        int cnt = getSegCircleIntersection(Line(p[i], p[i+1]-p[i]), C, sol);
        if (cnt == 0)
        {
            if (!InCircle(p[i], C) || !InCircle(p[i+1], C)) ret += SegCircleArea(C, p[i], p[i+1]);
            else ret += Cross(p[i+1] - C.c, p[i] - C.c) / 2.0;
        }
        if (cnt == 1)
        {
            if (InCircle(p[i], C) && !InCircle(p[i+1], C)) ret += Cross(sol[0] - C.c, p[i] - C.c) / 2.0, ret += SegCircleArea(C, sol[0], p[i+1]);
            else ret += SegCircleArea(C, p[i], sol[0]), ret += Cross(p[i+1] - C.c, sol[0] - C.c) / 2.0;
        }
        if (cnt == 2)
        {
            if ((p[i] < p[i + 1]) ^ (sol[0] < sol[1])) swap(sol[0], sol[1]);
            ret += SegCircleArea(C, p[i], sol[0]);
            ret += Cross(sol[1] - C.c, sol[0] - C.c) / 2.0;
            ret += SegCircleArea(C, sol[1], p[i+1]);
        }
    }
    return fabs(ret);
}

/*********其他模板*********/
//以下模板来自网上，都未使用过
//pick定理
LL x_mult(cpoint a,cpoint b,cpoint p)
{
    return (a.x-p.x)*(b.y-p.y)-(a.y-p.y)*(b.x-p.x);
}
LL pick()
{
    LL s =0, e = 0;
    for(int i=0;i<n;i++)
    {
        s += x_mult(re[i],re[i+1],re[0]);
        e += gcd(abs(re[i].y-re[i+1].y),abs(re[i].x-re[i+1].x));
    }e/=2;s/=2;
    return Abs(s)+1-e;
}

//快速判断点是否在凸包内
struct POINT{
    double x,y;
    POINT(double _x = 0, double _y = 0):x(_x),y(_y){};
    void show(){
        cout<<x<<" "<<y<<endl;
    }
};
POINT p[MAXN],wp[MAXN];
double multiply(POINT sp,POINT ep,POINT op){ //叉积
    return (sp.x-op.x) * (ep.y-op.y) - (ep.x-op.x) * (sp.y-op.y);
}
bool onseg(POINT a,POINT s,POINT e){   // 判断点是否在线段上
    if(multiply(a,s,e) == 0 && a.x <= max(s.x,e.x) && a.x >= min(s.x,e.x)
       && a.y <= max(s.y,e.y) && a.y >= min(s.y,e.y))
        return true;
    return false;
}
bool inside(POINT pp,POINT sp,POINT ep,POINT op){ //判断点pp是否在三角形中(极角序)
    if(onseg(pp,sp,ep) || onseg(pp,sp,op) || onseg(pp,ep,op)) //如果在三角形上
        return true;
    if(multiply(sp,ep,pp) > 0 && multiply(ep,op,pp) > 0
       && multiply(sp,op,pp) < 0)  //如果在三角形内
           return true;
    return false;
}
bool bsearch(POINT a,int len)
{    //二分所构造的三角形
    int l = 1,r = len,m;
    while(l < r){
        m = (l + r) / 2;
        if(inside(a,p[0],p[m],p[m+1]) == true) return true;
        if(multiply(p[0],p[m],a) >= 0 && multiply(p[0],p[m+1],a) <= 0
            && multiply(p[m],p[m+1],a) < 0) return false;
        if(multiply(p[0],p[m],a) > 0 && multiply(p[0],p[m+1],a) > 0)
            l = m + 1;
        else r = m;
    }
    return false;
}
int main()
{
    int n,m,k,tmp = 0,cnt = 0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 0 ; i < n ; i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    p[n] = p[0];
    for(int i = 0 ; i < m ; i++){
        scanf("%lf%lf",&wp[i].x,&wp[i].y);
        if(bsearch(wp[i],n-1) == true) cnt++;
    }
    if(cnt >= k) printf("YES\n");
    else printf("NO\n");
    return 0;
}

//圆的面积并
//圆的面积并
//
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define sqr(x) ((x)*(x))
using namespace std;

const int N = 1010;
const double eps = 1e-8;
const double pi = acos(-1.0);
double area[N];
int n;

int dcmp(double x) {
    if (x < -eps) return -1; else return x > eps;
}

struct cp {
    double x, y, r, angle;
    int d;
    cp(){}
    cp(double xx, double yy, double ang = 0, int t = 0) {
        x = xx;  y = yy;  angle = ang;  d = t;
    }
    void get() {
        scanf("%lf%lf%lf", &x, &y, &r);
        d = 1;
    }
}cir[N], tp[N * 2];

double dis(cp a, cp b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double cross(cp p0, cp p1, cp p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

int CirCrossCir(cp p1, double r1, cp p2, double r2, cp &cp1, cp &cp2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + eps < 0) return 0; if (d < eps) d = 0; else d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d; sq *= 2;
    cp1.x = (x - dy) / sq; cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq; cp2.y = (y - dx) / sq;
    if (d > eps) return 2; else return 1;
}

bool circmp(const cp& u, const cp& v) {
    return dcmp(u.r - v.r) < 0;
}

bool cmp(const cp& u, const cp& v) {
    if (dcmp(u.angle - v.angle)) return u.angle < v.angle;
    return u.d > v.d;
}

double calc(cp cir, cp cp1, cp cp2) {
    double ans = (cp2.angle - cp1.angle) * sqr(cir.r)
        - cross(cir, cp1, cp2) + cross(cp(0, 0), cp1, cp2);
    return ans / 2;
}

void CirUnion(cp cir[], int n) {
    cp cp1, cp2;
    sort(cir, cir + n, circmp);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dcmp(dis(cir[i], cir[j]) + cir[i].r - cir[j].r) <= 0)
                cir[i].d++;
    for (int i = 0; i < n; ++i) {
        int tn = 0, cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (CirCrossCir(cir[i], cir[i].r, cir[j], cir[j].r,
                cp2, cp1) < 2) continue;
            cp1.angle = atan2(cp1.y - cir[i].y, cp1.x - cir[i].x);
            cp2.angle = atan2(cp2.y - cir[i].y, cp2.x - cir[i].x);
            cp1.d = 1;    tp[tn++] = cp1;
            cp2.d = -1;   tp[tn++] = cp2;
            if (dcmp(cp1.angle - cp2.angle) > 0) cnt++;
        }
        tp[tn++] = cp(cir[i].x - cir[i].r, cir[i].y, pi, -cnt);
        tp[tn++] = cp(cir[i].x - cir[i].r, cir[i].y, -pi, cnt);
        sort(tp, tp + tn, cmp);
        int p, s = cir[i].d + tp[0].d;
        for (int j = 1; j < tn; ++j) {
            p = s;  s += tp[j].d;
            area[p] += calc(cir[i], tp[j - 1], tp[j]);
        }
    }
}

void solve()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        cir[i].get();
    memset(area, 0, sizeof(area));
    CirUnion(cir, n);
    //去掉重复计算的
    for (int i = 1; i <= n; ++i) {
        area[i] -= area[i + 1];
    }
    //area[i]为重叠了i次的面积
    //tot 为总面积
    double tot = 0;
    for(int i=1; i<=n; i++) tot += area[i];
    printf("%f\n", tot);
}

//多边形面积并
#define PDI pair<double,int>
#define point pair<double,double>
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define zero 1e-8
#define maxN 502
#define maxp 5
point operator +(point a,point b) { return mp(a.x+b.x,a.y+b.y); }
point operator -(point a,point b) { return mp(a.x-b.x,a.y-b.y); }
double operator *(point a,point b) { return a.x*b.y-b.x*a.y; }
double operator ^(point a,point b) { return a.x*b.x+a.y*b.y; }
inline double cross(point o,point a,point b) { return (a-o)*(b-o); }
inline int cmp(double x) { if (fabs(x)<zero) return 0; return x>0? 1:-1; }

class Polygon
{
	private: int i; double s;
	public: int n; point p[maxp];
	point& operator[] (int idx) { return p[idx]; }
	void input() { for (i=0;i<n;i++) scanf("%lf %lf",&p[i].x,&p[i].y); p[n]=p[0]; }
	double Area() { for (s=0,i=0;i<n;i++) s+=p[i]*p[i+1]; return s/2; }
};

PDI s[maxN*maxp*2];
Polygon P[maxN];
double S,ts;
int N;
inline double seg(point o,point a,point b)
{
	if (cmp(b.x-a.x)==0) return (o.y-a.y)/(b.y-a.y);
	return (o.x-a.x)/(b.x-a.x);
}

double PolygonUnion()
{
	int M,c1,c2; double s1,s2,ret=0;
	for (int i=0;i<N;i++)
	for (int ii=0;ii<P[i].n;ii++)
	{
		M=0;
		s[M++]=mp(0.00,0);
		s[M++]=mp(1.00,0);
		for (int j=0;j<N;j++) if (i!=j)
		for (int jj=0;jj<P[j].n;jj++)
		{
			c1=cmp(cross(P[i][ii],P[i][ii+1],P[j][jj]));
			c2=cmp(cross(P[i][ii],P[i][ii+1],P[j][jj+1]));
			if (c1==0 && c2==0)
			{
				if (((P[i][ii+1]-P[i][ii])^(P[j][jj+1]-P[j][jj]))>0 && i>j)
				{
					s[M++]=mp(seg(P[j][jj],P[i][ii],P[i][ii+1]),1);
					s[M++]=mp(seg(P[j][jj+1],P[i][ii],P[i][ii+1]),-1);
				}
			}
			else
			{
				s1=cross(P[j][jj],P[j][jj+1],P[i][ii]);
				s2=cross(P[j][jj],P[j][jj+1],P[i][ii+1]);
				if (c1>=0 && c2<0) s[M++]=mp(s1/(s1-s2),1);
				else if (c1<0 && c2>=0) s[M++]=mp(s1/(s1-s2),-1);
			}
		}
		sort(s,s+M);
		double pre=min(max(s[0].x,0.0),1.0),now;
		double sum=0;
		int cov=s[0].y;
		for (int j=1;j<M;j++)
		{
			now=min(max(s[j].x,0.0),1.0);
			if (!cov) sum+=now-pre;
			cov+=s[j].y;
			pre=now;
		}
		ret+=P[i][ii]*P[i][ii+1]*sum;
	}
	return ret/2;
}

int main()
{
	scanf("%d\n",&N);
	for (int i=0;i<N;i++)
	{
		P[i].n=4;
		P[i].input();
		ts=P[i].Area();
		if (cmp(ts<0))
		{
			reverse(P[i].p,P[i].p+P[i].n);
			P[i][P[i].n]=P[i][0];
			ts=-ts;
		}
		S+=ts;
	}
	printf("%.9lf\n",S/PolygonUnion());
}

//二维平面一个n个节点的简单多边形，多边形内有一个灯泡，求照明面积。
const double eps = 1e-8;
const double pi = acos(-1.);
using namespace std;
int dblcmp( double x )
{
	if( fabs(x) < eps )	return 0;
	return x > 0 ? 1 : -1;
}
double nowAng;
struct point
{
	double x, y, a;
	point(){}
	point( double _x, double _y ) : x(_x), y(_y)
	{
		a = atan2(y, x);
	}
	bool operator<( const point p )	const
	{
		if( dblcmp(a-p.a) == 0 )
			return x*x+y*y < p.x*p.x+p.y*p.y;
		return a < p.a;
	}
} p[60000], O;
inline double dis( point a, point b )
{
	double dx = a.x-b.x;
	double dy = a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}
inline double cross( point k, point a, point b )
{
	return (a.x-k.x)*(b.y-k.y) - (a.y-k.y)*(b.x-k.x);
}
point inter( point a1, point a2, double ang )
{
	point b1 = point(0, 0), b2 = point(cos(ang), sin(ang));
	double u = cross(a1, a2, b1), v = cross(a2, a1, b2);
	return point((b1.x*v+b2.x*u)/(v+u), (b1.y*v+b2.y*u)/(v+u));
}
struct line
{
	point a, b;
	line(){};
	line( point _a, point _b ) : a(_a), b(_b){};
	bool operator<( const line p )	const
	{
		if( fabs(a.x-p.a.x) < eps && fabs(a.y-p.a.y) < eps )
			return cross(a, b, p.b) < 0;
		point d1 = inter(a, b, nowAng);
		point d2 = inter(p.a, p.b, nowAng);
		return d1.x*d1.x+d1.y*d1.y < d2.x*d2.x+d2.y*d2.y;
	}
};
struct Event
{
	double ang;
	int id, st;
	line L;
	bool operator<( const Event p )	const
	{
		if( dblcmp(ang-p.ang) == 0 )
			return st > p.st;
		return ang < p.ang;
	}
} E[200000];
int c;
void add( point a, point b, int k )
{
	if( b < a )
		swap(a, b);
	E[c].ang = a.a, E[c].st = 1, E[c].L = line(a, b), E[c++].id = k;
	E[c].ang = b.a, E[c].st = 0, E[c++].id = k;
}
multiset<line> S;
multiset<line>::iterator itArr[100000];
inline double cal( line L, double d1, double d2 )
{
	point a = inter(L.a, L.b, d1);
	point b = inter(L.a, L.b, d2);
	return fabs(0.5*cross(O, a, b));
}
int main()
{
	int i, j, k, n;
	double d, t, ans, pre;
	while( scanf("%lf %lf", &O.x, &O.y) != EOF )
	{
		c = 0;
		scanf("%d", &n);
		for( i = 0; i < n; ++i )
		{
			scanf("%lf %lf", &p[i].x, &p[i].y);
			p[i].x -= O.x, p[i].y -= O.y;
			p[i].a = atan2(p[i].y, p[i].x);
		}
		O.x = O.y = 0;
		p[n] = p[0];
		for( i = k = 0; i < n; ++i )
		{
			d = fabs(p[i+1].a-p[i].a);
			if( d < pi )
				add(p[i], p[i+1], k++);
			else
			{
				point tmp = inter(p[i], p[i+1], pi);
				tmp.a = pi*dblcmp(p[i].a);
				add(p[i], tmp, k++);
				tmp.a = pi*dblcmp(p[i+1].a);
				add(p[i+1], tmp, k++);
			}
		}
		sort(E, E+c);
		S.clear();
		ans = 0;	pre = -pi;
		for( i = 0; i < c; ++i )
		{
			nowAng = E[i].ang;
			if( E[i].st )
			{
				if( S.size() > 0 )
					ans += cal(*S.begin(), pre, E[i].ang);
				itArr[E[i].id] = S.insert(E[i].L);
			}
			else
			{
				ans += cal(*S.begin(), pre, E[i].ang);
				S.erase(itArr[E[i].id]);
			}
			pre = E[i].ang;
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
//二维平面有n(0 < n <= 50000)条线段，要求判断n条线段是否存在交点，如果有，输出相交线段的编号。
#define MP make_pair
#define PI pair
#define FI first
#define SE second
#define PB push_back
#define SZ size()
const double eps = 1e-10;
const double pi = acos(-1.);
const int mod = 1000000007;
const int maxn = 50100;
const int INF = 99999999;
struct point
{
	int x, y;
	bool operator<( const point p )	const
	{
		if( x == p.x )	return y < p.y;
		return x < p.x;
	}
} L[maxn][2];
int tim;
struct eve
{
	int x, id, st;
	eve(){}
	eve( int _x, int _id, int _st ) : x(_x), id(_id), st(_st) {}
	bool operator<( const eve p ) 	const
	{
		if( p.x == x )	return st > p.st;
		return x < p.x;
	}
} E[maxn*2];

void getLine( point x, point y, double& a, double& b, double& c )
{
	a = y.y - x.y;
	b = x.x - y.x;
	c = y.x*x.y - x.x*y.y;
}
struct ele
{
	int id;
	double k, c;
	ele( int _id )
	{
		id = _id;
		if( L[id][0].x == L[id][1].x )
			k = 0, c = L[id][0].y;
		else
		{
			double A, B, C;
			getLine(L[id][0], L[id][1], A, B, C);
			k = -A/B, c = -C/B;
		}
	}
	bool operator<( const ele p )	const
	{
		return tim*k+c < tim*p.k+p.c;
	}
};
set<ele> S;
set<ele>::iterator itArr[maxn];
inline set<ele>::iterator preIt( set<ele>::iterator it )
{
	return it == S.begin() ? S.end() : --it;
}

inline set<ele>::iterator nxtIt( set<ele>::iterator it )
{
	return it == S.end() ? S.end() : ++it;
}

int cross( point& k, point& a, point& b )
{
	return (a.x-k.x)*(b.y-k.y) - (a.y-k.y)*(b.x-k.x);
}

int dot( point& k, point& a, point& b )
{
	return (a.x-k.x)*(b.x-k.x) + (a.y-k.y)*(b.y-k.y);
}

inline int sgn( int x )
{
	if( x > 0 )	return 1;
	if( x < 0 )	return -1;
	return x;
}

bool inter( int a, int b )
{
	int d1 = sgn(cross(L[a][0], L[a][1], L[b][0]));
	int d2 = sgn(cross(L[a][0], L[a][1], L[b][1]));
	int d3 = sgn(cross(L[b][0], L[b][1], L[a][0]));
	int d4 = sgn(cross(L[b][0], L[b][1], L[a][1]));
	if( (d1^d2)==-2 && (d3^d4)==-2 )	return 1;
	if( d1 == 0 && dot(L[b][0], L[a][0], L[a][1]) <= 0 )	return 1;
	if( d2 == 0 && dot(L[b][1], L[a][0], L[a][1]) <= 0 )	return 1;
	if( d3 == 0 && dot(L[a][0], L[b][0], L[b][1]) <= 0 )	return 1;
	if( d4 == 0 && dot(L[a][1], L[b][0], L[b][1]) <= 0 )	return 1;
	return 0;
}

bool solve( int n )
{
	sort(E, E+n);
	S.clear();
	for( int i = 0; i < n; ++i )
	{
		tim = E[i].x;
		int id = E[i].id;

		if( E[i].st == 1 )
		{
			ele t = ele(id);
			set<ele>::iterator nxt = S.lower_bound(t), pre = preIt(nxt);
			if( nxt != S.end() && inter((*nxt).id, id) )
			{
				printf("YES\n%d %d\n", (*nxt).id, id);
				return 1;
			}
			if( pre != S.end() && inter((*pre).id, id) )
			{
				printf("YES\n%d %d\n", (*pre).id, id);
				return 1;
			}
			itArr[id] = S.insert(nxt, t);
		}
		else
		{
			set<ele>::iterator pre = preIt( itArr[id] ), nxt = nxtIt( itArr[id] );
			if( pre != S.end() && nxt != S.end() && inter((*pre).id, (*nxt).id) )
			{
				printf("YES\n%d %d\n", (*pre).id, (*nxt).id);
				return 1;
			}
			S.erase(itArr[id]);
		}
	}

	return 0;
}

int main()
{
	srand(4);
	int T, cases = 1;
	int i, j, k, e;
	double A, B, C;
	int N, M;
	scanf("%d", &N);
	for( i = 1; i <= N; ++i )
	{
		scanf("%d %d %d %d", &L[i][0].x, &L[i][0].y, &L[i][1].x, &L[i][1].y);
		if( L[i][1] < L[i][0] )
			swap(L[i][0], L[i][1]);
	}
	for( i = 1, e = 0; i <= N; ++i )
	{
		E[e++] = eve(L[i][0].x, i, +1);
		E[e++] = eve(L[i][1].x, i, -1);
	}
	if( !solve(e) )
		puts("NO");
	return 0;
}
