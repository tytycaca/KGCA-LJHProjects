//
//

#include <iostream>

int Fun1()
{
    int a = 10;
    a = 17 - a;
    return a;
}

int Fun2()
{
    int a, b, c;
    a = 5;
    b = 3;
    c = 7;
    int iSum = a + b * c;
    return iSum;
}

int Fun3()
{
    int a = 5;
    int b = 2;
    int c = a % b;
    if (c == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Fun4()
{
    int ret1 = Fun1();
    int ret2 = Fun2();
    int ret3 = Fun3();

    //char buffer1[3] = { 'a','b','c','\n' };
    char buffer2[4] = { 'a','b','c','\n' };
    char buffer3[] = { 'a','b','c','\n' };
    char buffer4[3] = { 'a' };
    char buffer5[3] = "a";
    char buffer6[] = "";
}

int Fun5()
{
    int number[3] = { 1,2,3 };
    return number[1];
}

int main()
{
    Fun4();
    //std::cout << Fun5() << std::endl;
    //std::cout << "Hello World!3\n";

    int aArray[6] = {0, 1, 2, 3, 4, 5};
    int* ptrAdressA = aArray;
    int a0, a1, a2, a3, a4;

    a0 = *ptrAdressA;
    ptrAdressA++;
    a1 = *ptrAdressA;
    ptrAdressA--;
    a2 = *ptrAdressA;
    ptrAdressA += 2;
    a3 = *ptrAdressA;
    ptrAdressA += 3;
    a4 = *ptrAdressA;

    int i, k[10], a = 0, b = 0;

    for (i = 0; i < 10; i++)
        k[i] = 10 - i;

    int* p = k;
    p += 5;
    a = *(p + 1);
    b = p[3];
 }
