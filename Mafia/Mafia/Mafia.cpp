#include<iostream>
#include<random>

using namespace std;

int SetJob(int JobNum)
{
	if (JobNum == 0)
		return 2;
	else
		return 3;
}

int main()
{
	int Town[100] = { 0 };
	int PersonNum = 0;
	int Mafia = 0;
	int Doctor = 0;
	
	fill_n(Town, 100, 1);

	cin >> PersonNum;

	random_device Psn;
	mt19937 gen(Psn());
	uniform_int_distribution<int> dis(0, PersonNum - 1);

	for (int i = 0; i < 2; i++)
	{
		int a = dis(gen);

		if (Town[a] < 2)
			Town[a] = SetJob(i);
		else
			i -= 1;
	}

	for (int i = 0; i < PersonNum; i++)
	{
		cout << Town[i] << endl;
	}
}