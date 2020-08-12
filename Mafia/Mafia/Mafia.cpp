#include<iostream>
#include<random>
#include<string>
#include<conio.h>

using namespace std;

int SetJob(int JobNum)
{
	if (JobNum == 0)
		return 2;
	else
		return 3;
}

void Night(int Town[], int PersonNum)
{
	_getch();
	//마피아와 의사의 행동
	cout << "밤이 되었습니다..." << endl;

	for (int i = 1; i < PersonNum + 1; i++)
	{
		cout << Town[i] << endl;
	}
}

void Morning(int Town[],int PersonNum)
{
	_getch();
	//마피아와 의사의 행동결과
	cout << "날이 밝았습니다..." << endl;
}

void Afternoon(int Town[], int PersonNum)
{
	_getch();
	//플레이어의 투표와 투표결과
	cout << "투표시간이 되었습니다..." << endl;
}
int main()
{
	int Town[100] = { 0 };
	int PersonNum = 0;
	int Mafia = 0;
	int Doctor = 0;
	//char Next[2];
	
	fill_n(Town, 100, 1);

	cout << "마을주민의 수를 입력하세요 : ";
	cin >> PersonNum;
	cout << endl;

	random_device Psn;
	mt19937 gen(Psn());
	uniform_int_distribution<int> dis(1, PersonNum);

	for (int i = 0; i < 2; i++)
	{
		int a = dis(gen);

		if (Town[a] < 2)
			Town[a] = SetJob(i);
		else
			i -= 1;
	}

	int Player = dis(gen);

	while (Town[Player] == 3)
	{
		Player = dis(gen);
	}

	cout << "당신은 " << Player << "번 주민입니다." << endl;
	if (Town[Player] == 1)
		cout << "당신의 직업은 시민입니다. 투표를 통해 마피아를 찾아내세요." << endl;
	else
		cout << "당신의 직업은 의사입니다. 시민을 보호하며 투표를 통해 마피아를 찾아내세요." << endl;

	cout << "※다음으로 넘어가기 위해선 아무키나 입력하세요※" << endl << endl;

	while (1)
	{
		Night(Town, PersonNum);

		Morning(Town, PersonNum);

		Afternoon(Town, PersonNum);
	}

	return 0;
}