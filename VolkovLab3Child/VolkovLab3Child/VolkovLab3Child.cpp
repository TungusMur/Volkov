#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
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

	cout << "Номер зачетки: " << argv[1] << "|Имя студента: " << argv[2] << "|Средний бал: " << argv[3] << "\n\n";

	const int N = 2;
	emp iCreditsNew;
	vector <emp> CreditsNew;
	char num[255];

	ifstream iFile("E:\\Microsoft Visual Studio\\Project\\VolkovLab3\\VolkovLab3\\file.txt", ios::binary);
	while (iFile.peek() != EOF) {
		iFile.read((char*)&iCreditsNew, sizeof(iCreditsNew));
		sprintf_s(num, "%d", iCreditsNew.num);

		if ((strcmp(iCreditsNew.name, argv[2]) == 0) && (strcmp(num, argv[1]) == 0)) {
			sscanf_s(argv[3], "%lf", &iCreditsNew.grade);
		}
		CreditsNew.push_back(iCreditsNew);
	}
	iFile.close();


	ofstream oFile(".\\file.txt", ios::binary);
	for (emp item : CreditsNew) {
		oFile.write((char*)&item, sizeof(item));
	}
	oFile.close();

	system("PAUSE");
}
