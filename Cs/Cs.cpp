// Cs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <locale>
#include <vector>
using namespace std;
#pragma warning(disable: 4996)

void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}
class Setting{
public:
	  HWND hwnd;
	  HDC hdc;
	void Start(){
		char Title[] = "RgR";
		SetConsoleTitle(L"RgR");
		GetConsoleTitle(L"RgR", 1024);
		hwnd = FindWindow(NULL, L"RgR"); // Узнаем hwnd окна
		hdc= GetDC(hwnd);
		setlocale(LC_ALL, "Russian");
	}
};
class Zastavka{
public:
	int x;
	int y;
	void Begin(){
		double k = -10;
		while (k<10)
		{
			Function(k);
			    gotoxy(x, y); printf(".");
			k += 0.5;
			Sleep(10);
		}
		_getch();
	}
	void Color()
	{
		SetCol
	}
	void Cls(){
		system("cls");
	}
	void Function(double t){
		x = (cos(t)+2)*20;
		y = (sin(t)+2)*5;
		 //printf("%d %d\n", x, y);
	}
};
class display{
public:
	int KeyUp;
	int pozitsiya;
	int GN;
	void Start(int N){
		pozitsiya = 0;
		GN = N;
		while (true)
		{
			Ctrelca();
			Switsw();
			Cls();
		}
	}
	void Ctrelca(){
		gotoxy(8, pozitsiya); printf(">");
	}
	void Cls(){
		for (int i = 0; i < GN; i++){
			gotoxy(8, i); printf(" ");
		}
	}
	void Exit(){

	}
	void Print(){}
	void Switsw(){
		KeyUp = _getch();
		switch (KeyUp)
		{
		case 72:pozitsiya--; break; //кнопка вверх

		case 80:pozitsiya++; break; //кнопка вниз
		default:

			break;
		}
		// ограниченыя стрелки(>), нужно для того чтобы но не выходила за пределы пунктов меню
		if (pozitsiya == GN) pozitsiya = 0;
		if (pozitsiya < 0) pozitsiya = GN-1;

	}
};
class Record{
public:
	char Name[10];
	char Info[40][10];
	int count;
};
class Catalog{
public:
	FILE * file;
	char *fileName;
	vector<Record> record;
	void Start(){
		OpenFile();
		LoadCatalog();
		PrintRecordList();
	}
	void OpenFile(){
		file = fopen("test.txt", "rt");
	}
	void NewCatalog(char Name[]){
		file = fopen(Name, "wt");
	}
	void NewRecord(){
		Record temp;
		printf("Название планеты:");
		scanf("%s", temp.Name);
		printf("Описание:");
		scanf("%s", temp.Info);
		record.push_back(temp);
	}
	void RecordDelete(int i){
		record.erase(record.begin() + i);
	}
	void PrintRecordList(){
		display d;
		for (int i = 0; i < record.size(); i++){
			gotoxy(10, i); printf("%s", record[i].Name);
		}
		d.Start(record.size());
	}
	void PrintRecord(int N){
		for (int i = 0; i < record[N].count; i++){
			printf("%s ", record[N].Info[i]);
		}

	}
	void LoadCatalog(){
		char text[10];
		int i = 0;
		while (!feof(file))
		{
			Record TempRecord;
			fscanf(file, "%s", &text);
			strcpy(TempRecord.Name, text);

			int j = 0;
			while (true)
			{
				fscanf(file, "%s", &TempRecord.Info[j]);
				if (TempRecord.Info[j][0] == '}'){ break; }
				j++;
			}
			TempRecord.count = j;

			i++;
			record.push_back(TempRecord);
		}
	}
};

class Menu{
	public:
		int KeyUp;
		Catalog c;
			void Ctrelca(){
			gotoxy(29, pozitsiya); printf(">");
		}
		void Cls(){
			for (int i = 0; i < 6; i++){
				gotoxy(28, i + 4); printf("  ");
			}
		}	int pozitsiya;
		void Start(){
			pozitsiya = 4;
			Lable();
			while (true)
			{
				Key();
				Cls();
				Ctrelca();
			}
		}

		void Switsw2(){
			switch (pozitsiya){
			case 4:
				Clear();
				c.Start(); break;
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:break;
			}
		}
		void Clear()
		{
			system("cls");
		}
		void Switsw(){
			switch (KeyUp)
			{
			case 72:pozitsiya--; break; //кнопка вверх

			case 80:pozitsiya++; break; //кнопка вниз
			case 13:
				Switsw2();
				break;
			}
			// ограниченыя стрелки(>), нужно для того чтобы но не выходила за пределы пунктов меню
			if (pozitsiya > 9) pozitsiya = 4;
			if (pozitsiya < 4) pozitsiya = 9;

		}
		void Key(){
			KeyUp = _getch();
			Switsw();
		}
		void Lable(){
			gotoxy(30, 3); printf("_______Меню________");
			gotoxy(30, 4); printf(" Просмотр каталога");
			gotoxy(30, 5); printf(" Добавить в каталог");
			gotoxy(30, 6); printf(" Выбрать каталог");
			gotoxy(30, 7); printf(" Заставка");
			gotoxy(30, 8); printf(" Автор");
			gotoxy(30, 9); printf(" Выход");
		}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Setting Nastaroica;
	Nastaroica.Start();
//	Menu menu;
	//menu.Start();
	//_getch();
	Zastavka Zas;
	Zas.Begin();
	return 0;
}

