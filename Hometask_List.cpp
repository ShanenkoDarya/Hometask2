#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

template<typename TYPE> //создаем шаблон, в шаблоне будут использоваться встроенные типы данных 
class List {	//создаем общий класс для списка
private:
	template<typename TYPE> //создаем шаблон, в шаблоне будут использоваться встроенные типы данных 
	class V {	//создаем класс 
	public:
		TYPE d;
		V* next; //указатель для следующей точки 
		V* prev;  //указатель для предыдущей точки
		V(TYPE d, V* next = nullptr, V* prev = nullptr)  //обнуляем указатели
		{
			this -> d = d;
			this -> next = next;
			this -> prev = prev;
		}
	};
	size_t size;	// размер списка
	V<TYPE>* head;	//указатель начала списка
	V<TYPE>* tail;	//указатель конца списка

public:
	List();		//вызов автоконструктора
	void AddToList(TYPE d);	 //функция добавления элементов к списку
	void AddInHead(TYPE d);		//функция добавления элемента в начало списка (сохраняя все последующие значения)
	TYPE& operator[](const int index);	 //перегрузка оператора индексации
	size_t GetSizeofList();	 //функция определения размеров списка
	void Put(TYPE data, int index);	 //добавление на опредленную позицию элемента списка (с сохранением последующей очередности)
	TYPE Peek();	 //функция ‘peek’ для входных потоков извлекает следующий символ из потока, фактически не потребляя его. Это означает, что вы можете «просмотреть» следующий символ на входе, и при следующем вызове любой потребляющей операции
	void Delete(int index);		 //функция удаления из списка элемента с заданным индексом
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
		head = tail = new V<TYPE>(d);
	}
	else               //если в списке уже есть элементы
	{
		V<TYPE>* curr = new V<TYPE>(d, nullptr, tail);
		tail -> next = curr;
		tail = curr;
	}
	size++;
}

template<typename TYPE>
void List<TYPE>::AddInHead(TYPE d)
{
	if (head == nullptr)
	{
		head = tail = new V<TYPE>(d);
	}
	else
	{
		V<TYPE>* curr = new V<TYPE>(d, head);
		head = curr;
	}
	size++;
}

template<typename TYPE>
TYPE& List<TYPE>::operator[](const int index) //перегрузка оператора индексации. Оператор индексации является одним из операторов, перегрузка которого должна выполняться через метод класса.Функция перегрузки оператора[] всегда будет принимать один параметр : значение индекса(элемент массива, к которому требуется доступ)
{
	V<TYPE>* curr;
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
size_t List<TYPE>::GetSizeofList()
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
		AddToList(d);		//если в списке уже есть элементы
	}
	else
	{
		V<TYPE>* pred;	 //указатель для предыдущего
		V<TYPE>* nin;	//указатель для нынешнего
		if (index <= size / 2)		//если в первой половине списка
		{
			pred = head;
			for (int i = 0; i < index - 1; i++)
			{
				pred = pred -> next;
			}
			nin = new V<TYPE>(d, pred -> next, pred);
			pred -> next -> prev = nin;
			pred -> next = nin;
		}
		else
		{
			pred = tail;
			for (int i = size - 1; i > index; i--)
			{
				pred = pred -> prev;
			}
			nin = new V<TYPE>(d, pred, pred -> prev);
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
		V<TYPE>* temp = head;
		head = head -> next;
		delete temp;
	}
	else if (index == size - 1)
	{
		V<TYPE>* temp = tail;
		tail = tail -> prev;
		delete temp;
	}
	else
	{
		V<TYPE>* pred;
		V<TYPE>* ToDel;
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
		V<TYPE>* temp = head;
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

	for (int i = 0; i < 10; i++) //заполним список [0,3,6,9,12,15,18,21,24,27]
		list.AddToList(i * 3);

	cout << "The initial list:" << endl;

	for (int i = 0; i < list.GetSizeofList(); i++) 
		cout << list[i] << endl;

	list.Put(73, 8);		//вставим на 8 позицию число 73, т.е. добавим перед числом 24 число 73

	cout << "The list with changed element:" << endl;

	for (int i = 0; i < list.GetSizeofList(); i++) //вывести должен [0,3,6,9,12,15,18,21,73,24,27]
		cout << list[i] << endl;

	list.Delete(10);	//удаляем из списка 10 позицию (в нашем случае число 27)

	cout << "The list with deleted value:" << endl;

	for (int i = 0; i < list.GetSizeofList(); i++)	//вывести должен [0,3,6,9,12,15,18,21,73,24]
		cout << list[i] << endl;

	list.AddInHead(15); // добавляем в самое начало списка 15, со сдвигом остальных значений

	cout << "The list with added fisrt value:" << endl;

	for (int i = 0; i < list.GetSizeofList(); i++)	//вывести должен [15,0,3,6,9,12,15,18,21,73,24]
		cout << list[i] << endl;

	list.Clear();		//очистим список

	return 0;
	system("pause");
}