#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

template<typename TYPE> //создаем шаблон, в шаблоне будут использоваться встроенные типы данных 
class List {	//создаем класс для списка
private:
	template<typename TYPE> //создаем шаблон, в шаблоне будут использоваться встроенные типы данных 
	class Node {	//создаем класс 
	public:
		TYPE d;
		Node* next; //указатель для следующей точки 
		Node* prev;  //указатель для предыдущей точки
		Node(TYPE d, Node* next = nullptr, Node* prev = nullptr)  //обнуляем указатели
		{
			this->d = d;
			this->next = next;
			this->prev = prev;
		}
	};
	size_t size;	// размер списка
	Node<TYPE>* head;	//указатель начала списка
	Node<TYPE>* tail;	//указатель конца списка

public:
	List();		//вызов автоконструктора
	void AddToList(TYPE d);	 //функция добавления к списку
	void AddInHead(TYPE d);		//функция добавления в начало списка
	TYPE& opeator[](const int index);	 //перегрузка оператора индексации
	size_t GetSizeofList();	 //функция определения размеров списка
	void Put(TYPE data, int index);	 //добавление на опредленную позицию элемента списка
	TYPE Peek();	 //функция ‘peek’ для входных потоков извлекает следующий символ из потока, фактически не потребляя его. Это означает, что вы можете «просмотреть» следующий символ на входе, и при следующем вызове любой потребляющей операции
	void Delete(int index);		 //функция удаления из списка заданного элемента
	void Clear();	 //функция очистки списка
	~List();	 //вызывается деконструктор
};

template<typename TYPE>
List<TYPE>::List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename TYPE>
void List<TYPE>::AddToList(TYPE d)
{
	if (head == nullptr)		//если список пустой
	{
		head = tail = new Node<TYPE>(d);
	}
	else               //если в списке уже есть элементы
	{
		Node<TYPE>* curr = new Node<TYPE>(d, nullptr, tail);
		tail->next = curr;
		tail = curr;
	}
	size++;
}

template<typename TYPE> 
void List<TYPE>::AddInHead(TYPE d) 
{
	if (head == nullptr)
	{
		head = tail = new Node<TYPE>(d);
	}
	else
	{
		Node<TYPE>* curr = new Node<TYPE>(d, head);
		head = curr;
	}
	size++;
}

template<typename TYPE>
TYPE& List<TYPE>::operator[](const int index) //перегрузка оператора индексации. Оператор индексации является одним из операторов, перегрузка которого должна выполняться через метод класса.Функция перегрузки оператора[] всегда будет принимать один параметр : значение индекса(элемент массива, к которому требуется доступ)
{
	Node<TYPE>* curr;
	int iter; //итерации
	if (index <= size / 2)
	{
		curr = head;
		iter = 0;
		while (true)
		{
			if (iter == index)
			{
				return curr -> d;
			}
			else
			{
				curr = curr -> next;
				iter++;
			}
		}
	}
	else
	{
		curr = tail;
		iter = size - 1;
		while (true)
		{
			if (iter == index)
			{
				return curr -> d;
			}
			else
			{
				curr = curr -> prev;
				iter--;
			}
		}
	}
}

template<typename TYPE>
size_t List<TYPE>::GetSizeOfList()
{
	return size;
}

template<typename TYPE>
void List<TYPE>::Put(TYPE d, int index)
{
	if (index == 0)		//если список пуст
	{
		AddInHead(d);
	}
	else if (index == size)
	{
		AddTo(d);		//если в списке уже есть элементы
	}
	else
	{
		Node<TYPE>* pred;	 //указатель для предыдущего
		Node<TYPE>* nin;	//указатель для нынешнего
		if (index <= size / 2)		//если в первой половине списка
		{
			pred = head;
			for (int i = 0; i < index - 1; i++)
			{
				pred = pred -> next;
			}
			nin = new Node<TYPE>(d, pred -> next, pred);
			pred -> next -> pred = nin;
			pred -> next = nin;
		}
		else
		{
			pred = tail;
			for (int i = size - 1; i > index; i--)
			{
				pred = pred -> prev;
			}
			nin = new Node<TYPE>(d, pred, pred -> prev);
			pred -> prev -> next = nin;
			pred -> prev = nin;
		}
	}
	size++;
}

template<typename TYPE>
TYPE List<TYPE>::Peek()		//возврат данных о конце списка
{
	return tail -> d;
}

template<typename TYPE>
void List<TYPE>::Delete(int index)
{
	if (index == 0)
	{
		Node<TYPE>* temp = head;
		head = head -> next;
		delete temp;
	}
	else if (index == size - 1)
	{
		Node<TYPE>* temp = tail;
		tail = tail -> prev;
		delete temp;
	}
	else
	{
		Node<TYPE>* pred;
		Node<TYPE>* ToDel;
		if (index <= size / 2)
		{
			pred = head;
			for (int i = 0; i < index - 1; i++)
			{
				pred = pred -> next;
			}
			ToDel = pred -> next;
			pred -> next = ToDel -> next;
			ToDel -> next -> prev = pred;
		}
		else
		{
			pred = tail;
			for (int i = size - 1; i > index + 1; i--)
			{
				pred = pred -> prev;
			}
			ToDel = pred -> prev;
			pred -> prev = ToDel -> prev;
			ToDel -> prev -> next = pred;
		}
		delete ToDel;
	}
	size--;
}

template<typename TYPE>
void List<TYPE>::Clear()
{
	while (size > 0)
	{
		Node<TYPE>* temp = head;
		head = head -> next;
		delete temp;
		size--;
	}
}

template<typename TYPE>
List<TYPE>::~List()
{}

int main()
{
	List<int> list;
	for (int i = 0; i < 10; i++)
		list.AddTo(i * 10);
	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;
	list.Insert(73, 8);		//вставим на 8 позицию число 73
	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;
	list.Delete(10);	//удаляем из списка 10 позицию
	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;
	list.Clear();		//очистим список
	for (int i = 0; i < 5; i++)
		list.Add(i * 2);
	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;
		return 0;
}