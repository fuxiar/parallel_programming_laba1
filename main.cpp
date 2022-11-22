#define SIZE 100
#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

void CreateMatrix(const char* path, int rows, int columns) {
	ofstream fprint;
	fprint.open(path);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			int tmp = rand() % 100;
			fprint << setw(5) << tmp;
		}
		fprint << endl;
	}
	fprint.close();
}

int** ReadMatrix(const char* path, int rows, int columns) {
	ifstream M;
	M.open(path, ios_base::in);
	int** m = new int* [rows];
	for (size_t i = 0; i < rows; i++) {
		m[i] = new int[columns];
		for (size_t j = 0; j < columns; j++) {
			M >> m[i][j];
		}
	}
	return m;
}

int main() {

	srand(time(NULL));
	int r1 = SIZE, c1 = SIZE;
	int r2 = SIZE, c2 = SIZE;

	const char* path1 = "C:\\Games\\Parallel\\Lab1\\matrix1.txt";
	const char* path2 = "C:\\Games\\Parallel\\Lab1\\matrix2.txt";

	CreateMatrix(path1, r1, c1);
	CreateMatrix(path2, r2, c2);

	int** m1 = ReadMatrix(path1, r1, c1);
	int** m2 = ReadMatrix(path2, r2, c2);


	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	int** result = new int* [r1];
	for (int i = 0; i < r1; i++) {
		result[i] = new int[c2];
		for (int j = 0; j < c2; j++) {
			result[i][j] = 0;
			for (int k = 0; k < c1; k++)
				result[i][j] += m1[i][k] * m2[k][j];
		}
	}
	chrono::steady_clock::time_point end = chrono::steady_clock::now();


	cout << "Multiplication:" << endl;
	double mulTime = chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	cout << "Time(ms) = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

	ofstream R;
	R.open("C:\\Games\\Parallel\\Lab1\\result.txt");

	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			R << setw(8) << result[i][j];
		}
		R << endl;
	}

	ofstream measurements;

	measurements.open("C:\\Games\\Parallel\\Lab1\\measurements.txt", ios::app);
	measurements << SIZE << "\t" << mulTime << endl;
	measurements.close();

	return 0;
}
