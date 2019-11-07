/*  C++ Advanced 4
    
    Explain the result of running the program. Explain how its execution will end.

	The comma operator evaluates both of its arguments in turn, throwing away the result, except for the last. 
	The last evaluated expression determines the result of the entire expression.
	The program is going to finish just when var c exceeds the limit of the int.

*/

#include <iostream>

int main(int argc, char* argv[])
{
    int c = 0;
    while (c < 5, ++c)
        std::cout << c << std::endl;

	return 0;
}