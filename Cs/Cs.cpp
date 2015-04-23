// Cs.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		hwnd = FindWindow(NULL, L"RgR"); // ������ hwnd ����
		hdc= GetDC(hwnd);
		setlocale(LC_ALL, "Russian");
	}
};
class Zastavka{
public:
	int x;
	int y;
	void Saturn(){
		printf("     *******   \n");
		printf("   ************   \n");
		printf("  **************   \n");
		printf("  **************   \n");
		printf("   ************    \n");
		printf("      ****** \n");
	}
	void Begin(){
		double k = -10;
		Saturn();
		while (true)
		{

			while (k < 10)
			{
				Function(k);
				gotoxy(x, y); printf("*");
				k += 0.5;
				Sleep(10);
			}
		}
		_getch();
	}
	void Color()
	{
		 
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
	int k = 0;
	void Start(int N){
		pozitsiya = 0;
		GN = N;
		while (k != 1)
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
		case 72:pozitsiya--; break; //������ �����

		case 80:pozitsiya++; break; //������ ����
		case 13: k = 1;
			return;
			break;
		}
		// ����������� �������(>), ����� ��� ���� ����� �� �� �������� �� ������� ������� ����
		if (pozitsiya == GN) pozitsiya = 0;
		if (pozitsiya < 0) pozitsiya = GN-1;

	}
};
class Avtor{
public:
	void start(){
		printf("            ������������ ����������� � ����� ���������� ���������\n              ������ ��������������� ����������� ����������� ");
		printf("\n\n\n               <������� ����������� � �������������� �������>");
		printf("\n \n                                  �������� ������ ");
		printf("\n \n                             ������ � ����� � ������");
		printf("\n\n\n\n                                        ������������ �������: ������� �.�.");
		printf("\n                                        ���������� �������: ��������� A.");

		_getch();
	}
};
class Record{
public:
	char Name[10];
	char Info[40][10];
	int count;
};
char a[30];
class Catalog{
public:
	FILE * file;
	string fileName;
	vector<Record> record;
	vector<char *> FileList;
	void Start(){
		if (!fileName[0]){
			printf("������:�������� �������");
			_getch();
		}
		else{
			OpenFile(fileName);
			if (record.size()==0){
				LoadCatalog();
			}
			PrintRecordList();
		}
	}
	void OpenFile(string Name){
		file = fopen(Name.c_str(), "r");
	}
	void NewCatalog(){
		char name[30];
		printf("��� ��������(�/� �� ����������):");
		scanf("%s", &name);
		file = fopen(name, "wt");
		fclose(file);
	}
		void LoadSettingFile(){
			OpenFile("File.txt");
			char temp[30];
			while (!feof(file))
			{
				fscanf(file, "%s", &temp);
				FileList.push_back(temp);
			}
			fclose(file);
			PrintCatalogist();
		}
	
	void NewRecord(){
		Record temp;
		printf("�������� �������:");
		scanf("%s", temp.Name);
		printf("��������:");
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
		system("cls");
		PrintRecord(d.pozitsiya);
		_getch();
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
			Clear();
			switch (pozitsiya){
			case 4:c.Start();break;
		    case 5:c.NewCatalog(); break;
			case 6:c.LoadSettingFile(); break;
			case 7: break;
			case 8: Avtor atv; atv.start(); break;
				case 9:exit(0); break;
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
			case 72:pozitsiya--; break; //������ �����

			case 80:pozitsiya++; break; //������ ����
			case 13:
				Switsw2();
				break;
			}
			// ����������� �������(>), ����� ��� ���� ����� �� �� �������� �� ������� ������� ����
			if (pozitsiya > 9) pozitsiya = 4;
			if (pozitsiya < 4) pozitsiya = 9;

		}
		void Key(){
			KeyUp = _getch();
			Switsw();
		}
		void Lable(){
			gotoxy(30, 3); printf("_______����________");
			gotoxy(30, 4); printf(" �������� ��������");
			gotoxy(30, 5); printf(" �������� � �������");
			gotoxy(30, 6); printf(" ������� �������");
			gotoxy(30, 7); printf(" ��������");
			gotoxy(30, 8); printf(" �����");
			gotoxy(30, 9); printf(" �����");
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
	//Zastavka Zas;
	//Zas.Begin();
	return 0;
}

