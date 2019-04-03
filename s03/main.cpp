#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
	int key{};
	Node *left, *right;
	char nTab[10]{};
};

class BST {

	Node* root;

public:

	//konstruktor
	BST() {
		this->root = NULL;
	}

	//metoda wprowadza podana przez uzytk. liczbe do wezla
	void insert_user_node(const int key);
	//metoda wprowadza x podanych kluczy przez uzytkownika
	void insert_x_nodes(const int amount);
	//metoda sprawdza czy podany klucz jest unikalny
	bool unique_key(const int key);
	//metoda wyszukuje wezel o podanym kluczu
	Node* find_node(const int key);
	//metoda wyswielta drzewo w stylu preorder
	void preorder(Node* node);
	void display_preorder();
	//metoda wyswietla drzewo w stylu inorder
	void inorder(Node* temp_node);
	void display_inorder();
	//metoda wyswietla drzewo w stylu postorder
	void postorder(Node* temp_node);
	void display_postorder();
	//metoda usuwa wezel z drzewa
	void remove_node(const int key);
};

void BST::insert_user_node(const int key) {
	if (unique_key(key) != true) {
		cout << "klucz '" << key << "' juz istnieje!" << endl;
	}
	else {
		Node *local_node = new Node;
		Node *temp_node = new Node;
		local_node->key = key;

		string converted_key = to_string(key);

		for (int i = 0; i < converted_key.size(); i++) {
			local_node->nTab[i] = converted_key[i];
		}
		local_node->nTab[converted_key.size()] = NULL;

		local_node->left = local_node->right = NULL;

		if (this->root == NULL) {
			this->root = local_node;
		}
		else {
			temp_node = this->root;

			while (true) {
				if (local_node->key < temp_node->key) {
					if (temp_node->left != NULL) {
						temp_node = temp_node->left;
					}
					else {
						temp_node->left = local_node;
						break;
					}
				}
				else {
					if (local_node->key == temp_node->key) {
						cout << "Podany klucz '" << local_node->key << "' juz istnieje w drzewie!" << endl;
						break;
					}
					else if (temp_node->right != NULL) {
						temp_node = temp_node->right;
					}
					else {
						temp_node->right = local_node;
						break;
					}
				}
			}
		}
	}
}

void BST::insert_x_nodes(const int amount) {

	int max_amount{ 1000 };//ograniczenie ilosci wezlow
	if (amount < max_amount) {
		int random_key{};
		for (int i = 0; i < amount; i++) {
			do {
				random_key = (rand() % 20001) - 10000;
			} while (unique_key(random_key) != true);

			insert_user_node(random_key);
		}
	}
	else {
		cout << "Podana liczba wezlow musi byc mniejsza niz: " << max_amount << endl;
	}
}

