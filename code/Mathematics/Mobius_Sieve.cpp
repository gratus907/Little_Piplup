void mobiusfunction(int upto)
{
    for (int i = 1; i <= upto; i++)
		mobius[i] = 1;
	for (int i = 2; i*i <= upto; i++)
	{
		if (mobius[i] == 1)
		{
			for (int j = i; j <= upto; j += i)
				mobius[j] *= -i;
			for (int j = i * i; j <= upto; j += i * i)
				mobius[j] = 0;
		}
	}
	for (int i = 2; i <= upto; i++)
	{
		if (mobius[i] == i)
			mobius[i] = 1;
		else if (mobius[i] == -i)
			mobius[i] = -1;
		else if (mobius[i] < 0)
			mobius[i] = 1;
		else if (mobius[i] > 0)
			mobius[i] = -1;
	}
}
