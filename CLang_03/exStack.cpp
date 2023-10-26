#include <iostream>
#define MAX 30

int* array = new int[MAX];

int main()
{
	for (int i = 0; i < MAX; i++)
		array[i] = i;

	for (int i = 0; i < MAX; i++)
		std::cout << array[i] << std::endl;

	return 0;
}