#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// ���Ͽ��� ���� �ܾ �ҷ��� ���ߴ� ����
void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x*2;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

//�Է� Ű�� Ȯ��
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//���� ����
vector<string> pastWord;   // ����ڰ� �Է��� �ܾ�
vector<string> strWords;   // ���Ͽ� �ִ� �ܾ� ����

//�ܼ�ȭ�� ũ�� ����
void SetConsoleView()
{
	system("mode con:cols=80 lines=20");     //âũ�� ����
	system("title WORD GAME");
}

//��Ʈ�� ȭ�� ���
void DrawReadyGame()
{
	system("cls");
	gotoXY(5, 2);
	cout << " ==========================================";
	gotoXY(5, 3);
	cout << " =============== WORD GAME ================";
	gotoXY(5, 4);
	cout << " ==========================================";
	gotoXY(6, 6);
	cout << " �����Ϸ��� 'S'Ű�� ���� �ּ���";
	gotoXY(20, 18);
}

//intro ȭ������ 's'�� Ŭ���ϸ� ���� ����
bool ReadyGame()
{
	DrawReadyGame();
	while (true)
	{
		int key = GetKeyDown();
		key = tolower(key);

		if (key == 's')
		{
			return true;
		}
	}
	return false;
}

// ���Ͽ� �ִ� �ܾ� �о� ����
void SetWords()
{
	string str[4] = { "apple", "banana", "code", "program" };

	//1. ���� �о� ����
	ifstream readFromFile("words.txt");     

	//2. ������ ���� ���
	if (!readFromFile.is_open())
	{
		//3. ���� �����ϱ�
		ofstream writeToFile("words.txt");   

		for (int i = 0; i < 4; i++)
		{
			string temp = str[i];
			if (i < 3)
			{
				temp += "\n";     
			}
			writeToFile.write(temp.c_str(), temp.size());
			strWords.push_back(str[i]);
		}
		//4. ���� �ݱ�
		writeToFile.close();
	}
	else
	{
		// ������ �ִ� ���
		while (!readFromFile.eof())
		{
			string temp;
			getline(readFromFile, temp);
			strWords.push_back(temp);    //���Ϳ� �� �ֱ�
		}
		readFromFile.close();
	}
}

//ȭ�� ���
void DrawStartGame()
{
	system("cls");
	gotoXY(5, 8);
	cout << "past = ";
	for (int i = 0; i < (int)pastWord.size(); i++)
	{
		cout << pastWord[i] << " ";
	}

	gotoXY(5, 12);
	cout << "input = ";
}

//���� ����
void StartGame()
{
	srand((unsigned)time(NULL));

	SetWords();

	//���ʹ� ����� ������ �ʰ� ����� �� �ִ� ������ ����
	while (true)
	{
		int num = rand() % (int)strWords.size();   //������ ������ŭ �����ϰ� �ܾ� ����
		string strQuestion;   //����
		string strOriginal = strWords[num];
		int originalLen = (int)strOriginal.length();   //���� �� 
		string strTemp;
		bool overlap=false;

		for (int i = 0; i < originalLen; i++)
		{
			strQuestion += "_";
		}

		while (true)
		{
			DrawStartGame();

			gotoXY(5, 5);
			// _ _ _ ���
			for (int i = 0; i < originalLen; i++)
			{
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			gotoXY(9, 12);
			string strInput;
			
			cin >> strInput;

			for (int i = 0; i < (int)pastWord.size(); i++)
			{
			
				if (pastWord[i] == strInput)
				{
					overlap = true;					
				}
			}

			// �ߺ����� �ʾ��� ������ pastWord�� �� ����
			if(!overlap) 
			{ 
				pastWord.push_back(strInput);    //input �Է°� ���Ϳ� ����
			}
			

			

			if (strInput.length() == 1)
			{
				
				
					//�ܾ� üũ
					for (int i = 0; i < originalLen; i++)
					{
						if (strOriginal[i] == strInput[0])
						{
							strQuestion[i] = strInput[0];
						
						}
					}
			

				

			}
			else if(strInput.length()>1)
			{
				//������ ������ ������ ���
				if (strOriginal == strInput)
				{
					pastWord.clear();
					break;
				}
			}
		}

	}
}

int main()
{
	SetConsoleView();

	while (true)
	{
		if (ReadyGame())
		{
			StartGame();
		}
	}
	return 0;
}
