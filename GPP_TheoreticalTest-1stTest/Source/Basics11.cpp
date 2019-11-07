/*  C++ Basics 11
    
    Change the definition of class TypePrinter in such a way that it would be impossible for a descendant class to not define the method printClass
*/

#include <iostream>

class TypePrinter
{
public:
    virtual void printClass() = 0; // Children need to override this so it prints the correct class name
};

void TypePrinter::printClass(){}

class A: public TypePrinter
{
public:
	void printClass() { /* TypePrinter::printClass() */}
};

int main(int argc, char* argv[])
{
    A a;
    a.printClass();

	return 0;
}