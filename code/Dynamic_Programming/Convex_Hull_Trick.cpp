ll A[100020];
ll B[100020];
ll dp[100020];
//dp[i] = dp[j]+A[i]*B[j];
typedef struct linear
{
    ll a,b;
    double xpos;
    linear(ll x=0, ll y=0, double z=0): a(x),b(y),xpos(z){}
    ll cal(ll n){return a*n+b;}
}linear;
double cross(linear l, linear m)
{
    return (double)(l.b-m.b)/(double)(m.a-l.a);
}
linear s[100020];
int main()
{
    ll n;
    scanf("%lld",&n);
    for(int i=0; i<n; i++)
        scanf("%lld",A+i);
    for(int i=0; i<n; i++)
        scanf("%lld",B+i);
    s[0]=linear(B[0],0,-1e18);
    ll fpos = 0, pt = 0;
    // pt: 스택의 맨 위 fpos: 대입할 직선 결정
    for(int i=1; i<n; i++)
    {
        // 시작할 위치가 A[i](좌표) 보다 처음으로 크거나 같아지는 순간
        while(s[fpos].xpos<A[i]&&fpos<=pt)
            fpos++;
        dp[i]=s[--fpos].cal(A[i]);
        linear newlin = linear(B[i],dp[i],0);
        while(pt>0&&cross(s[pt],newlin)<=s[pt].xpos)
        {
            if(pt==fpos)
                fpos--;
            pt--;
        }
        newlin.xpos = cross(s[pt],newlin);
        s[++pt] = newlin;
    }
    printf("%lld",dp[n-1]);
}