bool BST::unique_key(const int key) {
	if (this->root != NULL) {
		Node *temp_node = new Node;
		temp_node = this->root;

		while (true) {
			if (key < temp_node->key) {
				if (temp_node->left != NULL) {
					temp_node = temp_node->left;  //przechodzenie po drzewie
				}
				else {
					return true;
				}
			}
			else if (key > temp_node->key) {
				if (temp_node->right != NULL) {
					temp_node = temp_node->right;  //przechodzenie po drzewie
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}
		}
	}
	else {
		return true;
	}
}
//METODA ZWRACA PARENT_NODE A NIE TEMP_NODE
Node* BST::find_node(const int key) {
	if (this->root != NULL) {
		
		vector<int> branch;  //do wyswietlenia sciezki do wezla

		Node *temp_node = new Node;
		temp_node = this->root;
		Node *parent_node = new Node;
		
		if (key == this->root->key) {
			branch.push_back(temp_node->key);
			cout << "Podany klucz jest korzeniem drzewa, czyli: " << branch[0] << endl;
			return temp_node;
		}
		else {
			while (true) {
				if (key == temp_node->key) {
					unsigned int size{ branch.size() };
					cout << "Wezel o podanym kluczu znajduje sie na koncu tej galezi:" << endl;
					branch.push_back(temp_node->key);
					for (int i = 0; i < size; i++) {
						cout << branch[i] << " -> ";
					}
					cout << branch[size] << endl;
					return parent_node;
					break;
				}
				else {
					if (key < temp_node->key) {
						if (temp_node->left != NULL) {
							branch.push_back(temp_node->key);  //dodanie klucza do wektora, zeby mozna bylo
							parent_node = temp_node;		   //ponzniej wyswietlic sciezke do szukanego wezla
							temp_node = temp_node->left;
						}
						else {
							cout << "W drzewie nie ma wezla o kluczu: " << key << endl;
							return NULL;
						}
					}
					else {
						if (temp_node->right != NULL) {
							branch.push_back(temp_node->key);
							parent_node = temp_node;
							temp_node = temp_node->right;
						}
						else {
							cout << "W drzewie nie ma wezla o kluczu: " << key << endl;
							return NULL;
						}
					}
				}
			}
		}
		branch.clear();
	}
	else {
		cout << "Drzewo jest puste!" << endl;
	}
}

int counter{};
void BST::preorder(Node* temp_node) {
	if (temp_node != NULL) {
		cout << temp_node->key << " ";
		preorder(temp_node->left);
		preorder(temp_node->right);
		counter++;
	}
}
void BST::display_preorder() {
	preorder(root);
	cout << endl << "#########################"
		<< endl << "Odwiedzono " << counter << " wezlow" << endl;
	counter = 0;
}
void BST::inorder(Node* temp_node) {
	if (temp_node != NULL) {
		inorder(temp_node->left);
		cout << temp_node->key << " ";
		inorder(temp_node->right);
		counter++;
	}
}
void BST::display_inorder() {
	inorder(root);
	cout << endl << "#########################"
		<< endl << "Odwiedzono " << counter << " wezlow" << endl;
	counter = 0;
}
void BST::postorder(Node* temp_node) {
	if (temp_node != NULL) {
		postorder(temp_node->left);
		postorder(temp_node->right);
		cout << temp_node->key << " ";
		counter++;
	}
}
void BST::display_postorder() {
	postorder(root);
	cout << endl << "#########################"
		<< endl << "Odwiedzono " << counter << " wezlow" << endl;
	counter = 0;
}

void BST::remove_node(const int key) {
	streambuf* orig_buf = cout.rdbuf();  //zeby nie wyswietlalo komunikatu dwa razy
	if (this->root != NULL) {
		cout.rdbuf(NULL);  //tutaj blokuje wyswietlanie
		if (find_node(key) != NULL) {
			Node *parent_node = new Node;
			Node *temp_node = new Node;
			Node *local_parent_node = new Node;  //do usuwania w przypadku dwoch potomkow
			
			parent_node = find_node(key);  //find_node zwraca rodzica wyszukanego wezla
			temp_node = parent_node;

			cout.rdbuf(orig_buf);  //tutaj przywraca wyswietlanie
			
			//ustalenie temp_node (zeby zeszlo do odpowiedniego potomka)
			if (key > parent_node->key) {
				temp_node = temp_node->right;

				//jesli wezel nie ma zadnego potomka, to ustawiany jest NULL w rodzicu
				if (temp_node->left == NULL && temp_node->right == NULL) {
					parent_node->right = NULL;
				}
				//jesli wezel ma prawego potomka
				if (temp_node->left == NULL && temp_node->right != NULL) {
					parent_node->right = temp_node->right;
				}
				//jesli wezel ma lewego potomka
				else if (temp_node->left != NULL && temp_node->right == NULL) {
					parent_node->right = temp_node->left;
				}
				//jesli wezel ma dwoch potomkow
				if (temp_node->left != NULL && temp_node->right != NULL) {
					temp_node = parent_node->right->right;
					local_parent_node = temp_node;

					while (true) {
						if (temp_node->left != NULL) {
							local_parent_node = temp_node;
							temp_node = temp_node->left;
						}
						else {
							if (temp_node->right != NULL) {
								local_parent_node->left = temp_node->right;
							}
							temp_node->left = parent_node->right->left;
							temp_node->right = parent_node->right->right;
							parent_node->right = temp_node;
							break;
						}
					}
				}
			}
			//ustalenie temp_node (zeby zeszlo do odpowiedniego potomka)
			else if (key < parent_node->key) {
				temp_node = temp_node->left;

				//jesli wezel nie ma zadnego potomka, to ustawiany jest NULL w rodzicu
				if (temp_node->left == NULL && temp_node->right == NULL) {
					parent_node->left = NULL;
				}
				//jesli wezel ma prawego potomka
				if (temp_node->left == NULL && temp_node->right != NULL) {
					parent_node->left = temp_node->right;
				}
				//jesli wezel ma lewego potomka
				else if (temp_node->left != NULL && temp_node->right == NULL) {
					parent_node->left = temp_node->left;
				}
				//jesli wezel ma dwoch potomkow
				if (temp_node->left != NULL && temp_node->right != NULL) {
					temp_node = parent_node->left->right;
					local_parent_node = temp_node;
					
					while (true) {
						if (temp_node->left != NULL) {
							local_parent_node = temp_node;
							temp_node = temp_node->left;
						}
						else {
							if (temp_node->right != NULL) {
								local_parent_node->left = temp_node->right;
							}
							temp_node->left = parent_node->left->left;
							temp_node->right = parent_node->left->right;
							parent_node->left = temp_node;
							break;
						}
					}
				}
			}
			//jesli usuwany jest korzen drzewa
			else {
				//jesli ma korzen ma dwoch potomkow, to wrzucam nastepnika
				if (this->root->left != NULL && this->root->right != NULL) {
					parent_node = this->root;
					temp_node = this->root->right;
					local_parent_node = temp_node;

					while (true) {
						if (temp_node->left != NULL) {
							local_parent_node = temp_node;
							temp_node = temp_node->left;
						}
						else {
							if (temp_node->right != NULL) {
								local_parent_node->left = temp_node->right;
							}
							//przypisanie lewgo wezla korzenia do nastepnika
							temp_node->left = parent_node->left;
							if (parent_node->right->left == NULL) {
								//przypisanie prawego wezla korzenia do nastepnika
								temp_node->right = parent_node->right;
							}
							else {
								temp_node->right = parent_node->right->right;
							}
							//przypisanie nastepnika jako nowy korzen
							this->root = temp_node;
							break;
						}
					}
				}
				else {
					//jesli korzen  ma tylko prawego potomka
					if (this->root->left == NULL && this->root->right != NULL) {
						this->root = this->root->right;
					}
					//jesli korzen  ma tylko lewego potomka
					else if (this->root->left != NULL && this->root->right == NULL) {
						this->root = this->root->left;
					}
				}
			}
			cout << "Klucz '" << key << "' zostal usuniety." << endl;
		}
	}
	else {
		cout << "Drzewo jest puste!" << endl << endl;
	}
}

//funkcja czyta z pliku
int read_from_file(int &amount, int *list) {

	ifstream file;
	file.open("inlab03.txt");
	if (!file.is_open()) {
		cout << "Brak pliku" << endl;
		return -5;
	}
	else {
		file >> amount;
		for (int i = 0; i < 5; i++)
			file >> list[i];
		file.close();
	}
	return 0;
}

int main() {

	srand(time(NULL));

	clock_t begin, end;
	double time_spent;

	int amount{}, list[4]{};

	begin = clock();
	read_from_file(amount, list);

	BST Tree;

	Tree.remove_node(list[0]);
	Tree.insert_user_node(list[0]);
	Tree.insert_x_nodes(amount);
	Tree.display_inorder();
	cout << endl << endl;
	Tree.display_preorder();
	Tree.insert_user_node(list[1]);
	cout << endl << endl;
	Tree.display_inorder();
	Tree.insert_user_node(list[2]);
	Tree.insert_user_node(list[3]);
	cout << endl << endl;
	Tree.remove_node(list[0]);
	cout << endl;
	Tree.display_preorder();
	cout << endl << endl;
	Tree.find_node(list[0]);
	cout << endl;
	Tree.remove_node(list[1]);
	Tree.display_inorder();
	cout << endl << endl;
	Tree.remove_node(list[2]);
	cout << endl;
	Tree.remove_node(list[3]);
	cout << endl;
	Tree.display_preorder();

	cout << endl << endl;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "Czas wykonania programu: " << time_spent << " sekund" << endl;

	return 0;
}
