#include <iostream>

class A
{
public:
	A();
	~A();

private:
	int a;
};

A::A()
{
}

A::~A()
{
}

class B
{
public:
	B();
	B(int, int);
	~B();

private:
	int val1;
	int val2;
};

B::B()
{
}

B::B(int b, int c)
{
	val1 = b;
	val2 = c;
}

B::~B()
{
}

int main()
{
	A a;
	int c = 0;
	B b(5, 6);
	B bb = {5, 6};

	return 0;
}