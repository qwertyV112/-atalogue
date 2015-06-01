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
HWND hwnd;
HDC hdc;
      
void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}

class Setting{
public:

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
	int Key;
	HBRUSH hBrush;
	void krug(float x, float y){
		Ellipse(hdc, x, y, x+5, y+5);
	}
	void Color(int k){
		hBrush = CreateSolidBrush(RGB(k, 0, 0));
		SelectObject(hdc, hBrush);
	}
	void Saturn(int m){
		for (float t = -22; t < 2*3.14; t += 0.05){
			float x = 16 * pow(sin(t), 3);	
			float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
			krug((x * -m) + 300, (y * -m) + 130);
		}

	}
	int SetingKey(){
		return GetKeyState(VK_RETURN);
	}
	bool GetKey(){
		int i = SetingKey();
		if (Key != i) return false;
		else true;
	}
	void Begin(){
		Key = SetingKey();
		float f = -1.14;
		while (GetKey())
		{
			float k = sin(f);
			f += 0.08;
			if (f > 3.14) f = -3.14;
			Color(255);
			Saturn(fabs(k) * 10);
			Color(0);
			Sleep(20);
			Rectangle(hdc, 0, 0, 700,500);
		}
	_getch();
	}

	void Cls(){
		system("cls");
	}
};
class display{
public:
	int KeyUp;
	int pozitsiya;
	int GN;
	int k = 0;
	void Start(int N){
		gotoxy(1, 24); printf("1)Удалить     2)Изменить   3)Поиск");
		pozitsiya = 0;
		GN = N;
		while (k < 1)
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
	//	printf("%d", pozitsiya);
		switch (KeyUp)
		{
		case 72:pozitsiya--; break; //кнопка вверх
		case 49:k = 1; break;
		case 50:k = 2; break;
		case 51:k = 4; break;
		case 80:pozitsiya++; break; //кнопка вниз
		case 13: k = 3;
			return;
			break;
		}
		// ограниченыя стрелки(>), нужно для того чтобы но не выходила за пределы пунктов меню
		if (pozitsiya == GN) pozitsiya = 0;
		if (pozitsiya < 0) pozitsiya = GN-1;

	}
};
class Avtor{
public:
	void start(){
		printf("            МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ\n              Омский государственный технический университет ");
		printf("\n\n\n               <Кафедра Информатики и вычислительной техники>");
		printf("\n \n                                  КУРСОВОЙ ПРОЕКТ ");
		printf("\n \n                             Работа с мышью и звуком");
		printf("\n\n\n\n                                        Руководитель проекта: Шафеева О.П.");
		printf("\n                                        Разработал студент: Игнатьева A.Я");

		_getch();
	}
};
class Record{
public:
	char Name[10];
	char Info[240][20];
	int count;
};
char a[30];
class Catalog{
public:
	FILE * file;
	bool bfilile = true;
	string fileName;
	vector<Record> record;
	vector<char *> FileList;
	void Start(){
		if (!fileName[0]){
			printf("Ошибка:невыбран каталог");
			_getch();
		}
		else{
			OpenFile(fileName);
			if (record.size()==0){
				LoadCatalog();
				bfilile = false;

			}
			PrintRecordList();
		}
	}
	void OpenFile(string Name){
		file = fopen(Name.c_str(), "r");
	}
	void NewCatalog(){
		char name[30];
		printf("Имя каталога(ж/л на Английском):");
		scanf("%s", &name);
		file = fopen(name, "wt");
		fclose(file);
	}
		void LoadSettingFile(){
			OpenFile("File.txt");
			char  temp[30];
			while (!feof(file))
			{
				
				fscanf(file, "%s", &temp);
				FileList.push_back(temp);
			}
			fclose(file);
			PrintCatalogist();
		}

	void NewRecord(){
		char t = ' ';
		OpenFile(fileName);
		if (bfilile){ LoadCatalog(); }
		
		FILE *f = fopen("temp.txt", "w");
		Record temp;
		printf("Название планеты:");
		scanf("%s", temp.Name);
		printf("Описание:");
		int i = 1;
		while (t !=VK_RETURN)
		{
			t = _getch();
			printf("%c", t);
			fprintf(f, "%c", t);
			i++;
		} 
		fprintf(f, " }");
		fclose(f); f = fopen("temp.txt", "r"); int j = 0;
		while (!feof(f))
		{
			fscanf(f, "%s", &temp.Info[j]);
			j++;
		}
		fclose(f); temp.count = j;
		//Text[i + 1] = '\0';
		//gotoxy(3, 5); printf("%s", Text);

		//temp =Preobrazov(Text,temp);
		record.push_back(temp);
	}
	void poisk(){
		system("cls");
		char temp[20];
		printf("Введите слово для поиска:");
		scanf("%s", &temp);
		for (int i = 0; i < record.size(); i++){
			if ((strcmp(temp, record[i].Name)) == 0){
				PrintRecord(i);
			}
		}
		_getch();
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
		if (d.k == 1){ RecordDelete(d.pozitsiya); }
		if (d.k == 2){ Edit(d.pozitsiya); }
		if (d.k == 4){ poisk(); }
		if (d.k==3){
			system("cls");
			PrintRecord(d.pozitsiya);
			_getch();
		}
		
	}
	void Edit(int i){
		system("cls");
		int j = 0;
		printf("Переминование(%s):", record[i].Name);
		scanf("%s", &record[i].Name);
		for (int u = 0; u < record[i].count; u++) { sprintf(record[i].Info[u], "\0");}
		FILE *f = fopen("temp.txt", "w");
		printf("Введите описание:");
		while (j != 13)
		{
			j = getch();
			printf("%c", j);
			fprintf(f, "%c", j);
		}printf("\n");
		fclose(f); f = fopen("temp.txt", "r"); j = 0;
		while (!feof(f))
		{
			fscanf(f, "%s", &record[i].Info[j]);
			j++;
		}
		record[i].count = j;
		fclose(f);

	}
	void PrintCatalogist(){
		display d;
		for (int i = 0; i < FileList.size(); i++){
			gotoxy(10, i); printf("%s", FileList[i]);
		}
		d.Start(FileList.size());
		fileName = FileList[d.pozitsiya];
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
			TempRecord.count = j+1;

			i++;
			record.push_back(TempRecord);
		}
	}
	void SaveCatalog(){
		file = fopen(fileName.c_str(), "w");
		for (int i = 0; i < record.size(); i++)
		{
			fprintf(file, "%s\n", record[i].Name);
			for (int j = 0; j < record[i].count; j++)
			{
				fprintf(file, "%s ", record[i].Info[j]);
			}
			fprintf(file, "\n");
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
			Clear();
			switch (pozitsiya){
			case 4:c.Start();break;
		    case 5:c.NewRecord(); break;
			case 6:c.LoadSettingFile(); break;
			case 7: Zastavka Zas; Zas.Begin();break;
			case 8: Avtor atv; atv.start(); break;
			case 9: 
				if (c.fileName[0]){
					c.SaveCatalog();
				}
				exit(0);
				break;
			}
			Clear();
			Lable();
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
	Menu menu;
	menu.Start();
	//Avtor avt;
	//_getch();
//	Zastavka Zas;
	//Zas.Begin();
	
}

