#define sz(v) ((int)(v).size())
typedef complex<double> base;
typedef vector <int> vi;
typedef vector <base> vb;
const double PI = acos(-1);

void fft(vb &a, bool invert)
{
    int n = sz(a);
    for (int i = 1, j=0; i<n; i++)
    {
        int bit = n>>1;
        for (; j>=bit; bit>>=1)
        {
            j -= bit;
        }
        j += bit;
        if (i < j)
            swap(a[i],a[j]);
    }
    vector<base> root(n/2);
    double ang = 2*acos(-1)/n*(invert?-1:1);
    for(int i=0;i<n/2;i++)root[i]=base(cos(ang*i), sin(ang*i));
    for (int len = 2; len <= n; len <<= 1)
    {
        int step = n / len;
        for (int i = 0; i<n; i+= len)
        {
            for (int j = 0; j<len/2; j++)
            {
                base u = a[i+j], v = a[i+j+len/2]*root[step*j];
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i<n; i++)
            a[i] /= n;
    }
}

void multiply(const vi &a, const vi &b, vi &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while(n < max(sz(a),sz(b)))
        n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,0), fft(fb,0);
    for (int i = 0; i<n; i++)
        fa[i] *= fb[i];
    fft(fa,1);
    res.resize(n);
    for (int i = 0; i<n; i++)
        res[i] = int64_t(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
}
