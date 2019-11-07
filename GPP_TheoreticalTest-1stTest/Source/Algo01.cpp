/*  C++ Algorithms 1
    
    Consider the following sequence – 0,1,1,2,3,5,8,13,21,34,55,89,144...
    Write an iterative function to return the nth element of the sequence.

*/

#include <iostream>

int sequence(unsigned n)
{
    // Smart code goes here
	if( (n==1) || (n==0) )
	{
		return(n);
	}
	else 
	{
		return(sequence(n-1)+sequence(n-2));
	}
	return 0;
}

int main(int argc, char* argv[])
{
    std::cout << sequence(25) << std::endl;

	return 0;
}