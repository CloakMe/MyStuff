/*  C++ Basics 3
    
    Fix the problem with the code below
    Write a comment to explain the output

	The destructor in the base class must be declared virtual in order 
	to complete proper order of destructor calls inside the class hierarchy.
	Proper destructor order:
	from outside going to inside, i.e. from children to parent.
		
	Going the other way around is wrong because e.g.:
	If child var decides to use parent resource and it has already been cleaned
	the program might crash.

	
*/

#include <iostream>

class A
{
public:
    A(): m_AData(new int()) { std::cout << "Calling A::A() " << std::endl; }
    virtual ~A()                    { std::cout << "Calling A::~A() " << std::endl; delete m_AData; }
private:
    int* m_AData;
};
class B : public A
{
public:
    B(): m_BData(new int()) { std::cout << "Calling B::B() " << std::endl;}
    ~B()                    { std::cout << "Calling B::~B() " << std::endl; delete m_BData; }
private:
    int* m_BData;
};

int main(int argc, char* argv[])
{
    A* someA = new B();
    delete someA;
    B b;

	return 0;
}