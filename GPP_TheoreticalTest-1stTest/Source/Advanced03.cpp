/*  C++ Advanced 3
    
    You are debugging a program using your usual debugger and it always crashes on the same memory address because it has been corrupted. 
    The problem is that you don’t know when it could happen and you don’t know what line of source code is causing the crash 
    (And you can’t check all the code... That would take too much time). 
    
    Write a comment explaining the steps you will take in order to find the cause of the problem.
	2. I could use conditional debugging to identify the exact time a change has happened to that memory location
	1. I could assign a pointer to the memory location eg. int* ptr = reinterpret_cast<int*>(0x12345678  <--same memory address);
*/

#include <iostream>

int main(int argc, char* argv[])
{
    *(int *) 42 = 0;

	return 0;
}