#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;


struct NAME
{
	string surname, name, patronymic;
};

struct DATABIRTH
{
	int day, month, year;
};

struct GROUP_SES
{
	int GROUP;
	string SES;
};

struct STUDENT
{
	DATABIRTH Birth;
	NAME Name;
	GROUP_SES group_ses;
};

void DataEntry(STUDENT* (&d), int& n);//Ввід данних вручну
void ReadingData(STUDENT* (&d), int& n, string fileName);//Читання данних з файлу
void Print(STUDENT* d, int n);//Вивід данних
void DataChange(STUDENT* (&d), int n);//Зміна данних
void DeleteData(STUDENT* (&d), int& n);//Видалення данних 
void Copy(STUDENT* (&d_n), STUDENT* (&d_o), int n);//Копія данних
void Copy(STUDENT& d_n, STUDENT& d_o);//Копія данних елемента
void AddData(STUDENT* (&d), int& n);//Додати данні
void DataSorting(STUDENT* d, int n);//Сортувати дані
void SavingData(STUDENT* d, int n, string fileName);// Зберегти дані

int _stateMenu;

void Menu()
{
	cout << "Виберіть дію: " << '\n'
		<< "(0) Вихід з програми: " << '\n'
		<< "(1) Ввід нанних: " << '\n'
		<< "(2) Вивід данних: " << '\n'
		<< "(3) Зміна данних: " << '\n'
		<< "(4) Видалення данних: " << '\n'
		<< "(5) Додавання данних: " << '\n'
		<< "(6) Сортування данних: " << '\n'
		<< "(7) Збереження данних: " << '\n'
		<< "Ваш вибір: ";
	cin >> _stateMenu;
}

