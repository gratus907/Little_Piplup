int kadane(vector <int> &arr)
{
	int nn = arr.size();
	int lm = arr[0], gm = arr[0];
	for (int i = 1; i<nn; i++)
	{
		lm = max(arr[i], lm+arr[i]);
		gm = max(gm, lm);
	}
	return gm;
}
