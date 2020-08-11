#include<iostream>
#include<random>

using namespace std;

int main()
{
	random_device PsnJob;

	mt19937 gen(PsnJob());

	uniform_int_distribution<int> dis(1, 3);

	for (int i = 0; i < 5; i++)
	{
		cout << dis(gen) << endl;
	}
}