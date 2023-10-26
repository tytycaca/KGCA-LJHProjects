#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#define SIZE 10

template <class T>
class TStack
{
public:
	TStack();
	~TStack();
	void Push(const T& pData);
	void Pop();

private:
	int top;
	T* data;
};

