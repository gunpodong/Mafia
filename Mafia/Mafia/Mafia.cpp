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

void NightResult(int Target, bool Heal, bool Overlap)
{
	if (Target == 0 && Overlap == false)
	{
		cout << "밤중에 주민 한 명이 살해 당했습니다." << endl;
		_getch();
	}
	else if (Target == 0 && Overlap == true)
	{
		cout << "밤중에 아무일도 일어나지 않았습니다." << endl;
		_getch();
	}
	else
	{
		if (Heal == true)
		{
			cout << "밤중에 의사가 환자를 치료하여 피해자가 나오지 않았습니다." << endl;
			_getch();
		}
		else
		{
			cout << "밤중에 아무일도 일어나지 않았습니다." << endl;
			_getch();
		}
	}
}

void Night(int Town[], int PersonNum, int Player, int Doctor, int Mafia)
{
	//마피아와 의사의 행동
	cout << "밤이 되었습니다..." << endl;
	_getch();

	random_device Target;
	mt19937 gen(Target());
	uniform_int_distribution<int> dis(0, PersonNum - 1);

	int DoctorsTarget = 0;
	int MafiasTarget = 0;
	bool Heal = false;
	bool Overlap = false;

	if (Doctor != Player)
		DoctorsTarget = dis(gen);
	else
	{
		cout << "치료할 주민을 선택하세요 : ";
		cin >> DoctorsTarget;
		DoctorsTarget -= 1;
	}

	if (Mafia != Player)
		MafiasTarget = dis(gen);
	else
	{
		cout << "살해할 주민을 선택하세요 : ";
		cin >> MafiasTarget;
		MafiasTarget -= 1;
	}

	if (Town[MafiasTarget] == 0)
	{
		Overlap = true;
	}

	if (Overlap == false)
	{
		if (MafiasTarget == DoctorsTarget && Town[Doctor] != 0 && Town[DoctorsTarget] != 3)
		{
			if (Town[DoctorsTarget] != Town[Doctor])
				Town[DoctorsTarget] = 1;
			else
				Town[DoctorsTarget] = 2;
			Heal = true;
		}
		else if (MafiasTarget != Player && Town[MafiasTarget] == 1 || Town[MafiasTarget] == 2)
		{
			Town[MafiasTarget] = 0;
		}
	}
	else if(Mafia != Player)
	{
		MafiasTarget = dis(gen);

		if (MafiasTarget == DoctorsTarget && Town[Doctor] != 0 && Town[DoctorsTarget] != 3)
		{
			if (Town[DoctorsTarget] != Town[Doctor])
				Town[DoctorsTarget] = 1;
			else
				Town[DoctorsTarget] = 2;
			Heal = true;
		}
		else if (MafiasTarget != Player && Town[MafiasTarget] == 1 || Town[MafiasTarget] == 2)
		{
			Town[MafiasTarget] = 0;
			Overlap = false;
		}
	}


	cout << "..." << endl;
	_getch();

	NightResult(Town[MafiasTarget], Heal,Overlap);
}

void Morning(int Town[], int PersonNum, int Player)
{
	//마피아와 의사의 행동결과
	cout << "날이 밝았습니다..." << endl;
	_getch();

	int Live = 0;

	for (int i = 0; i < PersonNum; i++)
	{
		if (Town[i] != 0)
			Live += 1;
	}

	cout << "남은 주민의 수는 " << Live << "명 입니다." << endl;
	_getch();
	cout << "..." << endl;
	_getch();

}

void AfternoonResult(int Town[], int PlayersChoice)
{
	if (PlayersChoice != 0)
	{
		if (Town[PlayersChoice - 1] != 0)
		{
			Town[PlayersChoice - 1] = 0;
			cout << PlayersChoice << "번 주민이 마을에서 추방되었습니다." << endl;
		}
		else
			cout << "이미 죽은 주민입니다." << endl;
	}
	else
		cout << "투표가 무효 되었습니다." << endl;
	_getch();
}

void Afternoon(int Town[], int PersonNum, int Player, int Mafia)
{
	//플레이어의 투표와 투표결과
	random_device Choice;
	mt19937 gen(Choice());
	uniform_int_distribution<int> dis(0, PersonNum - 1);

	cout << "투표시간이 되었습니다..." << endl;
	_getch();

	int PlayersChoice = 0;

	if (Mafia != Player)
	{
		for (int i = 0; i < PersonNum; i++)
		{
			if (i != Player)
				cout << i + 1 << "번 ";
		}

		cout << endl << "위의 주민들 중 마피아라고 생각되는 주민을 지목하세요(무효표는 0번 입니다.) : ";
		cin >> PlayersChoice;
	}
	else
	{
		PlayersChoice = dis(gen);
		cout << "주민들의 투표결과는 " << PlayersChoice << "번입니다." << endl;
	}

	_getch();
	cout << "..." << endl;
	_getch();

	AfternoonResult(Town,PlayersChoice);
}

bool Result(int Town[], int PersonNum)
{
	//게임이 끝났는지의 여부
	bool GameSet = true;
	bool MafiaWin = false;
	int Live = 0;

	for (int i = 0; i < PersonNum; i++)
	{
		if (Town[i] > 0)
		{
			Live += 1;
			if (Town[i] == 3)
				GameSet = false;
		}
	}

	if (Live == 2)
	{
		MafiaWin = true;
		GameSet = true;
	}

	if (GameSet == true)
	{
		if (MafiaWin == true)
			cout << "마을에 마피아와 플레이어만 남았으므로 마피아의 승리입니다." << endl;
		else
			cout << "마피아가 마을에서 추방되었으므로 시민들의 승리입니다." << endl;
		_getch();
	}

	return GameSet;
}

int main()
{
	int PersonNum = 0;
	
	cout << "마을주민의 수를 입력하세요 : ";
	cin >> PersonNum;
	cout << endl;

	int *Town = new int[PersonNum];

	fill_n(Town, PersonNum, 1);
	
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

	int Doctor = 0;
	int Mafia = 0;

	for (int i = 0; i < PersonNum; i++)
	{
		if (Town[i] == 2)
			Doctor = i;
		else if (Town[i] == 3)
			Mafia = i;
	}
	int Player = dis(gen);

	/*while (Town[Player] == 3)
	{
		Player = dis(gen);
	}*/

	cout << "당신은 " << Player + 1<< "번 주민입니다." << endl;
	_getch();
	if (Town[Player] == 1)
		cout << "당신의 직업은 시민입니다. 투표를 통해 마피아를 찾아내세요." << endl;
	else if (Town[Player] == 2)
		cout << "당신의 직업은 의사입니다. 시민을 보호하며 투표를 통해 마피아를 찾아내세요." << endl;
	else if (Town[Player] == 3)
		cout << "당신의 직업은 마피아입니다. 시민들을 살해하여 마을에서 살아남으세요." << endl;
	_getch();
	cout << "※다음으로 넘어가기 위해선 아무키나 입력하세요※" << endl << endl;
	_getch();

	bool GameSet = false;

	while (!GameSet)
	{
		Night(Town, PersonNum, Player, Doctor, Mafia);
		cout << endl;

		GameSet = Result(Town, PersonNum);
		if (GameSet == true)
			continue;

		Morning(Town, PersonNum, Player);
		cout << endl;

		Afternoon(Town, PersonNum, Player, Mafia);
		cout << endl;

		GameSet = Result(Town, PersonNum);
	}

	delete[] Town;

	return 0;
}