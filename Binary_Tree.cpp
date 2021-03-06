#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <math.h>
#include <conio.h>
#include <fstream>
using namespace std;

struct Node {
	Node* l, *r;
	int  x;
};
void Node_Add(Node*& p, int x);
void Node_Clear(Node* p);
int  Node_Height(const Node* p);

int main(void) {

	Node* tr = NULL;

	setlocale(LC_ALL, "Russian"); 
	int n, how_much;
	int x;
	ifstream infile;
	infile.open("infile.txt"); //Проверка файла
	long int current;
	int file_count = 0;
	do
	{
		infile >> current;
		file_count++;

	} while (current != 00000);
	file_count--;
	cout << file_count << endl;
	infile.close();
	cout << "Сколько узлов будет в дереве ? (Введите кол-во узлов (min : 2))" << endl;
	cin >> n;
		if ((n < 1) || (n > file_count))
			{
				cout << "Введено неправильное кол-во узлов." << endl;
				return -1;
			}
	infile.open("infile.txt"); //Проверка файла
	current = 0;
	for (int count = 0; count < n; count++)
	{
		cout << "Введите элемент #" << count + 1 << " : ";
		infile >> current;
		cout << current << endl;
		Node_Add(tr, current);
	}

	cout << "height: " << Node_Height(tr) << std::endl;
	Node_Clear(tr);
	return 0;
}

//вставка
void Node_Add(Node*& p, int x) {
	if (p == NULL) {
		p = new (std::nothrow) Node();
		if (p != NULL) {
			p->l = p->r = NULL;
			p->x = x;
		}
	}
	else if (x < p->x)
		Node_Add(p->l, x);
	else
		Node_Add(p->r, x);
}

//удаление всех
void Node_Clear(Node* p) {
	if (p != NULL) {
		if (p->l != NULL)
			Node_Clear(p->l);
		if (p->r != NULL)
			Node_Clear(p->r);
		delete p;
	}
}

//высота дерева
int Node_Height(const Node* p) {
	int l, r, h = 0;
	if (p != NULL) {
		l = Node_Height(p->l);
		r = Node_Height(p->r);
		h = ((l > r) ? l : r) + 1;
	}
	return h;
}