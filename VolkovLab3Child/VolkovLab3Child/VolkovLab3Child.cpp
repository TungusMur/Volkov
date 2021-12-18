#include <iostream>
#include <fstream>
#include <limits>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <stdlib.h>
#include <Windows.h>

using namespace std;
struct emp
{
	int num; // номер зачетки
	char name[10]; // имя студента
	double grade; // средний бал
};

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	emp wValue;
	FILE* bfile = NULL;
	int pos = 0,
		num;
	double newGrade = 1.0;
	char cNum[255];

	cout << "*****";
	cout << "Номер зачетки: " << argv[1] << "|Имя студента: " << argv[2] << "|Средний бал: " << argv[3] << "\n\n";
	cout << "*****\n";
	
	fopen_s(&bfile, "E:/Microsoft Visual Studio/Project/VolkovLab3/VolkovLab3/file.txt", "r+b");

	while (!feof(bfile)) {
		fseek(bfile, pos * sizeof(emp), SEEK_SET);
		fread(&num, sizeof(int), 1, bfile);
		
		sprintf_s(cNum, "%d", num);

		if(!feof(bfile) && (strcmp(cNum, argv[1]) == 0)) {
			fseek(bfile, sizeof(char[10]), SEEK_CUR);
			/**
			newGrade = atof(argv[3]);
			cout << newGrade;
			*/
			fread(&newGrade, sizeof(double), 3, bfile);
			cout << newGrade;
			break;
		}

		pos++;
	}

	fclose(bfile);

	_getch();








	/*const int N = 2;
	int p = 0;
	emp iCreditsNew;
	char num[255];
	char t;

	ifstream iFile("E:\\Microsoft Visual Studio\\Project\\VolkovLab3\\VolkovLab3\\file.txt", ios::binary);
	while (iFile.peek() != EOF) {
		p = iFile.tellg();
		iFile.read((char*)&iCreditsNew, sizeof(iCreditsNew));
		sprintf_s(num, "%d", iCreditsNew.num);
		if (strcmp(num, argv[1]) == 0) {
			sscanf_s(argv[3], "%lf", &iCreditsNew.grade);
			//iFile.write((char*)&iCreditsNew, sizeof(iCreditsNew));
			break;
		}
	}
	iFile.close();

	fstream oFile("E:\\Microsoft Visual Studio\\Project\\VolkovLab3\\VolkovLab3\\file.txt", ios::in | ios::out | ios::binary);
	for (int i = 0; i < 24; i++) {
		oFile.seekp(p + i, ios::beg);
		oFile.put('\0');
	}
	oFile.seekp(p, ios::beg);
	cout << "\n" << oFile.tellg() << "\n";
	oFile.write((char*)&iCreditsNew, sizeof(iCreditsNew));
	oFile.close();*/

	system("PAUSE");
}
