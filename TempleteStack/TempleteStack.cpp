// TempleteStack.cpp
#include "TStack.cpp"

TStack<int>* intStack = new TStack<int>;

int main()
{
	int input = 0;

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		input = rand() % 100;

		if (rand() % 3 <= 1)
		{
			intStack->Push(input);
		}

		else
		{
			intStack->Pop();
		}
	}
}
