#include <iostream>
#include <exception>

//template <typename T>
struct MyStack
{
	int Data;
	MyStack* next = nullptr;
};

struct MyStack_List
{
	MyStack* top = nullptr;
	void push(int D) // добавление элементов
	{
		MyStack* q = new MyStack;
		q->Data = D;
		if (top == nullptr)
			top = q;
		else
		{
			q->next = top;
			top = q;
		}
	}
	int pop()//удаляет последний элемент стека
	{
		int dat = top->Data;
		top = top->next;
		return dat;
	}
	void peek()// вывод всех элементов на экран
	{
		MyStack* q = new MyStack;
		q = top;
		while (q != NULL)
		{
			std::cout << q->Data << std::endl;
			q = q->next;
		}
	}
	//int arr[10];
	//int top = -1;
	//void peek();
};

int main()
{
	MyStack_List* top = new MyStack_List;
	MyStack_List* top_2 = new MyStack_List;
	MyStack_List* top_3 = new MyStack_List;
	top->push(1);
	top->push(4);
	top->push(6);
	top->push(2);
	top->push(8);
	top->push(12);
	top->push(3);
	top->push(9);
	top->push(7);
	top->push(0);
	top->peek();
	std :: cout << std :: endl;
	for (int i = 0; i < 10; i++)
	{
		int pop_copy = top->pop();
		if (pop_copy < 5) top_2->push(pop_copy);
		else top_3->push(pop_copy);
	}

	top_2->peek();
	std :: cout <<std :: endl;
	top_3->peek();
}
