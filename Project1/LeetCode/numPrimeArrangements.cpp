# include <vector>
using std::vector;

int numPrimeArrangements(int n) {
	int value = 1;
	vector<int> prime_number;
	if (n >= 3)
	{
		prime_number.push_back(2);
		prime_number.push_back(3);

		for (int i = 4; i < n + 1; i++)
		{
			for (int j = 2; j < i / 2 + 1; j++)
			{
				int temp = 0;
				temp = i / j;
				if (i - j * temp == 0)
					break;
				else
				{
					if (j == i / 2 || j == (i - 1) / 2)
						prime_number.push_back(i);

					else
						continue;
				}

			}

		}
	}
	else if (n == 2)
		prime_number.push_back(2);

	for (int i = 1; i < prime_number.size() + 1; i++)
	{
		value = value * i;
	}
	return value;




}