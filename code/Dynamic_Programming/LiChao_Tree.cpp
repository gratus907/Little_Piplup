using pii = pair<int, int>;
#define int ll
const int INF = 2e18;
struct Line // Linear function ax + b
{
    int a, b;
    int eval(int x)
    {
    return a*x + b;
    }
};

struct Node
{
    int left, right;
    int start, end;
    Line f;
};
Node new_node(int a, int b)
{
    return {-1,-1,a,b,{0,-INF}};
}
vector <Node> nodes;

struct LiChao
{
    void init(int min_x, int max_x)
    {
        nodes.push_back(new_node(min_x, max_x));
    }
    void insert(int n, Line new_line)
    {
        int xl = nodes[n].start, xr = nodes[n].end;
        int xm = (xl + xr)/2;
        Line llo, lhi;
        llo = nodes[n].f, lhi = new_line;
        if (llo.eval(xl) >= lhi.eval(xl))
            swap(llo, lhi);
        if (llo.eval(xr) <= lhi.eval(xr))
        {
            nodes[n].f = lhi;
            return;
        }
        else if (llo.eval(xm) > lhi.eval(xm))
        {
            nodes[n].f = llo;
            if (nodes[n].left == -1)
            {
                nodes[n].left = nodes.size();
                nodes.push_back(new_node(xl,xm));
            }
            insert(nodes[n].left, lhi);
        }
        else
        {
            nodes[n].f = lhi;
            if (nodes[n].right == -1)
            {
                nodes[n].right = nodes.size();
                nodes.push_back(new_node(xm+1,xr));
            }
            insert(nodes[n].right,llo);
        }
    }

    int get(int n, int q)
    {
        if (n == -1) return -INF;
        int xl = nodes[n].start, xr = nodes[n].end;
        int xm = (xl + xr)/2;
        if (q > xm)
            return max(nodes[n].f.eval(q), get(nodes[n].right, q));
        else
            return max(nodes[n].f.eval(q), get(nodes[n].left, q));
    }

    int evaluate(int pt)
    {
        return get(0, pt);
    }
};
LiChao CHT;
int32_t main()
{
    usecppio
    int Q;
        CHT.init(-2e12, 2e12);
    cin >> Q;
    while(Q--)
    {
        int tp;
        cin >> tp;
        if (tp == 1)
        {
            int a, b;
            cin >> a >> b;
            CHT.insert(0, {a, b});
        }
        else
        {
            int x;
            cin >> x;
            cout << CHT.evaluate(x) << '\n';
        }
    }
}
