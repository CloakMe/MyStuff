/*  C++ Basics 6
    
    Fix the problem with the code below


*/

#include <iostream>

void printValuePlus2(int *p)
{
    std::cout << *p + 2 << std::endl;
}

int main(int argc, char* argv[])
{
    int a = 5;
    printValuePlus2(&a); // 7

	return 0;
}