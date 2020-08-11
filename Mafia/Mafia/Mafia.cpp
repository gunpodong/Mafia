#include<iostream>
#include<random>

using namespace std;

int SetJob(int PersonNum)
{
	random_device PsnJob;

	mt19937 gen(PsnJob());

	uniform_int_distribution<int> dis(2, 3);

	return dis(gen);
}

int main()
{
	int Town[100] = { 0 };
	int PersonNum = 0;
	int Mafia = 0;
	int Doctor = 0;
	
	fill_n(Town, 100, 1);

	cin >> PersonNum;

	for (int i = 0; i < PersonNum; i++)
	{	
		if(Mafia < 1 || Doctor < 1)
		{
			Town[i] = SetJob(PersonNum);
			if (Town[i] == 2)
				Doctor += 1;
			else if (Town[i] == 3)
				Mafia += 1;

			if (Doctor > 1)
				Town[i] = 1;
			else if (Mafia > 1)
				Town[i] = 1;
		}
	}

	for (int i = 0; i < PersonNum; i++)
	{
		cout << Town[i] << endl;
	}
}