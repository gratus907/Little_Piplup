void multiply(const vi &a, const vi &b, vi &res)
{
    vector <base> fa_big, fb_big;
    vector <base> fa_small, fb_small;
    int cut_val = sqrt(P);
    int n = 1;
    while(n < max(sz(a),sz(b)))
        n <<= 1;
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
        res[i] += (sb+bs)*cut_val;
        res[i] += bb*cut_val*cut_val;
    }
}
