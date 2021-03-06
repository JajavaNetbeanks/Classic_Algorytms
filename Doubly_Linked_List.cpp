#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;
struct Elem
{
	int data; // данные
	Elem * next, *prev;
};

class List
{
	// Голова, хвост
	Elem * Head, *Tail;
	// Количество элементов
	int Count;

public:

	// Конструктор
	List();
	// Получить количество
	int GetCount();
	// Получить элемент списка
	Elem* GetElem(int);

	// Вставка элемента, если параметр не указывается,
	// то функция его запрашивает
	void Insert(int pos = 0);

	// Добавление в конец списка
	void AddTail(int n);

	// Добавление в начало списка
	void AddHead(int n);

	// Печать списка
	void Print();
	// Печать определенного элемента
	void Print(int pos);
	// Запись списка из файла
	List FromFile();
	int InputCheck();
};

List::List()
{
	// Изначально список пуст
	Head = Tail = NULL;
	Count = 0;
}
void List::AddHead(int n)
{
	// новый элемент
	Elem * temp = new Elem;

	// Предыдущего нет
	temp->prev = 0;
	// Заполняем данные
	temp->data = n;
	// Следующий - бывшая голова
	temp->next = Head;

	// Если элементы есть?
	if (Head != 0)
		Head->prev = temp;

	// Если элемент первый, то он одновременно и голова и хвост
	if (Count == 0)
		Head = Tail = temp;
	else
		// иначе новый элемент - головной
		Head = temp;

	Count++;
}

void List::AddTail(int n)
{
	// Создаем новый элемент
	Elem * temp = new Elem;
	// Следующего нет
	temp->next = 0;
	// Заполняем данные
	temp->data = n;
	// Предыдущий - бывший хвост
	temp->prev = Tail;

	// Если элементы есть?
	if (Tail != 0)
		Tail->next = temp;

	// Если элемент первый, то он одновременно и голова и хвост
	if (Count == 0)
		Head = Tail = temp;
	else
		// иначе новый элемент - хвостовой
		Tail = temp;

	Count++;
}

void List::Insert(int pos)
{
	// если параметр отсутствует или равен 0, то запрашиваем его
	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}

	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count + 1)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}

	// Если вставка в конец списка
	if (pos == Count + 1)
	{
		// Вставляемые данные
		int data;
		cout << "Input new number: ";
		cin >> data;
		// Добавление в конец списка
		AddTail(data);
		return;
	}
	else if (pos == 1)
	{
		// Вставляемые данные
		int data;
		cout << "Input new number: ";
		cin >> data;
		// Добавление в начало списка
		AddHead(data);
		return;
	}

	// Счетчик
	int i = 1;

	// Отсчитываем от головы n - 1 элементов
	Elem * Ins = Head;

	while (i < pos)
	{
		// Доходим до элемента, 
		// перед которым вставляемся
		Ins = Ins->next;
		i++;
	}

	// Доходим до элемента, 
	// который предшествует
	Elem * PrevIns = Ins->prev;

	// Создаем новый элемент
	Elem * temp = new Elem;

	// Вводим данные
	cout << "Input new number: ";
	cin >> temp->data;

	// настройка связей
	if (PrevIns != 0 && Count != 1)
		PrevIns->next = temp;

	temp->next = Ins;
	temp->prev = PrevIns;
	Ins->prev = temp;

	Count++;
}


void List::Print(int pos)
{
	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}

	Elem * temp;

	// Определяем с какой стороны 
	// быстрее двигаться
	if (pos <= Count / 2)
	{
		// Отсчет с головы
		temp = Head;
		int i = 1;

		while (i < pos)
		{
			// Двигаемся до нужного элемента
			temp = temp->next;
			i++;
		}
	}
	else
	{
		// Отсчет с хвоста
		temp = Tail;
		int i = 1;

		while (i <= Count - pos)
		{
			// Двигаемся до нужного элемента
			temp = temp->prev;
			i++;
		}
	}
	// Вывод элемента
	cout << pos << " element: ";
	cout << temp->data << endl;
}

void List::Print()
{
	// Если в списке присутствуют элементы, то пробегаем по нему
	// и печатаем элементы, начиная с головного
	if (Count != 0)
	{
		Elem * temp = Head;
		cout << "( ";
		while (temp->next != 0)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}

		cout << temp->data << " )\n";
	}
}


int List::GetCount()
{
	return Count;
}

Elem * List::GetElem(int pos)
{
	Elem *temp = Head;

	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return 0;
	}

	int i = 1;
	// Ищем нужный нам элемент
	while (i < pos && temp != 0)
	{
		temp = temp->next;
		i++;
	}

	if (temp == 0)
		return 0;
	else
		return temp;
}

List List::FromFile()
{
	List G;
	ifstream infile;
	infile.open("infile.txt"); //Проверка файла
	int current;
	string check = " ";
	int counter = 0;
	do
	{
		infile >> check;
		counter++;
	} while (check != "$");
	infile.close();
	infile.open("infile.txt");
	cout << "Number of elements without spaces: " << counter << endl;
	counter--;
	if (counter != 0) {
		do
		{
			infile >> current;
			G.AddTail(current);
			counter--;
		} while (counter != 0);
	}
	infile.close();
	return G;
}
int List::InputCheck()
{
	ifstream infile;
	infile.open("infile1.txt");
	//Проверка файла
	if (!infile.is_open())
	{
		cout << "Error, file doesn't exist or doesn't open";
		return -1;
	};
	if (infile.peek() == EOF)
	{
		cout << "Error,this file is empty!";
		return 1;
	}
	infile.close();
	infile.open("infile2.txt");
	//Проверка файла
	if (!infile.is_open())
	{
		cout << "Error, file doesn't exist or doesn't open";
		return -1;
	};
	if (infile.peek() == EOF)
	{
		cout << "Error,this file is empty!";
		return 1;
	}
	infile.close();
	infile.open("infile3.txt");
	//Проверка файла
	if (!infile.is_open())
	{
		cout << "Error, file doesn't exist or doesn't open";
		return -1;
	};
	if (infile.peek() == EOF)
	{
		cout << "Error,this file is empty!";
		return 1;
	}
	infile.close();
	return 0;
}

int main()
{
	List L1, L2, L3;
	ifstream infile;
	int check;
	check = L1.InputCheck();
	if (check)
	{
		return -1;
	}
	L1 = L1.FromFile();
	// Распечатка списка
	cout << "List L:\n";
	L1.Print();
	cout << endl;
	// Вставка элемента в список
	L1.Insert();
	// Распечатка списка
	cout << "List L:\n";
	L1.Print();
	return 0;
}