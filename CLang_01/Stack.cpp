#include <iostream>
#include <Windows.h>
#define MAX 3

using namespace std;

int cnt, result;
int arr[MAX];

void init()
{
	cnt = -1;
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

	cnt++;
	arr[cnt] = data;
	cout << "PUSH!" << endl;

	return;
}

void pop()
{
	if (cnt == -1)
	{
		cout << "underflow!" << endl;
		return;
	}

	result = arr[cnt];
	cnt--;
	cout << "POP!" << "index: " << cnt+1 << " / data: " << result << endl;

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