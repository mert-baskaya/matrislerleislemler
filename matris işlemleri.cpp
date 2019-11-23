#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*Fonksiyon prototip tanımları*/
void printMatrix(int**, int);
void reverse(int**, int, int);
void changeLineWithCol(int**, int, int, int);
void sort(int**, int, int);
void sum(int**, int);
void swap(int*, int*);
void printMenu(int**, int);

int main()
{
	srand(time(NULL));
	int size;
	bool endLoop;
	/*Kullanıcıdan matris boyutunu alıp kontrol ediyor*/
	do {
		cout << "Matris Boyutu: ";
		cin >> size;
		if (size < 5 || size > 25) {
			cout << "matris boyutu 25'den kucuk 5'den buyuk olmalidir!\n";
			endLoop = false;
		}
		else endLoop = true;
	} while (!endLoop);

	/*2 boyutlu pointer dizisi heap'ta allocate ediliyor*/
	int** array = new int* [size];
	for (int i = 0; i < size; i++) array[i] = new int[size];

	/*Diziyi 0'dan 9'a kadar rastgele sayılarla dolduruyor*/
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = rand() % 9 + 1;
		}
	}

	printMenu(array, size);

	/*Çöp veriyi siliyor*/
	for (int i = 0; i < size; i++) delete array[i];
	delete[] array;

	system("pause");
	return 0;
}

void printMatrix(int** array, int size) {
	/*Matrisi bastırmak için gerekli döngüler*/
	cout << "        ";

	for (int i = 1; i <= size; i++) {
		if (i < 9) cout << i << "   ";
		else cout << i << "  ";
	}
	cout << "\n";
	cout << "      ";

	for (int i = 1; i <= size; i++) {
		cout << "____";
	}
	cout << "\n\n";

	for (int i = 0; i < size; i++) {
		if (i < 9) cout << "  " << i + 1 << "  |";
		else cout << " " << i + 1 << "  |";
		for (int j = 0; j < size; j++) {
			if (array[i][j] < 10) cout << "  " << array[i][j] << " ";
			else if (array[i][j] < 100) cout << " " << array[i][j] << " ";
			else cout << array[i][j] << " ";
		}
		cout << "\n\n";
	}
}

void printMenu(int** array, int size) {

	printMatrix(array, size);

	cout << "1.Sutun Satir Degistir\n";
	cout << "2.Tekleri Basa Al(Satir)\n";
	cout << "3.Ters Cevir(Sutun)\n";
	cout << "4.ToplamlariYazdir\n";
	int choice;
	cin >> choice;
	int line;
	int column;
	/*Kullanıcı girişleri isteniyor*/
	switch (choice)
	{
	case 1:
		cout << "satir bosluk sutun :";
		cin >> line >> column;
		if (line > size || line == 0 || column > size || column == 0) {
			cout << "satir ve sutun sayisi matris boyutundan buyuk olamaz\n";
			printMenu(array, size);
		}
		else {
			changeLineWithCol(array, size, line - 1, column - 1);
			printMatrix(array, size);
		}
		break;
	case 2:
		cout << "Satir numarasi..:";
		cin >> line;
		if (line > size || line == 0) {
			cout << "satir sayisi matris boyutundan buyuk olamaz\n";
			printMenu(array, size);
		}
		else {
			sort(array, size, line - 1);
			printMatrix(array, size);
		}
		break;
	case 3:
		cout << "Sutun numarasi..:";
		cin >> column;
		if (column > size || column == 0) {
			cout << "sutun sayisi matris boyutundan fazla olamaz\n";
			printMenu(array, size);
		}
		else {
			reverse(array, size, column - 1);
			printMatrix(array, size);
		}
		break;
	case 4:
		sum(array, size);
		printMatrix(array, size);
		break;
	default:
		break;
	}
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverse(int** array, int size, int col) {

	int* temp = new int[size];

	/*Sütundaki sayıları geçici diziye atıyor*/
	for (int i = 0; i < size; i++) {
		temp[i] = array[i][col];
	}

	/*Geçici dizideki sayıları ters olarak ana diziye atıyor*/
	for (int i = 0; i < size; i++) {
		array[i][col] = temp[size - 1 - i];
	}

	delete[] temp;
}

void changeLineWithCol(int** array, int size, int l, int c) {

	int* line = new int[size];
	int* column = new int[size];

	/*Sütün için açılan geçici diziye istenen sütundaki elemanları atıyor*/
	for (int i = 0; i < size; i++) {
		column[i] = array[i][c];
	}

	/*Satır için açılan geçici diziye istenen satırdaki elemanları atıyor*/
	for (int j = 0; j < size; j++) {
		line[j] = array[l][j];
	}

	/*Satırı sütuna atıyor*/
	for (int i = 0; i < size; i++) {
		array[i][c] = line[i];
	}

	/*Sütunu satıra atıyor*/
	for (int j = 0; j < size; j++) {
		array[l][j] = column[j];
	}

	/*Kesişen sayıları toplayıp atamasını yapıyor*/
	array[l][c] = array[0][c] + array[l][l];

	delete[] line;
	delete[] column;
}

void sort(int** array, int size, int line) {

	int* temp = new int[size];

	/*Satırdaki elemanları geçiçi diziye kopyalıyor*/
	for (int j = 0; j < size; j++) {
		temp[j] = array[line][j];
	}

	/*Sayıların tek mi çift mi olduğunu kontrol edip geçiçi dizi üzerinde sıralama yapıyor*/
	int left = 0, right = size - 1;
	while (left < right)
	{

		while (temp[left] % 2 == 1 && left < right)
			left++;


		while (temp[right] % 2 == 0 && left < right)
			right--;

		if (left < right)
		{
			swap(&temp[left], &temp[right]);
			left++;
			right--;
		}
	}

	/*Uygun şekilde sıralanmış sayıları geçiçi diziden ana diziye atıyor*/
	for (int j = 0; j < size; j++) {
		array[line][j] = temp[j];
	}

	delete[] temp;
}

void sum(int** array, int size) {

	int sum = 0;

	/*Dizideki sayıları topluyor*/
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum += array[i][j];
		}
	}
	/*Toplamdan elemanları çıkartarak diziyi dolaşıyor*/
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = sum - array[i][j];
			sum = array[i][j];
		}
	}
}