/*  C++ Basics 2
    
    Write code that will allocate and then delete an array of 10 arrays of 8 ints each
*/

#include <iostream>

int main(int argc, char* argv[])
{
    // Allocate array of arrays
	int sizeY = 10;
	int sizeX = 8;
	int **ary = new int*[sizeY];
	for(int i = 0; i < sizeY; ++i) {
		ary[i] = new int[sizeX];
	}
    // Delete it
	for(int i = 0; i < sizeY; ++i) {
		delete [] ary[i];
	}
	delete [] ary;
	return 0;
}