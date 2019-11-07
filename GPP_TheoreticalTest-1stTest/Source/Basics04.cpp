/*  C++ Basics 4
    
    Write a comment explaining the problem with the code below
	func returns a reference to an int named 'a'. After the function completes
	'a' is deleted and therefore the adress is invalid.	
*/

#include <iostream>

int& func(int i)
{
    int a = i + 3;
    return a;
}

int g(int a)
{
    return a;
}

int main(int argc, char* argv[])
{
    int &i = func(5);
    std::cout << i << " " << g(3) << std::endl;
	return 0;
}