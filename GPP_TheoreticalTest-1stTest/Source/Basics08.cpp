/*  C++ Basics 8
    
    Write a comment explaining the output of the code below
	1) func0() returns F
	F && X == F, where X is either F or T. 
	2) func1() returns T
	T || X == T, where X is either F or T. 

	The compiler knows that	and speed opimizes the code where possible.

	Thus at the line where the first if statement occurs,
	only func0() function is executed (see case 1)) and since it is F
	we move on ...

	to the second if statement. There only func1() (see case 2)) is executed
	and since it is T we go inside the if statement and print Main1;

*/

#include <iostream>

bool func0() { std::cout << "Func0" << std::endl ; return false; }
bool func1() { std::cout << "Func1" << std::endl ; return true; }

int main(int argc, char* argv[])
{
    if (func0() && func1())
    {
        std::cout << "Main0";
    }

    if (func1() || func0())
    {
        std::cout << "Main1";
    }

	return 0;
}