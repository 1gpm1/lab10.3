#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

void createFile(string& filename) {
	ofstream outfile(filename);

	outfile << "Milk\t\tSilpo\t\t26.99\t\t1\t\tL" << endl;
	outfile << "Bread\t\tATB\t\t9.99\t\t2\t\tpcs" << endl;
	outfile << "Chicken\t\tMetro\t\t89.50\t\t1\t\tkg" << endl;
	outfile << "Apples\t\tFurshet\t\t16.50\t\t3\t\tkg" << endl;
	outfile << "Coca-Cola\tAuchan\t\t19.99\t\t2\t\tL" << endl;

	outfile.close();

	cout << "Продукти були успішно додані до списку";
}

void AddProduct(const string& filename) {

	ofstream outfile(filename, ios::app);

	if (!outfile.is_open())
	{
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	string name, shop, units;
	double price;
	int quantity;

	cout << "Введіть назву товару: ";
	getline(cin, name);

	cout << "Введіть назву магазину: ";
	getline(cin, shop);

	cout << "Введіть ціну товару в гривнях: ";
	cin >> price;


	cout << "Введіть кількість товару: ";
	cin >> quantity;


	cout << "Введіть одиниці вимірювання: ";
	cin >> units;
	cin.ignore();

	cout << endl;


	outfile << name << " " << shop << " " << price << " " << quantity << " " << units << endl;

	outfile.close();
}

void Print(const string& filename) {

	ifstream infile(filename);

	if (!infile.is_open())
	{
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	cout << "=================================================================" << endl;
	cout << "|  №  |  Назва товару  |     Магазин     |  Ціна  |  Кількість  |" << endl;
	cout << "-----------------------------------------------------------------" << endl;

	int i = 1;
	string name, shop, units;
	double price;
	int quantity;

	while (infile >> name >> shop >> price >> quantity >> units)
	{
		cout << "| " << setw(3) << right << i << " ";

		cout << "| " << setw(15) << left << name
			<< "| " << setw(16) << left << shop
			<< "| " << setw(7) << left << price
			<< "| " << setw(3) << left << quantity << setw(8) << left << units
			<< " |" << endl;
		i++;
	}

	cout << "=================================================================" << endl;

	infile.close();
}

void DisplayShopProducts(const string& filename) {
	string shopName;
	cout << "Введіть назву магазину: ";
	cin >> shopName;

	ifstream infile(filename);

	if (!infile.is_open()) {
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	string name, shop, units;
	double price;
	int quantity;
	bool found = false;

	cout << "Продукти, які продаються в магазині " << shopName << ":" << endl << endl;

	while (infile >> name >> shop >> price >> quantity >> units) {
		if (shop == shopName) {
			found = true;
			cout << name << " - " << price << " грн за " << quantity << " " << units << endl << endl;
		}
	}

	if (!found) {
		cout << "Товари для магазину " << shopName << " не знайдені!" << endl;
	}

	infile.close();
}

void DisplayByPriceRange(const string& filename)
{
	double lower_bound, upper_bound;

	ifstream infile(filename);

	if (!infile.is_open()) {
		cout << "Помилка відкриття файлу!" << endl;
		return;
	}

	cout << "Введіть нижню межу цінового діапазону: ";
	cin >> lower_bound;

	cout << "Введіть верхню межу цінового діапазону: ";
	cin >> upper_bound;

	cout << "=================================================================" << endl;
	cout << "|  №  |  Назва товару  |     Магазин     |  Ціна  |  Кількість  |" << endl;
	cout << "-----------------------------------------------------------------" << endl;

	string name, shop, units;
	double price;
	int quantity, i = 1;

	while (infile >> name >> shop >> price >> quantity >> units)
	{
		if (price >= lower_bound && price <= upper_bound)
		{
			cout << "| " << setw(3) << right << i << " ";

			cout << "| " << setw(15) << left << name
				<< "| " << setw(16) << left << shop
				<< "| " << setw(7) << left << price
				<< "| " << setw(3) << left << quantity << setw(8) << left << units
				<< " |" << endl;
			i++;
		}
	}

	infile.close();
	cout << "================================================================="
		<< endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string fileName;

	cout << "Введіть ім'я файлу: ";
	cin >> fileName;
	cin.ignore();

	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - створення продутків" << endl;
		cout << " [2] - вивід данних" << endl;
		cout << " [3] - додати продукт" << endl;
		cout << " [4] - вивести список товарів в конкретному магазині" << endl;
		cout << " [5] - вивести список в діапазоні цін" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			createFile(fileName);
			break;
		case 2:
			Print(fileName);
			break;
		case 3:
			int N;
			bool ch;

			do {
				cout << "Скільки товарів потрібно створити?: ";
				cin >> N;
				cin.ignore();

				if (N > 0) {
					ch = true;
				}
				else {
					cout << "Кількість не має бути менше нуля." << endl;
					ch = false;
				}

			} while (!ch);


			for (int i = 0; i < N; i++) {
				AddProduct(fileName);
			}
			break;
		case 4:
			DisplayShopProducts(fileName);
			break;
		case 5:
			DisplayByPriceRange(fileName);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	return 0;
}