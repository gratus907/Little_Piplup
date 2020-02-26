/* FFT Library : Originally Written by Myungwoo *
 * https://blog.myungwoo.kr/54                  *
 * Nonrecursive, Bit-Flipping Trick             *
 * Several Modifications                        */
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

/* FFT polynomial Multiplication with higher precision */
void multiply(const vi &a, const vi &b, vi &res)
{
    vector <base> fa_big, fb_big;
    vector <base> fa_small, fb_small;
    int cut_val = sqrt(P);
    int n = 1;
    while(n < max(sz(a),sz(b)))
        n <<= 1;
    fa_big.resize(n);
    fa_small.resize(n);
    fb_big.resize(n);
    fb_small.resize(n);
    for (int i = 0; i<sz(a); i++)
    {
        fa_big[i] = a[i]/cut_val;
        fa_small[i] = a[i]%cut_val;
    }
    for (int i = 0; i<sz(b); i++)
    {
        fb_big[i] = b[i]/cut_val;
        fb_small[i] = b[i]%cut_val;
    }
    fft(fa_big,0), fft(fb_big,0);
    fft(fa_small, 0), fft(fb_small, 0);
    vector <base> fa_big_2(all(fa_big));
    vector <base> fa_small_2(all(fa_small));
    for (int i = 0; i<n; i++)
    {
        fa_big_2[i] *= fb_big[i];
        fa_big[i] *= fb_small[i];
        fa_small[i] *= fb_small[i];
        fa_small_2[i] *= fb_big[i];
    }
    fft(fa_small,1);
    fft(fa_small_2, 1);
    fft(fa_big, 1);
    fft(fa_big_2, 1);
    res.resize(n);
    for (int i = 0; i<n; i++)
    {
        int ss = (int64_t)round(fa_small[i].real());
        int sb = (int64_t)round(fa_small_2[i].real());
        int bs = (int64_t)round(fa_big[i].real());
        int bb = (int64_t)round(fa_big_2[i].real());
        res[i] = ss;
        res[i] += (((((sb+bs)%P)*cut_val)%P)+P)%P;
        res[i] += (((((bb*cut_val)%P)*cut_val)%P)+P)%P;
        res[i] %= P;
    }
}
