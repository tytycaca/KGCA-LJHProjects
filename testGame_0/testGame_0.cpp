#include <locale>
#include "MyCharacter.h"

int main()
{
	// 유니코드로 한국어를 출력하기 위한 설정 함수 호출
	std::locale::global(std::locale("Korean"));
	// 위의 코드가 작동하지 않을 경우에는 아래의 코드를 사용
	// (Global Locale 을 설정하는 것이어서 Stream 에 미치지 않을 수 있음)
	// std::wcout.imbue(std::locale("kor"));
	// cin 의 경우
	// std::wcin.imbue(std::locale("kor"));

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