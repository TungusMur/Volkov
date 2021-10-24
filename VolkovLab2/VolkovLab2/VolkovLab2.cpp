#include <iostream>
#include <vector>
#include <limits>
#include <Windows.h>

using namespace std;

volatile int maxM = INT_MIN,
			 minM = INT_MAX;

DWORD WINAPI Worker(vector<int>& mass)
{
	//main #1
	double averageValue = 0;
	for (int n : mass) {
		averageValue += n;
		cout << "\naverageValue_ = " << averageValue << "\n";
		Sleep(100);
	}
	averageValue = (averageValue - maxM) / (mass.size() - 1);
	cout << "\nvariant #10 = " << averageValue << "\n";
	//main #2
	return 0;
}

int main()
{
	//main #1
	int size, 
		number,
		quantity = 0;
	double averageValue = 0;

	vector<int> mass;

	HANDLE hThread;
	DWORD IDThread;

	cout << "size = ";
	cin >> size;
	cout << "\n";

	for (int i = 0; i < size; i++) {
		cout << i + 1 << "# = ";
		cin >> number;
		mass.push_back(number);
	}

	//main #2
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Worker, &mass, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	//main #3
	for (int n : mass) {
		averageValue += n;
		if (maxM < n) {
			maxM = n;
		}
		cout << "\nmax_ = " << maxM << "\n";
		Sleep(100);
		if (minM > n) {
			minM = n;
		}
		cout << "\nmin_ = " << minM << "\n";
		Sleep(100);
	}
	cout << "\nmax = " << maxM << "\nmin = " << minM << "\n";

	//main #4
	WaitForSingleObject(hThread, INFINITE); // ждем пока поток Add закончит работу
	Worker;
	CloseHandle(hThread);// закрываем дескриптор потока

	//main #5
	averageValue = averageValue / mass.size();
	for (int n : mass) {
		if (n > averageValue) {
			quantity++;
		}
	}
	cout << "\nquantity = " << quantity << "\n";

	//main #6
	return 0;
}