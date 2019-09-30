struct Fenwick
{
	int n;
	int tree[MAXN];
	void init()
	{
		memset(tree,0,sizeof(tree));
	}
	int sum(int p)
	{
		int ret = 0;
		for (; p > 0; p -= p & -p)
			ret += tree[p];
		return ret;
	}
	void add (int p, int val)
	{
		for (; p <= n; p += p & -p) tree[p] += val;
	}
	void change (int p, int val)
	{
		int u = sum(p) - sum(p-1);
		add(p, val-u);
	}
};
