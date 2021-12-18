#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct emp
{
	int num = 0; // номер зачетки
	char name[10] = ""; // имя студента
	double grade = 0; // средний бал
};

void showStudents(FILE* bfile, emp wValue) {
	int pos = 0;

	while (!feof(bfile)) {
		fseek(bfile, pos * sizeof(emp), SEEK_SET);
		fread(&wValue, sizeof(emp), 1, bfile);

		if (!feof(bfile)) {
			cout << "Номер зачетки: " << wValue.num << "|Имя студента: " << wValue.name << "|Средний бал: " << wValue.grade << "\n\n";
		}

		pos++;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* bfile = NULL;
	int pos = 0,
		check;
	emp wValue;
	char num[10]; // номер зачетки
	char name[10]; // имя студентаx
	char newGrade[10]; // НОВЫЙ средний бал

	fopen_s(&bfile, ".//file.txt", "r+b");

	if (bfile == NULL) {
		fopen_s(&bfile, ".//file.txt", "wb");
		fclose(bfile);
		fopen_s(&bfile, ".//file.txt", "r+b");
	}

	while (true) {

		showStudents(bfile, wValue);

		cout << "Добавить студента ?\n	1 - да\n	2 - нет\n";
		cin >> check;

		if (check == 1) {
			cout << "---Ввод студентов---\n";

			cout << "Номер зачетки:	";
			cin >> wValue.num;

			cin.get();
			cout << "Имя студента:	";
			gets_s(wValue.name);

			cout << "Средний бал:	";
			cin >> wValue.grade;

			cout << "\n";

			fwrite(&wValue, sizeof(emp), 1, bfile);
		}
		else {
			break;
		}
	}

	fclose(bfile);

	cout << "---Обновление ср.оценки студента---\n";

	cout << "Номер зачетки:	";
	cin.get();
	gets_s(num);

	cout << "Имя студента:	";
	gets_s(name);

	cout << "Средний бал:	";
	gets_s(newGrade);

	cout << "\n";

	char lpszCommandLine[256];
	sprintf_s(lpszCommandLine, "E:\\Microsoft Visual Studio\\Project\\VolkovLab3Child\\Debug\\VolkovLab3Child.exe %s %s %s", num, name, newGrade);

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	// Запускает дочерний процесс Child, которому как параметр передается командная строка, сформированная в пункте 4.
	if (!CreateProcess(NULL, (LPSTR)lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom))

	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		return 0;
	}


	// Ждет завершения работы процесса Child.	
	WaitForSingleObject(piCom.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	fopen_s(&bfile, ".//file.txt", "r+b");
	showStudents(bfile, wValue);
	fclose(bfile);











	/*

	const int N = 2;
	emp oCredits;
	emp iCredits;
	emp iCreditsNew;
	emp iCreditsOld;
	char num[10]; // номер зачетки
	char name[10]; // имя студента
	char newGrade[10]; // средний бал

	showStudents();

	// 1. Создает бинарный файл, записи которого имеют следующую структуру
	ofstream oFile(".\\file.txt", ios::binary | ios::app);
	while (true) {
		cout << "Добавить студента ?\n	1 - да\n	2 - нет\n";
		cin >> check;
		if (check == 1) {
			cout << "---Ввод студентов---\n";
			cout << "Номер зачетки:	";
			cin >> oCredits.num;
			cin.get();
			cout << "Имя студента:	";
			gets_s(oCredits.name);
			cout << "Средний бал:	";
			cin >> oCredits.grade;
			cout << "\n";
			oFile.write((char*)&oCredits, sizeof(oCredits));
		}
		else {
			break;
		}
	}
	oFile.close();

	// 2. Выводит созданный файл на консоль
	showStudents();


	// 3. Запрашивает с консоли номер зачетки, имя студента и новый средний бал этого студента
	cout << "---Обновление ср.оценки студента---\n";
	cout << "Номер зачетки:	";
	cin.get();
	gets_s(num);
	cout << "Имя студента:	";
	gets_s(name);
	cout << "Средний бал:	";
	gets_s(newGrade);
	cout << "\n";
	 
	// 4. Формирует командную строку, которая содержит имя созданного файла и информацию, полученную в пункте 3
	char lpszCommandLine[256];
	sprintf_s(lpszCommandLine, "E:\\Microsoft Visual Studio\\Project\\VolkovLab3Child\\Debug\\VolkovLab3Child.exe %s %s %s", num, name, newGrade);

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);


	// 5. Запускает дочерний процесс Child, которому как параметр передается командная строка, сформированная в пункте 4.
	if (!CreateProcess(NULL, (LPSTR)lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom))

	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		return 0;
	}


	// 6. Ждет завершения работы процесса Child.	
	WaitForSingleObject(piCom.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);


	// 7. Выводит откорректированный файл на консоль.
	showStudents();

	// 8. Завершает свою работу.*/
	return 0;
}