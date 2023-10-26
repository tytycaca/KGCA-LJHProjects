#include "TStack.h"

template <class T>
TStack<T>::TStack(): top(-1)
{
	data = new T[SIZE];
}

template <class T>
TStack<T>::~TStack()
{
	delete [] data;
}

template <class T>
void TStack<T>::Push(const T &pData)
{
	if (top == SIZE - 1)
	{
		std::cout << "overflow!" << std::endl;
		return;
	}
	else
	{
		top++;
		data[top] = pData;
		std::cout << "PUSH!" << data[top] << std::endl;
		return;
	}
}

template <class T>
void TStack<T>::Pop()
{
	if (top == -1)
	{
		std::cout << "underflow!" << std::endl;
		return;
	}
	else
	{
		std::cout << "POP!" << data[top] << std::endl;
		top--;
		return;
	}
}