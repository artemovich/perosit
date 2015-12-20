Expression * read_expressio(char * a)
{
	Expression *e;
	int i = 0, k = 1;
	int n = strlen(a);
	char *b, *c;
	b = (char*)calloc(n, sizeof(char));
	c = (char*)calloc(n, sizeof(char));
	*a = *a + 1;
	while (k != 0)
	{
		if (a[i] == '(')
		{
			k++;
			for (int j = 0; j < n - 1; j++)
				b[i] = a[i + 1];
		}
		else
		{
			int j = 0;
			while (a[j] == ')')
				k--;
			j++;
			for (int kk = 0; kk < j - 1; kk++)
				c[kk] = b[kk];
		}
		if (c[0] != '\0')
		{
			int j = 0;
			if (c[j] >= 'a' && c[j] <= 'z')
				if (c[j] == 's' || c[j] == 'c')
				{
					if (c[++j] == 'i')
					{

					}
					else;
					if (a[i + 1] == 'o')
					{

					}
					else;
				}
				else e = new Variable(c[j - 1]);
			else e = new Variable(c[j]);

		}
	}
}
