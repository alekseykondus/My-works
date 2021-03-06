#include <iostream>
#define order 100

struct MatrixElement
{
	int i, j;
	double data;
	MatrixElement* next = nullptr;
	MatrixElement* prev = nullptr;
};

struct MatrixElement_List
{
	MatrixElement* head = nullptr;
	MatrixElement* end = nullptr;

	void add(int i, int j, int data)
	{
		MatrixElement *e = new MatrixElement;
		e->i = i;
		e->j = j;
		e->data = data;
		if (!head)
		{
			head = e;
			end = e;
		}
		else 
		{
			e->next = head;
			head->prev = e;
			head = e;
		}
	}
};

void make_vertical_bundle(MatrixElement_List h_c[order], MatrixElement_List(&v_c)[order])
{//получаем горизонтальную связку, имея вертикальную
	for (int i = 0; i < order; i++)
	{
		MatrixElement* e = h_c[i].end;
		while (e != nullptr)
		{
			v_c[e->j].add(e->i, e->j, e->data);
			e = e->prev;
		}
	}

}

void matrix_sum(MatrixElement_List horizontal_A[order], MatrixElement_List horizontal_B[order], MatrixElement_List (&h_c)[order], MatrixElement_List (&v_c)[order])
{//сумма матриц
	for (int i = 0; i < order; i++)
	{
		MatrixElement* h_a = horizontal_A[i].end;
		MatrixElement* h_b = horizontal_B[i].end;
		if (h_a == nullptr && h_b != nullptr)  
			while (h_b != nullptr)
			{
				h_c[i].add(h_b->i, h_b->j, h_b->data);
				h_b = h_b->prev;
			}
		while (h_a != nullptr)
		{
			if (h_b == nullptr)
				h_b = horizontal_B[i].head;
			while (h_b != nullptr)
			{
				if ((h_a->j == h_b->j) && ((h_a->data + h_b->data) != 0))
				{
					h_c[i].add(h_a->i, h_a->j, h_a->data + h_b->data);
					h_b = h_b->prev;
					break;
				}
				else if (h_a->j > h_b->j && h_b->prev == nullptr)
				{
					h_c[i].add(h_a->i, h_a->j, h_a->data);
					break;
				}
				else if (h_a->j > h_b->j)
					h_c[i].add(h_b->i, h_b->j, h_b->data);
				else if (h_a->j < h_b->j)
				{
					h_c[i].add(h_a->i, h_a->j, h_a->data);
					break;
				}
				h_b = h_b->prev;
			}
			h_a = h_a->prev;
		}
	}
	make_vertical_bundle(h_c, v_c);
}

void matrix_multiplication(MatrixElement_List horizontal_A[order], MatrixElement_List vertical_B[order], MatrixElement_List (&h_c)[order], MatrixElement_List (&v_c)[order])
{//умножение матриц
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			int count = 0;
			MatrixElement* h_a = horizontal_A[i].end;

			while (h_a != nullptr)
			{
				MatrixElement* v_b = vertical_B[j].end;
				while (v_b != nullptr)
				{
					if (h_a->j == v_b->i)
						count += h_a->data * v_b->data;
					v_b = v_b->prev;
				}
				h_a = h_a->prev;
			}
			if (count != 0) 
				h_c[i].add(i, j, count);
		}
	}
	make_vertical_bundle(h_c, v_c);
}

void print_matrix(MatrixElement_List horizontal[order])
{//вывод в виде матрицы
	for (int i = 0; i < order; i++)
	{
		MatrixElement* e = horizontal[i].end;

		int j_copy = -1;
		if (e == nullptr)
			for (int j = 0; j < order; j++)
				std::cout << '0' << ' ';
		while (e != nullptr)
		{
			if (j_copy == -1 && e->j != 0)
				for (int j = 0; j < e->j; j++)
					std::cout << '0' << ' ';
			else
				for (int j = j_copy + 1; j < e->j; j++)
					std::cout << '0' << ' ';
			std::cout << e->data << ' ';
			j_copy = e->j;

			if (e->prev == nullptr)
				for (int j = j_copy + 1; j < order; j++) std::cout << '0' << ' ';

			e = e->prev;
		}
		std::cout << std::endl;
	}
}

void print_list(MatrixElement_List list[order])
{//вывод в виде списка
	for (int i = 0; i < order; i++)
	{
		MatrixElement* e = list[i].end;
		while (e != nullptr)
		{
			std::cout << e->data << ' ';
			e = e->prev;
		}
	}
}

void matrix_creation(MatrixElement_List (&horizontal)[order], MatrixElement_List (&vertical)[order], const char m[10])
{//заполнение матрицы из файла
	char name[20] = "matrix_";
	strcat_s(name, m);
	FILE* file;
	int A;

	if (fopen_s(&file, name, "rb"))
		perror("Error");
	else
	{
		for (int i = 0; i < order; i++)
			for (int j = 0; j < order; j++)
			{
				fread(&A, sizeof(int), 1, file);
				if (A != 0)
				{
					horizontal[i].add(i, j, A);
					vertical[j].add(i, j, A);
				}
			}
		std::cout << name << std::endl;
		print_matrix(horizontal);
		std::cout << std::endl;
	}
	fclose(file);
}

int main()
{
	/* СОЗДАНИЕ И ЗАПОЛНЕНИЕ ФАЙЛА ЭЛЕМЕНТАМИ МАТРИЦЫ
	FILE* file;
	if (fopen_s(&file, "matrix_A", "wb"))
		perror("Error");
	else
	{
		for (int i = 0; i < pow(order, 2); i++)
		{
			int a = rand() % 2;
			fwrite(&a, sizeof(int), 1, file);
		}
	}
	fclose(file);

	if (fopen_s(&file, "matrix_B", "wb"))
		perror("Error");
	else
	{
		for (int i = 0; i < pow(order, 2); i++)
		{
			int a = rand() % 2;
			fwrite(&a, sizeof(int), 1, file);
		}
	}
	fclose(file);
	*/

	MatrixElement_List horizontal_A[order], vertical_A[order];
	matrix_creation(horizontal_A, vertical_A, "A");

	std::cout << std::endl << std::endl;


	MatrixElement_List horizontal_B[order], vertical_B[order];
	matrix_creation(horizontal_B, vertical_B, "B");


	MatrixElement_List horizontal_SUM_A_B[order], vertical_SUM_A_B[order];
	matrix_sum(horizontal_A, horizontal_B, horizontal_SUM_A_B, vertical_SUM_A_B);

	std::cout << "matrix SUM (A+B):" << std::endl;
	print_matrix(horizontal_SUM_A_B);
	std::cout << std::endl << std::endl;

	//print_list(vertical_SUM_A_B);

	MatrixElement_List horizontal_multiply_A_B[order], vertical_multiply_A_B[order];
	matrix_multiplication (horizontal_A, vertical_B, horizontal_multiply_A_B, vertical_multiply_A_B);
	
	std::cout << "matrix MULTIPLICATION (A*B):" << std::endl;
	print_matrix(horizontal_multiply_A_B);
	std::cout << std::endl << std::endl;

	//print_list(vertical_multiply_A_B); 

}
