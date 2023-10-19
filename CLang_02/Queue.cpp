#include <iostream>
#include <Windows.h>
#define MAX 3

using namespace std;

int cnt, result, in, out;
int arr[MAX];

void init()
{
	cnt = 0;
	in = 0;
	out = 0;
	result = 0;
	memset(arr, 0, sizeof(int) * MAX);
}

void push(int data)
{
	if (cnt == MAX)
	{
		cout << "overflow!" << endl;
		return;
	}

	arr[in] = data;
	cout << "PUSH!" << endl;

	in = ++in % MAX;
	cnt++;

	return;
}

void pop()
{
	if (cnt == 0)
	{
		cout << "underflow!" << endl;
		return;
	}

	result = arr[out];
	cout << "POP!" << "index: " << out << " / data: " << result << endl;

	out = ++out % MAX;
	cnt--;

	return;
}


int main()
{
	int input = 0;
	srand(time(NULL));

	init();

	for (int i = 0; i < 10; i++)
	{
		input = rand() % 100;

		if (rand() % 3 <= 1)
			push(input);

		else
			pop();
	}
}