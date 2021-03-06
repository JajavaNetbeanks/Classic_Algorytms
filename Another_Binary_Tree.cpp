// algorytmi_6_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "locale.h"

class Tree {
private:
	struct TreeNode {
		TreeNode() :left(0), right(0), data(0) {}
		int data;
		TreeNode* left; // указатель на левого потомка
		TreeNode* right; // указатель на правого потомка
	};
	TreeNode* root;

public:

	//конструктор
	Tree() : root(0) {}

	//добавление узла в дерево
public:
	void insert(int value) {
		insert_helper(&root, value); // вызываем вспомогательную подпрограмму
	}

private:
	void insert_helper(TreeNode** node, int value) {
		if (*node == 0) { // если нашли пустой "лист", добавляем
			*node = new TreeNode; // выделяем память
			if (node == NULL)
				printf("Ошибка! Память не выделилась");

			(*node)->data = value; // добавляем ключ
		}
		else
			if ((*node)->data > value) // идем вниз по дереву:
				insert_helper(&((*node)->left), value); // если новое значение меньше, уходим налево, 
			else										// вызывая рекурсивно вспомогательную фукнцию
				insert_helper(&((*node)->right), value); // -//- направо
	}

	//печать дерева на экран
public:
	void print() {
		if (root)
			print_helper(root, 0); // если корень не найден, печатаем ошибку
		else
			printf("Дерево пусто!\n");
	}

private:
	void print_helper(TreeNode* node, int spaces) {
		while (node != 0) { // пока есть элементы: 
			print_helper(node->right, spaces + 5); // печатем правое поддерево, считая кол-во потомков

			for (int i = 1; i < spaces; ++i) // после печатаем нужное кол-во пробелов для "красивого" вывода дерева
				printf(" ");

			printf("%d\n", node->data);	// печатаем корень

			node = node->left;	// идем вниз по дереву и печатаем левые потомки
			spaces += 5; // увеичиваем кол-во пробелов
		}
	}

	//печать дерева в файл
public:
	void fprint(FILE *out) {
		if (root)
			fprint_helper(root, 0, out);
		else
			fprintf(out, "Дерево пусто!\n");
	}

private:
	void fprint_helper(TreeNode* node, int spaces, FILE *out) { // аналогично обычному вывода дерева 
		while (node != 0) {
			fprint_helper(node->right, spaces + 5, out);

			for (int i = 1; i < spaces; ++i)
				fprintf(out, " ");

			fprintf(out, "%d\n", node->data);

			node = node->left;
			spaces += 5;
		}
	}

public:
	int  heigth() {
		return(heigth_helper(&root));
	}
private:
	int heigth_helper(TreeNode** node) {
		int Hleft = 0; // зануляем высоты поддеревьев
		int Hright = 0;
		if (*node == NULL) return 0; // если не найден элемент, возращаем 0
		if ((*node)->left)	Hleft = heigth_helper(&((*node)->left)); // идем налево
		if ((*node)->right)	Hright = heigth_helper(&((*node)->right)); // идем направо
		if (Hright > Hleft)
			return(Hright + 1); // возращаем наибольшую высоту
		return(Hleft + 1);
	}
};
int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Rus");
	Tree Lr6;
	FILE *infile;
	infile = fopen("infile.txt", "r");
	if (infile == NULL)
	{
		printf("Файл \"infile.txt\" не был открыт... Проверьте его целостность и запустите программу.\n");
		return 1;
	}
	int X; // чтение из файла
	while (fscanf(infile, "%d\n", &X) != EOF)
	{
		Lr6.insert(X);
	}
	printf("Дерево имеет вид:\n\n"); // печать дерева
	Lr6.print();

	int H = Lr6.heigth(); // находим высоту
	printf("\n\nВысота дерева: %d", H);
	FILE *output;
	output = fopen("output.txt", "w");
	if (output == NULL)
	{
		printf("File \"output.txt\" не может быть открыт или создан...");
		return 2;
	}
	Lr6.fprint(output);
	fclose(infile);
	fclose(output);
	return 0;
}