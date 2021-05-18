#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// 파일에서 영어 단어를 불러와 맞추는 게임
void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x*2;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

//입력 키값 확인
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//변수 선언
vector<string> pastWord;   // 사용자가 입력한 단어
vector<string> strWords;   // 파일에 있는 단어 저장

//콘솔화면 크기 지정
void SetConsoleView()
{
	system("mode con:cols=80 lines=20");     //창크기 지정
	system("title WORD GAME");
}

//인트로 화면 출력
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
	cout << " 시작하려면 'S'키를 눌러 주세요";
	gotoXY(20, 18);
}

//intro 화면으로 's'를 클릭하면 게임 시작
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

// 파일에 있는 단어 읽어 오기
void SetWords()
{
	string str[4] = { "apple", "banana", "code", "program" };

	//1. 파일 읽어 오기
	ifstream readFromFile("words.txt");     

	//2. 파일이 없는 경우
	if (!readFromFile.is_open())
	{
		//3. 파일 생성하기
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
		//4. 파일 닫기
		writeToFile.close();
	}
	else
	{
		// 파일이 있는 경우
		while (!readFromFile.eof())
		{
			string temp;
			getline(readFromFile, temp);
			strWords.push_back(temp);    //벡터에 값 넣기
		}
		readFromFile.close();
	}
}

//화면 출력
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

//게임 동작
void StartGame()
{
	srand((unsigned)time(NULL));

	SetWords();

	//벡터는 사이즈를 정하지 않고 사용할 수 있는 장점이 있음
	while (true)
	{
		int num = rand() % (int)strWords.size();   //벡터의 갯수만큼 랜덤하게 단어 선정
		string strQuestion;   //문제
		string strOriginal = strWords[num];
		int originalLen = (int)strOriginal.length();   //글자 수 
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
			// _ _ _ 출력
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

			// 중복되지 않았을 때에만 pastWord에 값 저장
			if(!overlap) 
			{ 
				pastWord.push_back(strInput);    //input 입력값 벡터에 저장
			}
			

			

			if (strInput.length() == 1)
			{
				
				
					//단어 체크
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
				//유저가 정답을 눌렀을 경우
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
