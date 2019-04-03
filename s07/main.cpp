#include <iostream>
#include <set>
#include <ctime>
#include <fstream>

std::set<int> MyStructure;  //cale drzewo

int unsigned globalKeyCounter{};   //globalny licznik ilosci kluczy

//funkcja wpisuje klucz do drzewa
bool InsertKey(const int& key) {
    if (MyStructure.insert(key).second) {
        globalKeyCounter++;
        return true;
    }
    else {
        return false;   //konczy dzialanie funkcji zeby nie inkrementowac KeyCounter
    }                   //w momencie kiedy podany klucz jest juz wczesniej wpisany
}
//funkcja czyta z pliku
int ReadFileKey(std::ifstream& file) {
    int key{};
    if (!file.is_open()) {
        std::cout << "Brak pliku" << std::endl;
        return -5;
    }
    else {
        file >> key;
        return key;
    }
}
//funkcja wyszukuje klucz
void FindKey(const int& key) {
    //TODO? zamienic uzywanie globalnego key countera na uzywanie
    //      metod klas dzialajacych na ciele klasy

    std::set< int >::iterator it = MyStructure.find(key);
    if (it != MyStructure.end()) {
        globalKeyCounter++;
    }
    else {
        //TODO? jak nie znaleziono
    }
    if (globalKeyCounter > MyStructure.size()) {
        globalKeyCounter = MyStructure.size();
    }
}
//funkcja usuwa podany klucz
void RemoveKey(const int& key) {
    std::set< int >::iterator it = MyStructure.find(key);
    if (it != MyStructure.end()) {
        MyStructure.erase(key);
        globalKeyCounter++;
    }
}

int main() {

    srand(time(NULL));

    int keyAmount{},    //uzytkownik podaje ile chce wpisac kluczy do drzewa
        key{}, randomKey{};  //odpowiednio klucze do wpisania

    std::cout << "Podaj ilosc kluczy:" << std::endl;
    std::cin >> keyAmount;
    std::cout << std::endl;
    
    clock_t begin, end;
    double time_spent;

    {//2.
        std::cout << "2.----------------------------------" << std::endl;
        begin = clock();
        std::ifstream file;
        file.open("rand.txt");
        for (int i = 0; i < keyAmount; i++) {
            InsertKey(ReadFileKey(file));
        }
        file.close();   //zamyka plik po wczytaniu
        std::cout << "Ilosc wstawionych kluczy: "
            << globalKeyCounter << std::endl;;
        globalKeyCounter = 0;

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << "Czas wstawiania kluczy: " << time_spent << " sekund" << std::endl;
    }
    {//3.
        std::cout << "3.----------------------------------" << std::endl;
        begin = clock();
        std::ifstream file;
        file.open("rand.txt");
        for (int i = 0; i < keyAmount; i++) {
            FindKey(ReadFileKey(file));
        }
        file.close();   //zamyka plik po wczytaniu
        std::cout << "Ilosc wyszukanych kluczy: "
            << globalKeyCounter << std::endl;;
        globalKeyCounter = 0;

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << "Czas wyszukiwania kluczy: " << time_spent << " sekund" << std::endl;
    }
    {//4.
        std::cout << "4.----------------------------------" << std::endl;
        begin = clock();
        std::ifstream file;
        for (int i = 0; i < keyAmount; i++) {
            randomKey = rand() % 10000000;
            FindKey(randomKey);
        }
        file.close();   //zamyka plik po wczytaniu
        std::cout << "Ilosc wyszukanych kluczy: "
            << globalKeyCounter << std::endl;;
        globalKeyCounter = 0;

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << "Czas wyszukiwania kluczy: " << time_spent << " sekund" << std::endl;
    }
    {//5.
        std::cout << "5.----------------------------------" << std::endl;
        begin = clock();
        std::ifstream file;
        for (int i = 0; i < keyAmount; i++) {
            randomKey = rand() % 10000000;
            RemoveKey(randomKey);
        }
        file.close();   //zamyka plik po wczytaniu
        std::cout << "Ilosc usunietych kluczy: "
            << globalKeyCounter << std::endl;;
        globalKeyCounter = 0;

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << "Czas usuwania kluczy: " << time_spent << " sekund" << std::endl;
    }
    {//6.
        std::cout << "6.----------------------------------" << std::endl;
        begin = clock();
        std::ifstream file;
        file.open("rand.txt");
        for (int i = 0; i < keyAmount/2; i++) {
            RemoveKey(ReadFileKey(file));
        }
        file.close();   //zamyka plik po wczytaniu
        std::cout << "Ilosc usunietych kluczy: "
            << globalKeyCounter << std::endl;;
        globalKeyCounter = 0;

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << "Czas usuwania kluczy: " << time_spent << " sekund" << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }

	system("pause");
	return 1;
}