int main()
{
	SetConsoleCP(1251); //Робимо можливим вивід кирилиці на екран
	SetConsoleOutputCP(1251);

	Menu();

	int _actions, amountOfData = 0;// Ініціалізацію данних
	string fileName;
	//Масив данних
	STUDENT* d = new STUDENT[amountOfData];

	while (_stateMenu != 0)
	{
		switch (_stateMenu)
		{
		case 1:
		{
			system("cls"); //очистка кoнсолі

			cout << "Ввід вручну чи з файлу?\n\t1 = вручну\n\tБудь яке інше число з файлу\n";
			cin >> _actions;

			system("cls"); //очистка кoнсолі

			if (_actions == 1)//Ввід вручну
			{
				DataEntry(d, amountOfData);
			}
			else // Ввід з файлу
			{
				ReadingData(d, amountOfData, "Input.txt");
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 2:
		{
			system("cls"); //очистка кoнсолі

			if (amountOfData != 0)
			{
				Print(d, amountOfData);
			}
			else
			{
				cout << "Данних немає" << '\n';
			}
			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 3:
		{
			system("cls"); //очистка кoнсолі

			if (amountOfData != 0)
			{
				DataChange(d, amountOfData);
			}
			else
			{
				cout << "Данних немає" << '\n';
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 4:
		{
			system("cls"); //очистка кoнсолі

			if (amountOfData != 0)
			{
				DeleteData(d, amountOfData);
			}
			else
			{
				cout << "Данних немає" << '\n';
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 5:
		{
			system("cls"); //очистка кoнсолі

			if (amountOfData != 0)
			{
				AddData(d, amountOfData);
				amountOfData++;
			}
			else
			{
				cout << "Данних немає" << '\n';
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 6:
		{
			system("cls"); //очистка кoнсолі

			if (amountOfData != 0)
			{
				DataSorting(d, amountOfData);
			}
			else
			{
				cout << "Данних немає" << '\n';
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		case 7:
		{
			system("cls"); //очистка кoнсолі

			cout << "Введіть назву файла: ";
			cin >> fileName;

			if (amountOfData != 0)
			{
				SavingData(d, amountOfData, fileName);
			}
			else
			{
				cout << "Данних немає" << '\n';
			}

			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		default:
		{
			cout << "Неправильно введений номер дії" << '\n';
			system("pause");
			system("cls"); //очистка кoнсолі
			Menu();
			break;
		}
		}
	}
}
void DataEntry(STUDENT* (&d), int& n) // коли передаємо силку то функція не передає окремі дані а працює з первинними даними
{
	cout << "Введіть кількість данних: ";
	cin >> n;

	d = new STUDENT[n];
	for (size_t i = 0; i < n; i++)
	{
		cout << "Введіть прізвище, ім'я, по-батькові: ";
		cin >> d[i].Name.surname;
		cin >> d[i].Name.name;
		cin >> d[i].Name.patronymic;

		cout << "Введіть дату народження (день місяць рік): ";
		cin >> d[i].Birth.day;
		cin >> d[i].Birth.month;
		cin >> d[i].Birth.year;

		cout << "Введіть номер групи: ";
		cin >> d[i].group_ses.GROUP;

		cout << "Введіть Успішність з 5-ти предметів !БЕЗ ПРОБІЛІ В ПОРЯДКУ ЗРОСТАННЯ!: ";
		cin >> d[i].group_ses.SES;

		cout << "_______________________" << '\n';
	}
}
void ReadingData(STUDENT* (&d), int& n, string fileName)
{
	ifstream reading(fileName);
	if (reading)
	{
		reading >> n;

		d = new STUDENT[n]; //Виділяєм память

		for (size_t i = 0; i < n; i++)
		{
			reading >> d[i].Name.surname;
			reading >> d[i].Name.name;
			reading >> d[i].Name.patronymic;

			reading >> d[i].Birth.day;
			reading >> d[i].Birth.month;
			reading >> d[i].Birth.year;

			reading >> d[i].group_ses.GROUP;

			reading >> d[i].group_ses.SES;
		}

		cout << "Данні зчитані" << '\n';
	}
	else
	{
		cout << "Помилка відкриття файлу" << '\n';
	}
	reading.close();
}
void Print(STUDENT* d, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << "Данні №" << i + 1 << ':' << '\n';

		cout << "Прізвище, ім'я, по - батькові: " << d[i].Name.surname << ' ' << d[i].Name.name << ' ' << d[i].Name.patronymic << '\n';
		cout << "Дата народження: " << d[i].Birth.day << ' ' << d[i].Birth.month << ' ' << d[i].Birth.year << '\n';
		cout << "Номер групи: " << d[i].group_ses.GROUP << '\n';
		cout << "Успішність з 5-ти предметів !БЕЗ ПРОБІЛІ В ПОРЯДКУ ЗРОСТАННЯ!: " << d[i].group_ses.SES << '\n';


		cout << "_______________________" << '\n';
	}
}
void DataChange(STUDENT* (&d), int n)
{
	int _n;
	cout << "Введіть номер єлемента (від 1 до " << n << "): ";
	cin >> _n;
	_n--;

	system("cls"); //очистка кoнсолі

	// Перевірки чи ввели правельне значення
	if (_n >= 0 && _n < n)
	{
		cout << "Введіть прізвище, ім'я, по-батькові: ";
		cin >> d[_n].Name.surname;
		cin >> d[_n].Name.name;
		cin >> d[_n].Name.patronymic;

		cout << "Введіть дату народження (день місяць рік): ";
		cin >> d[_n].Birth.day;
		cin >> d[_n].Birth.month;
		cin >> d[_n].Birth.year;

		cout << "Введіть номер групи: ";
		cin >> d[_n].group_ses.GROUP;

		cout << "Введіть Успішність з 5-ти предметів !БЕЗ ПРОБІЛІ В ПОРЯДКУ ЗРОСТАННЯ!: ";
		cin >> d[_n].group_ses.SES;

		system("cls"); //очистка кoнсолі

		cout << "Дані змвнені" << '\n';
	}
	else
	{
		cout << "Намер введений не правильно" << '\n';
	}
}
void DeleteData(STUDENT* (&d), int& n)
{
	int _n;
	cout << "Введіть номер єлемента (від 1 до " << n << "): ";
	cin >> _n;
	_n--;

	system("cls"); //очистка кoнсолі

	// Перевірки чи ввели правельне значення
	if (_n >= 0 && _n < n)
	{
		STUDENT* buf = new STUDENT[n]; //Тимчасовий масив

		Copy(buf, d, n);

		//Виділяєм нову памят
		--n;
		d = new STUDENT[n];

		int q = 0;

		//замамятовуєм дані крім непотрібного
		for (size_t i = 0; i <= n; i++)
		{
			if (i != _n)
			{
				d[q] = buf[i];
				q++;
			}
		}

		system("cls"); //очистка кoнсолі
		delete[]buf;

		cout << "Данні видалені" << '\n';

	}
	else
	{
		cout << "Намер введений не правильно" << '\n';
	}
}
void Copy(STUDENT* (&d_n), STUDENT* (&d_o), int n)
{
	for (size_t i = 0; i < n; i++)
	{
		d_n[i] = d_o[i];
	}
}
void Copy(STUDENT& d_n, STUDENT& d_o)
{
	d_n.Name.surname = d_o.Name.surname;
	d_n.Name.name = d_o.Name.name;
	d_n.Name.patronymic = d_o.Name.patronymic;

	d_n.Birth.day = d_o.Birth.day;
	d_n.Birth.month = d_o.Birth.month;
	d_n.Birth.year = d_o.Birth.year;

	d_n.group_ses.GROUP = d_o.group_ses.GROUP;

	d_n.group_ses.SES = d_o.group_ses.SES;
}
void AddData(STUDENT* (&d), int& n)
{
	STUDENT* buf;// Тимчасвий масив данних
	buf = new STUDENT[n];

	Copy(buf, d, n);//Зберігаєм дані в тимчасовй масив

	n++;
	d = new STUDENT[n];// Виділяєм нову память

	Copy(d, buf, --n); // повертаєм дані

	cout << "Введіть прізвище, ім'я, по-батькові: ";
	cin >> d[n].Name.surname;
	cin >> d[n].Name.name;
	cin >> d[n].Name.patronymic;

	cout << "Введіть дату (день місяць рік): ";
	cin >> d[n].Birth.day;
	cin >> d[n].Birth.month;
	cin >> d[n].Birth.year;

	cout << "Введіть номер групи: ";
	cin >> d[n].group_ses.GROUP;

	cout << "Введіть Успішність з 5-ти предметів !БЕЗ ПРОБІЛІ В ПОРЯДКУ ЗРОСТАННЯ!: ";
	cin >> d[n].group_ses.SES;
	system("cls"); //очистка кoнсолі

	cout << "Дані дадані" << '\n';

	delete[]buf;
}
void DataSorting(STUDENT* d, int n)
{
	STUDENT buf;//тимчасова змінна

	int a;

	cout << "За яким параметром відбудеться сортування?\n1 - за прізвищем\n2 - за роком народження\n3 - за номером групи\n4 - за баллом\n";
	cin >> a;
	switch (a)
	{
	case 1:
	{
		for (size_t i = 0; i < n; i++)// мортування методом бульбашки
		{
			for (size_t j = 0; j < n; j++)
			{
				if (d[i].Name.surname > d[j].Name.surname)
				{
					Copy(buf, d[j]);
					Copy(d[j], d[i]);
					Copy(d[i], buf);
				}
			}
		}
		break;
	}
	case 2:
	{
		for (size_t i = 0; i < n; i++)// мортування методом бульбашки
		{
			for (size_t j = 0; j < n; j++)
			{
				if (d[i].Birth.year > d[j].Birth.year)
				{
					Copy(buf, d[j]);
					Copy(d[j], d[i]);
					Copy(d[i], buf);
				}
			}
		}
		break;
	}
	case 3:
	{
		for (size_t i = 0; i < n; i++)// мортування методом бульбашки
		{
			for (size_t j = 0; j < n; j++)
			{
				if (d[i].group_ses.GROUP > d[j].group_ses.GROUP)
				{
					Copy(buf, d[j]);
					Copy(d[j], d[i]);
					Copy(d[i], buf);
				}
			}
		}
		break;
	}
	case 4:
	{
		for (size_t i = 0; i < n; i++)// мортування методом бульбашки
		{
			for (size_t j = 0; j < n; j++)
			{
				if (d[i].group_ses.SES > d[j].group_ses.SES)
				{
					Copy(buf, d[j]);
					Copy(d[j], d[i]);
					Copy(d[i], buf);
				}
			}
		}
		break;
	}
	default:
	{
		cout << "Неправильно введений номер дії" << '\n';
		break;
	}
	}
	cout << "Данні відсортовані" << '\n';
}
void SavingData(STUDENT* d, int n, string fileName)
{
	ofstream record(fileName, ios::out);
	if (record)
	{
		record << n << '\n';// створюєм потік для запису

		for (size_t i = 0; i < n; i++)
		{
			record << d[i].Name.surname << '\n';
			record << d[i].Name.name << '\n';
			record << d[i].Name.patronymic << '\n';

			record << d[i].Birth.day << ' ';
			record << d[i].Birth.month << ' ';
			record << d[i].Birth.year << '\n';

			record << d[i].group_ses.GROUP << ' ';
			if (i < n - 1)
			{
				record << d[i].group_ses.SES << '\n';
			}
			else
			{
				record << d[i].group_ses.SES;
			}
		}
	}
	else
	{
		cout << "Помилка відкриття файлу" << '\n';
	}
	record.close();
}