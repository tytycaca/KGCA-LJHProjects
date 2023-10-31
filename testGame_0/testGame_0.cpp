#include <iostream>
#include "MyCharacter.h"

int main()
{
	std::list<MyCharacter*> MyCharacterList;

	MyCharacter* TestCharacter_0 = new MyCharacter;
	MyCharacter* TestCharacter_1 = new MyCharacter;
	MyCharacter* TestCharacter_2 = new MyCharacter;
	MyCharacterList.push_back(TestCharacter_0);
	MyCharacterList.push_back(TestCharacter_1);
	MyCharacterList.push_back(TestCharacter_2);

	for (std::list<MyCharacter*>::iterator iter = MyCharacterList.begin();
		iter != MyCharacterList.end();
		iter++)
	{
		std::wcout << *iter;
	}

	return 0;
}