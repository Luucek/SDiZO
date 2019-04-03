#define _WIN32_WINNT 0x0502
#include<windows.h>
//powyzej potrzebne do zmiany wielkosci okna
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int global_table_size = 1000;  //rozmiar tablicy

class HashTable {
	int *table;

public:
	//inicjacja pustej tablicy przez konstruktor
	HashTable() {
		this->table = new int[global_table_size];
		for (int i = 0; i < global_table_size; i++) {
			this->table[i] = 0;
		}
	}
	void display_table();
	int power(int base, int index);
	int hash(int key);
	int hash_helper(int key);
	bool insert_key(int key, int method);
	void insert_x_keys(int amount, int method);
	bool unique_key(int key);
	int find_key(int key);
	void display_block(int st, int en);
	bool remove_key(int key);
};
//metoda wyswietla cala tablice
void HashTable::display_table() {
	stringstream ss;
	for (int i = 0; i < global_table_size; i++) {
		if (this->table[i] > 0) {
			ss << "Color 0" << i % 10;
			string s = ss.str();
			char *cstr = new char[s.length() + 1];
			strcpy_s(cstr, s.length()+1, s.c_str());
			system(cstr);
			cout << "[" << i << "]: "
				<< this->table[i] << "\t";
			delete[] cstr;
			ss.str(std::string());
		}
	}
}
//metoda potegujaca
int HashTable::power(int base, int index) {
	int result{ 1 };

	for (int i = 0; i < index; i++) {
		result *= base;
	}

	return result;
}
//metoda hashujaca
int HashTable::hash(int key) {
	return (key % 1000 + (power(2, key % 10) + 1)) % 977;
}
int HashTable::hash_helper(int key) {
	return ((3 * key) % 19) + 1;
}
//metoda wstawiajaca klucz
bool HashTable::insert_key(int key, int method) {

	int temp_index = hash(key);
	int temp_index_old = temp_index;  //potrzebne zeby wyjsc z petli
	int full_circle{};
	
	if (this->table[temp_index] <= 0) {

		this->table[temp_index] = key;
		return true;
	}
	else {
		//metoda liniowa
		if (method == 1) {
			while (this->table[temp_index] > 0) {
				if (temp_index == 0) {
					temp_index = global_table_size - 1;
					full_circle++;
				}
				if (full_circle != 0 && temp_index_old == temp_index) {
					cout << "Osiagnieto maksymalna wielkosc tablicy!" << endl;
					break;
				}
				temp_index--;
			}

			this->table[temp_index] = key;
			return true;
		}
		//metoda mieszania podwojnego
		else {
			temp_index = hash_helper(key);
			while (this->table[temp_index_old] > 0) {
				temp_index_old += temp_index;
			}
			this->table[temp_index_old] = key;
		}
	}
	return false;
}
//metoda wstawiajaca x kluczy
void HashTable::insert_x_keys(int amount, int method) {
	if (amount < global_table_size) {
		int random_key{};
		for (int i = 0; i < amount; i++) {
			//generowanie unikalnego klucza
			do {
				random_key = (rand() % 20001) + 20000;
			} while (unique_key(random_key) != true);
			insert_key(random_key, method);
		}
	}
	else {
		cout << "Podana liczba musi byc mniejsza niz "<< global_table_size << "!" << endl;
	}
}
//metoda sprawdzajaca unikalnosc klucza
bool HashTable::unique_key(int key) {
	for (int i = 0; i < global_table_size; i++) {
		if (key == this->table[i]) {
			return false;
		}
		else {
			return true;
		}
	}
}
//metoda zwraca numer indexu wyszukiwanego klucza
int HashTable::find_key(int key) {
	int temp_index = hash(key);
	if (this->table[temp_index] == key) {
		return temp_index;
	}
	else {
		for (int i = 0; i < global_table_size; i++) {
			if (this->table[temp_index] == key) {
				return temp_index;  //zwraca index pod ktorym znajduje sie poszukiwany klucz
			}
			else {
				temp_index--;
				if (temp_index == 0) {
					temp_index = global_table_size - 1;
				}
			}
		}
	}
	return -2;  //nie znaleziono podanego klucza
}
//metoda wyswietla okreslona czesc tablicy
void HashTable::display_block(int st, int en) {
	for (int i = st; i <= en; i++) {
		if (this->table[i] <= 0) {
			cout << "[" << i << "]: "
				<< this->table[i] << "  \t";
		}
		else {
			cout << "[" << i << "]: "
				<< this->table[i] << "\t";
		}
		if (i % 10 == 9) {
			cout << endl;
		}
	}
}
//metoda usuwa podany klucz
bool HashTable::remove_key(int key) {
	int key_index = find_key(key);
	
	if (key_index != -2) {
		this->table[key_index] = -1;
	}
	else {
		cout << "Klucz " << key << " nie znajduje sie w tablicy!" << endl << endl;
		return false;  //nie znaleziono podanego klucza
	}				   //wyswietlic stosowny komunikat
}
//funkcja czyta z pliku
int read_from_file(int &amount, int *list) {

	ifstream file;
	file.open("inlab06.txt");
	if (!file.is_open()) {
		cout << "Brak pliku" << endl;
		return -5;
	}
	else {
		file >> amount;
		for (int i = 0; i < 4; i++)
			file >> list[i];
		file.close();
	}
	return 0;
}

int main() {

	//zmiana wielkosci okna
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 1350, 600, SWP_SHOWWINDOW | SWP_NOMOVE); }

	srand(time(NULL));

	int inserting_method{};
	while (true) {
		system("cls");
		cout << "Wybierz metode wstawiania kluczy do tablicy:" << endl
			<< "1 - metoda liniowa" << endl
			<< "2 - metoda 'Klasycznego' mieszania podwojnego" << endl;
		cin >> inserting_method;
		if (inserting_method == 1 || inserting_method == 2) {
			break;
		}
	}
	if (inserting_method == 1) {
		system("cls");
		cout << "###########################" << endl
			<< "      METODA LINIOWA" << endl
			<< "###########################" << endl << endl;
	}
	else if (inserting_method == 2) {
		system("cls");
		cout << "###########################" << endl
			<< "     METODA MIESZANIA" << endl
			<< "###########################" << endl << endl;
	}
		clock_t begin, end;
		double time_spent;

		int amount{}, list[4]{};

		begin = clock();
		read_from_file(amount, list);
		//START
		HashTable Table;
		Table.remove_key(list[0]);
		Table.insert_key(list[0], inserting_method);
		Table.display_block(0, 100);
		Table.insert_x_keys(amount, inserting_method);
		cout << endl << endl;
		Table.display_block(0, 100);
		Table.insert_key(list[1], inserting_method);
		Table.insert_key(list[2], inserting_method);
		Table.insert_key(list[3], inserting_method);
		cout << endl << endl;
		Table.display_block(0, 100);
		cout << endl << endl;
		Table.display_block(500, 600);
		Table.remove_key(list[3]);
		Table.remove_key(list[2]);
		cout << endl << endl;
		Table.display_block(0, 100);
		cout << endl << endl;
		Table.display_block(500, 600);
		//KONIEC
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		cout << endl << "Czas wykonania programu: " << time_spent << " sekund" << endl;
	
	system("PAUSE");
	return 0;
}